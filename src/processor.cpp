#include "processor.h"
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <thread>
using namespace std::this_thread;
using namespace std::chrono_literals;

using std::string;
using std::ifstream;
using std::istringstream;
using std::stof;
using std::chrono::system_clock;
// TODO: Return the aggregate CPU utilization
/*
PrevIdle = previdle + previowait
Idle = idle + iowait

PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal
NonIdle = user + nice + system + irq + softirq + steal

PrevTotal = PrevIdle + PrevNonIdle
Total = Idle + NonIdle

# differentiate: actual value minus the previous one
totald = Total - PrevTotal
idled = Idle - PrevIdle

CPU_Percentage = (totald - idled)/totald
*/
float Processor::Utilization() {
  string key;
  string line;
  string use, nic, idl, syste, iowai, ir, softIr, stea;
  string fuse, fnic, fidl, fsyste, fiowai, fir, fsoftIr, fstea;
  string file = "/proc/stat";
  ifstream cpustream(file);
  if(cpustream.is_open()){
    while(std::getline(cpustream, line)){
      istringstream stem(line);
      while(stem >> key >> use >> nic >> idl >> syste >> iowai >> ir >> softIr >> stea){
        if(key == "cpu"){
          float user, nice, idle, system, iowait, irq, softIrq, steal;
          user = stof(use);
          nice = stof(nic);
          idle = stof(idl);
          system = stof(syste);
          iowait = stof(iowai);
          irq = stof(ir);
          softIrq = stof(softIr);
          steal = stof(stea);
          float idld = idle + iowait;
          float totd = user + nice + idle + system + iowait + irq + softIrq + steal;
          return (totd-idld)/totd; //I believe I am doing everything to get the correct CPU utilisation, and yet it comes out wrong
        }
      }
    }
  }
  return 0.0;
}

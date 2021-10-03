#include "processor.h"
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using std::string;
using std::ifstream;
using std::istringstream;
using std::stof;

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
stack overflow post: https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
*/
float Processor::Utilization() {
  string key;
  string line;
  string use, nic, idl, syste, iowai, ir, softIr, stea;
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
          float totIdle = iowait + idle;
          float totAct = user + nice + system + irq + softIrq + steal;
          float tot = totIdle + totAct;
          float aggCPU = (tot-totIdle)/tot;
          return aggCPU;
        }
      }
    }
  }
  return 0.0;
}

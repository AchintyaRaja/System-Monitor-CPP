#include <string>
#include <cmath>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) {
  long int minutes = floor(seconds/60);
  int second = seconds%60;
  int minute = minutes%60;
  int hours =  floor(minutes/60);
  string answer = std::to_string(hours) + ":" + std::to_string(minute) + ":" + std::to_string(second);
  return answer;
}

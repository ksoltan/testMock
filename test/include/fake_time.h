#ifndef FAKE_TIME_H
#define FAKE_TIME_H

#include "fake_particle_string.h"

// define global format; we don't actually use this value in tests.
#define TIME_FORMAT_ISO8601_FULL "%Y-%m-%dT%H:%M:%S%z"

class FakeTime {
public:
  String format(){ // returns time string in the format that you set it.
    return curr_time;
  }
  String format(String frmt){ // returns time string in the format that you set it.
    // don't do anything with frmt because we manually set the string
    return curr_time;
  }
  void SetTimeStr(String time_str){
    curr_time = time_str;
  }

private:
  String curr_time;
};

extern FakeTime Time; // initialize in test/main.cpp

#endif // FAKE_TIME_H

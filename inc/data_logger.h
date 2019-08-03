// file: data_logger.h
// Purpose: Write augmented string to SD card
#ifndef data_logger_h
#define data_logger_h

#include "SDFat.h"
#include <vector>

class DataLogger(){
public:
  DataLogger();
  boolean setup(); // Set up the SD card and filename and headers
  boolean setDataHeaders(std::vector<String>);
  boolean writeData();

private:
  String filename;
}

#endif // data_logger_h

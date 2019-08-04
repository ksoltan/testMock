// file: sd_card_writer.h
// Purpose: Write batch of data to SD card

#ifndef sd_card_writer_h
#define sd_card_writer_h

#include "SDFat.h"
#include <vector>

class SDCardWriter {
public:
  SDCardWriter();
  int Setup(); // Set up the SD card and filename and headers
  boolean SetDataHeaders(String);
  boolean WriteData(std::vector<String>);

private:
  String filename;
}

#endif // sd_card_writer_h

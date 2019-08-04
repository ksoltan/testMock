/** File: sd_card_writer.h
    Purpose: Write batch of data packets to SD card when enough packets have been acquired
**/

#ifndef sd_card_writer_h
#define sd_card_writer_h

#include "SDFat.h"

class SDCardWriter {
public:
  struct Options {
    int num_packets_per_batch;
    String filename_format;
    String data_headers;
  }

  SDCardWriter(Batcher*, const Options&);

  int WriteIfReady(); // Write batch only if enough packets have been batched

private:
  Batcher* batcher;
  String filename;

}

#endif // sd_card_writer_h

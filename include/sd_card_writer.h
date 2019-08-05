/** File: sd_card_writer.h
    Purpose: Write batch of data packets to SD card when enough packets have been acquired
**/

#ifndef sd_card_writer_h
#define sd_card_writer_h

#include "SDFat.h"
#include <vector>

class SDCardWriter {
public:
  struct Options {
    int num_packets_per_batch;
    String filename_format;
    String data_headers;
  }
  SDCardWriter(const Options&);
  void AddDataPacket(DataPacket); // Add data packet to batch

private:
  std::vector<DataPacket> data_packet_batch;
  String filename;

}

#endif // sd_card_writer_h

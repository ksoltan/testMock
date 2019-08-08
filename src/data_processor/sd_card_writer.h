/** File: sd_card_writer.h
 *  Purpose: Write batch of data packets to SD card when enough packets have been acquired
**/

#ifndef sd_card_writer_h
#define sd_card_writer_h

#include <vector>
#include <string>

// #include "SDFat.h"
#include "writer_interface.h"

class SDCardWriter : public WriterInterface {
public:
  struct Options {
    int num_packets_per_batch;
    std::string filename_format;
    std::string data_headers;
  };
  SDCardWriter(const Options&);
  void AddDataPacket(const DataPacket&); // Add data packet to batch

private:
  std::vector<DataPacket> data_packet_batch; // Make copies of datapackets internally so that when they go out of scope, you still have them.
  std::string filename;

};

#endif // sd_card_writer_h

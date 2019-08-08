/** File: sd_writer.h
 *  Purpose: Write batch of data packets to SD card when enough packets have been acquired
**/

#ifndef SD_WRITER_H
#define SD_WRITER_H

#include <vector>
#include <string>

// #include "SDFat.h"
#include "writer_interface.h"

class SDWriter : public WriterInterface {
public:
  struct Options {
    int num_packets_per_batch;
    std::string filename_format;
    std::string data_headers;
  };
  SDWriter(const Options&);
  Status AddDataPacket(const DataPacket&); // Add data packet to batch

private:
  std::vector<DataPacket> data_packet_batch_; // Make copies of datapackets internally so that when they go out of scope, you still have them.
  std::string filename_;

};

#endif // SD_WRITER_H

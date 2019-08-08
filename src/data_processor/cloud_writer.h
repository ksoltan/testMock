/** File: cloud_writer.h
 *  Purpose: Publish data packet batches to the cloud when
 *            enough packets have been acquired.
**/

#ifndef CLOUD_WRITER_H
#define CLOUD_WRITER_H

#include "writer_interface"

class CloudWriter : WriterInterface {
public:
  struct Options {
    int num_packets_per_batch;
  };
  CloudWriter(const Options&);
  Status AddDataPacket(const DataPacket&); // Add to batch

private:
  std::vector<DataPacket> data_packet_batch_;
  int Write(); // Publish a batch of data packets when enough have accumulated
};

#endif // CLOUD_WRITER_H

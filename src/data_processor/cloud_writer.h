/** File: cloud_writer.h
 *  Purpose: Publish data packet batches to the cloud when
 *            enough packets have been acquired.
**/

#ifndef cloud_writer_h
#define cloud_writer_h

#include "writer_interface"

class CloudWriter : WriterInterface {
public:
  struct Options {
    int num_packets_per_batch;
  };
  CloudWriter(const Options&);
  void AddDataPacket(const DataPacket&); // Add to batch

private:
  std::vector<DataPacket> data_packet_batch;
  int Write(); // Publish a batch of data packets when enough have accumulated
};

#endif // cloud_publisher_h

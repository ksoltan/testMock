/** File: cloud_writer.h
 *  Purpose: Publish data packet batches to the cloud when
 *            enough packets have been acquired.
**/

#ifndef CLOUD_WRITER_H
#define CLOUD_WRITER_H

#include <vector>

#include "writer_interface.h"

class CloudWriter : WriterInterface {
public:
  struct Options {
    int num_packets_per_batch;
  };
  CloudWriter(const Options&);
  Status AddDataPacket(const DataPacket&); // Batch and publish if enough
  int GetNumPacketsInBatch(); // For testing

private:
  Options options_;
  std::vector<DataPacket> data_packets_;
  Status Write();
};

#endif // CLOUD_WRITER_H

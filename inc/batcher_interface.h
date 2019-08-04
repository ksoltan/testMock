/** File: batcher_interface.h
    Purpose: Batch data packets separately for SD card and Cloud use.
**/

#ifndef batcher_interface_h
#define batcher_interface_h

#include <vector>

#include "data_packet.h"

class BatcherInterface {
public:
  BatcherInterface();
  void AddToBatch(DataPacket);

  int GetCloudBatchLength();
  std::vector<DataPacket> GetCloudBatch();

  int GetSDBatchLength();
  std::vector<DataPacket> GetSDBatch();

  boolean ResetSDBatch();
  boolean ResetCloudBatch();

private:
  std::vector<DataPacket> cloud_batch;
  std::vector<DataPacket> sd_batch;
}

#endif // batcher_interface_h

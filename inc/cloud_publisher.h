// file: cloud_publisher.h
// Purpose: Batch/queue augmented data and push to mesh network
//          for publishing to cloud
#ifndef cloud_publisher_h
#define cloud_publisher_h

#include <vector>

class CloudPublisher {
public:
  CloudPublisher(int);
  boolean setup();
  boolean addDataToBatch(String dataStr);
  boolean publishDataBatch();

private:
  int numDataPerBatch; // can be configured (not constant)
  std::vector<String> batchedData; // to save the data strings to while not publishing
}

#endif // cloud_publisher_h

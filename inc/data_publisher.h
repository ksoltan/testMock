// file: data_publisher.h
// Purpose: Batch/queue augmented data and push to mesh network
//          for publishing to cloud
#ifndef data_publisher_h
#define data_publisher_h

#include <vector>

class DataPublisher(){
public:
  DataPublisher(int);
  boolean setup();
  boolean addDataToBatch(String dataStr);
  boolean publishDataBatch();

private:
  int numDataPerBatch; // can be configured (not constant)
  std::vector<String> batchedData; // to save the data strings to while not publishing
}

#endif // data_publisher_h

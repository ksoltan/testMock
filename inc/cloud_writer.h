/** File: cloud_publisher.h
    Purpose: Publish data packet batches to the cloud when
              enough packets have been acquired.
**/

#ifndef cloud_publisher_h
#define cloud_publisher_h

#include <vector>

class CloudPublisher {
public:
  struct Options {
    int num_packets_per_batch;
  }
  CloudPublisher(Batcher*, const Options&);
  int PublishIfReady(); // If there are enough packets in the cloud batch, push to the cloud

private:
  Batcher* batcher;
}

#endif // cloud_publisher_h

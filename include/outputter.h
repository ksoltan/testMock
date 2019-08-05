/** File: outputter.h
 *  Purpose: Output an annotated data packet to all of the writers.
**/

#ifndef outputter_h
#define outputter_h

#include <memory>
#include <vector>

#include "data_packet.h"

class Outputter {
public:
  Outputter(std::unique_ptr<SDCardWriter>, std::unique_ptr<CloudWriter>);
  void Output(DataPacket);

private:
  SDCardWriter sd_writer;
  CloudWriter cloud_writer;
}

#endif // outputter_h

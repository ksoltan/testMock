/** File: outputter_interface.h
 *  Purpose: Output an annotated data packet to all of the writers.
**/

#ifndef outputter_interface_h
#define outputter_interface_h

#include <memory>
#include <vector>

#include "cloud_writer.h"
#include "data_packet.h"
#include "outputter_interface.h"
#include "sd_card_writer.h"

class Outputter : public OutputterInterface {
public:
  Outputter(std::unique_ptr<SDCardWriter>, std::unique_ptr<CloudWriter>);
  void Output(const DataPacket&);
}

#endif // outputter_interface_h

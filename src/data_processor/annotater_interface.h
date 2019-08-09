/** File: annotater_interface.h
 *  Purpose: Add extra data (such as time or geo location) to a data packet.
 *
**/

#ifndef ANNOTATER_INTERFACE_H
#define ANNOTATER_INTERFACE_H

#include "../common/data_packet.h"

class AnnotaterInterface {
  public:
    virtual ~AnnotaterInterface(){}; // for mocking
    virtual DataPacket Annotate(const DataPacket& /*raw_packet*/) = 0; // Return new annotated DataPacket
};
#endif // ANNOTATER_INTERFACE_H

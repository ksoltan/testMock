/** File: annotater_interface.h
 *  Purpose: Add extra data (such as time or geo location) to a data packet.
 *
**/

#ifndef annotater_interface_h
#define annotater_interface_h

#include "data_packet.h"

class AnnotaterInterface {
  public:
    AnnotaterInterface();
    DataPacket Annotate(const DataPacket& /*raw_packet*/); // Return new annotated DataPacket
}
#endif // annotater_interface_h

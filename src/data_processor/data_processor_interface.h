/** File: data_processor.h
 *  Purpose: Process one data packet
**/

#ifndef DATA_PROCESSOR_INTERFACE_H
#define DATA_PROCESSOR_INTERFACE_H

#include "../common/data_packet.h"
#include "../common/packet_with_status.h"
#include "../common/status.h"

class DataProcessorInterface {
  public:
    virtual void ProcessPacket(const PacketWithStatus<DataPacket>&) = 0; // Assume packet exists.
    virtual void ProcessErrors(const std::vector<Status> &) = 0;
};
#endif // DATA_PROCESSOR_INTERFACE_H

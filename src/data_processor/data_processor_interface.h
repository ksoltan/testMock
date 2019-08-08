/** File: data_processor.h
 *  Purpose: Process one data packet
**/

#ifndef DATA_PROCESSOR_INTERFACE_H
#define DATA_PROCESSOR_INTERFACE_H

#include "../common/data_packet.h"
#include "../common/status.h"

class DataProcessorInterface {
  public:
     // TODO: Make distinct RawDataPacket // Assume packet exists.
    virtual void ProcessPacket(const DataPacket&) = 0;
    virtual void ProcessErrors(const std::vector<Status> &) = 0;
};
#endif // DATA_PROCESSOR_INTERFACE_H

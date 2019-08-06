/** File: data_processor.h
 *  Purpose: Process one data packet
**/

#ifndef data_processor_interface_h
#define data_processor_interface_h

#include <memory>

#include "data_annotater.h"
#include "data_packet.h"
#include "outputter.h"

class DataProcessorInterface {
  public:
    DataProcessorInterface(std::unique_ptr<DataAnnotater>, std::unique_ptr<Outputter>);
    virtual void ProcessPacket(const DataPacket&) = 0; // TODO: Make distinct RawDataPacket // Assume packet exists.
}
#endif // data_processor_interface_h

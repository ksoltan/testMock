/** File: data_processor.h
 *  Purpose: Process one data packet
**/

#ifndef data_processor_interface_h
#define data_processor_interface_h

#include <memory>

#include "annotater_interface.h"
#include "data_packet.h"
#include "outputter_interface.h"

class DataProcessorInterface {
  public:
    DataProcessorInterface(){}; // Default ctor since derived (impls) shouldn't be passing its unique_ptr to the base (interface)
    DataProcessorInterface(std::unique_ptr<AnnotaterInterface>, std::unique_ptr<OutputterInterface>){}
    ~DataProcessorInterface(){};
    virtual void ProcessPacket(const DataPacket&) = 0; // TODO: Make distinct RawDataPacket // Assume packet exists.
};
#endif // data_processor_interface_h

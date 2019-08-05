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
    void ProcessPacket(DataPacket);

  private:
    DataAnnotater annotater;
    Outputter outputter;
}
#endif // data_processor_interface_h

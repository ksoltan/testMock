#ifndef data_processor_impl_h
#define data_processor_impl_h

#include "data_processor_interface.h"

class DataProcessorImpl : public DataProcessorInterface {
  public:
    DataProcessorInterface(std::unique_ptr<DataAnnotater>, std::unique_ptr<Outputter>);
    void ProcessPacket(const DataPacket&); // TODO: Make distinct RawDataPacket // Assume packet exists.

  private:
    DataAnnotater annotater;
    Outputter outputter;
}
#endif // data_processor_impl_h

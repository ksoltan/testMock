#ifndef data_processor_impl_h
#define data_processor_impl_h

#include "data_processor_interface.h"
#include "annotater_interface.h"
#include "outputter_interface.h"

class DataProcessorImpl : DataProcessorInterface {
public:
  DataProcessorInterface(std::unique_ptr<AnnotaterInterface>, std::unique_ptr<OutputterInterface>);
  virtual void ProcessPacket(const DataPacket&) = 0; // TODO: Make distinct RawDataPacket // Assume packet exists.

private:
  AnnotaterInterface annotater;
  OutputterInterface outputter;
};
#endif // data_processor_impl_h

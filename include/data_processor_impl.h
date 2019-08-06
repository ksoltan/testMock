#ifndef data_processor_impl_h
#define data_processor_impl_h

#include "data_processor_interface.h"
#include "annotater_interface.h"
#include "outputter_interface.h"

class DataProcessorImpl : DataProcessorInterface {
public:
  DataProcessorImpl(std::unique_ptr<AnnotaterInterface>, std::unique_ptr<OutputterInterface>);
  ~DataProcessorImpl(){};
  void ProcessPacket(const DataPacket&); // TODO: Make distinct RawDataPacket // Assume packet exists.

private:
  std::unique_ptr<AnnotaterInterface> annotater_ptr;
  std::unique_ptr<OutputterInterface> outputter_ptr;
};
#endif // data_processor_impl_h

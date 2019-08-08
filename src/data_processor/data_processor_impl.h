/** File: data_processor_impl.h
 *  Purpose: Handle annotating packets, outputting them, and outputting any errors
 **/

#ifndef DATA_PROCESSOR_IMPL_H
#define DATA_PROCESSOR_IMPL_H

#include <memory>
#include <vector>

#include "data_processor_interface.h"
#include "annotater_interface.h"
#include "outputter_interface.h"

class DataProcessorImpl : DataProcessorInterface {
public:
  DataProcessorImpl(std::unique_ptr<AnnotaterInterface>, std::unique_ptr<OutputterInterface>);
  ~DataProcessorImpl(){};
  void ProcessPacket(const DataPacket&);
  void ProcessErrors(const std::vector<Status>&);

private:
  // If you want to add multiple annotaters, change to a std::vector of AnnotaterInterfaces
  // and loop through each one, calling its Annotate function
  std::unique_ptr<AnnotaterInterface> annotater_;
  std::unique_ptr<OutputterInterface> outputter_;
};
#endif // DATA_PROCESSOR_IMPL_H

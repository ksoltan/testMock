#include "data_processor_impl.h"

DataProcessorImpl::DataProcessorImpl(std::unique_ptr<AnnotaterInterface> a_ptr, std::unique_ptr<OutputterInterface> o_ptr){
  annotater_ptr = std::move(a_ptr);
  outputter_ptr = std::move(o_ptr);
}

void DataProcessorImpl::ProcessPacket(const DataPacket& raw_packet){
  // Add metadata to the packet
  // If you want to add multiple annotaters, change to a std::vector of AnnotaterInterfaces
  // and loop through each one, calling its Annotate function
  DataPacket annotated_packet = annotater_ptr->Annotate(raw_packet);
  // Output the packets to the appropriate locations/writers
  outputter_ptr->Output(annotated_packet);
}

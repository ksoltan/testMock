#include "data_processor_impl.h"

// TODO: Rename priv vars to blah underscore, change args to func to blach
DataProcessorImpl::DataProcessorImpl(std::unique_ptr<AnnotaterInterface> a_ptr, std::unique_ptr<OutputterInterface> o_ptr){
  annotater_ptr = std::move(a_ptr);
  outputter_ptr = std::move(o_ptr);
}

void DataProcessorImpl::ProcessPacket(const DataPacket& raw_packet){
  // Add metadata to the packet
  DataPacket annotated_packet = annotater_ptr->Annotate(raw_packet);
  // Output the packets to the appropriate locations/writers
  std::vector<Status> errors = outputter_ptr->Output(annotated_packet);
  if(errors.size() != 0){ // Output timestamped error packets
    ProcessErrors(errors);
  }
}

void DataProcessorImpl::ProcessErrors(const std::vector<Status>& errors){
  for(auto const& error : errors){
    DataPacket error_packet = DataPacket(error.msg);
    DataPacket annotated_error_packet = annotater_ptr->Annotate(error_packet);
    outputter_ptr->OutputError(annotated_error_packet);
  }
}

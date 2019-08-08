#include "data_processor_impl.h"

// TODO: Rename priv vars to blah underscore, change args to func to blach
DataProcessorImpl::DataProcessorImpl(std::unique_ptr<AnnotaterInterface> annotater, std::unique_ptr<OutputterInterface> outputter){
  annotater_ = std::move(annotater);
  outputter_ = std::move(outputter);
}

void DataProcessorImpl::ProcessPacket(const DataPacket& raw_packet){
  // Add metadata to the packet
  DataPacket annotated_packet = annotater_->Annotate(raw_packet);
  // Output the packets to the appropriate locations/writers
  std::vector<Status> errors = outputter_->Output(annotated_packet);
  if(errors.size() != 0){ // Output timestamped error packets
    ProcessErrors(errors);
  }
}

void DataProcessorImpl::ProcessErrors(const std::vector<Status>& errors){
  for(auto const& error : errors){
    DataPacket error_packet = DataPacket(error.msg);
    DataPacket annotated_error_packet = annotater_->Annotate(error_packet);
    outputter_->OutputError(annotated_error_packet); // doesn't return status code
  }
}

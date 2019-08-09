#include "data_processor_impl.h"

DataProcessorImpl::DataProcessorImpl(std::unique_ptr<AnnotaterInterface> annotater, std::unique_ptr<OutputterInterface> outputter){
  annotater_ = std::move(annotater);
  outputter_ = std::move(outputter);
}

void DataProcessorImpl::ProcessPacket(const PacketWithStatus<DataPacket>& raw_packet_with_status){
  // Check if packet is errored (ie Read returned status not OK)
  if(raw_packet_with_status.status.NotOK()){
    ProcessError(raw_packet_with_status.status);
    return;
  }
  // Add metadata to the packet
  DataPacket annotated_packet = annotater_->Annotate(raw_packet_with_status.packet);
  // Output the packets to the appropriate locations/writers
  std::vector<Status> errors = outputter_->Output(annotated_packet);
  if(errors.size() != 0){ // Output timestamped error packets
    ProcessErrors(errors);
  }
}

void DataProcessorImpl::ProcessErrors(const std::vector<Status>& errors){
  for(auto const& error : errors){
    ProcessError(error);
  }
}

void DataProcessorImpl::ProcessError(const Status& error){
  DataPacket error_packet = DataPacket(error.msg);
  DataPacket annotated_error_packet = annotater_->Annotate(error_packet);
  outputter_->OutputError(annotated_error_packet); // doesn't return status code
}

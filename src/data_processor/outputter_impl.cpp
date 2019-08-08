#include "outputter_impl.h"

void OutputterImpl::AddWriter(std::unique_ptr<WriterInterface> writer){
  writers_.push_back(std::move(writer));
  return;
}

void OutputterImpl::AddErrorWriter(std::unique_ptr<WriterInterface> writer){
  error_writers_.push_back(std::move(writer));
  return;
}

int OutputterImpl::GetNumWriters(){
  return writers_.size();
}

int OutputterImpl::GetNumErrorWriters(){
  return error_writers_.size();
}

std::vector<Status> OutputterImpl::Output(const DataPacket& annotated_packet){
  std::vector<Status> errors;
  for(auto const& writer : writers_){
    Status status = writer->AddDataPacket(annotated_packet);
    if(status.NotOK()){
      errors.push_back(status);
    }
  }
  return errors;
}

void OutputterImpl::OutputError(const DataPacket& error_packet){
  for(auto const& error_writer : error_writers_){
    error_writer->AddDataPacket(error_packet);
  }
}

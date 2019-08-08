#include "outputter_impl.h"

void OutputterImpl::AddWriter(std::unique_ptr<WriterInterface> writer){
  writers.push_back(std::move(writer));
  return;
}

int OutputterImpl::GetNumWriters(){
  return writers.size();
}

std::vector<Status> OutputterImpl::Output(const DataPacket& annotated_packet){
  std::vector<Status> errors;
  for(auto const& writer : writers){
    writer->AddDataPacket(annotated_packet);
  }
  return errors;
}

Status OutputterImpl::OutputError(const DataPacket& error_packet){
  for(auto const& error_writer : error_writers){
    error_writer->AddDataPacket(error_packet);
  }
  return Status::OK();
}

#include "outputter_impl.h"

void OutputterImpl::AddWriter(std::unique_ptr<WriterInterface> writer){
  writer_ptrs.push_back(std::move(writer));
  return;
}

int OutputterImpl::GetNumWriters(){
  return writer_ptrs.size();
}

void OutputterImpl::Output(const DataPacket& annotated_packet){
  for(auto const& writer : writer_ptrs){
    writer->AddDataPacket(annotated_packet);
  }
}

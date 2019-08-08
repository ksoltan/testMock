#include "cloud_writer.h"

CloudWriter::CloudWriter(const Options& options){
  options_ = options;
}

Status CloudWriter::AddDataPacket(const DataPacket& packet){
  data_packets_.push_back(packet);
  // Check if enough packets to write
  if(GetNumPacketsInBatch() >= options_.num_packets_per_batch){
    // Write
    return Write();
  }
  return Status::OK();
}

int CloudWriter::GetNumPacketsInBatch(){
  return data_packets_.size();
}

Status CloudWriter::Write(){
  int num_failed;
  for(auto const& packet : data_packets_){
    bool publish_flag = Particle.Publish("topic", packet.ToString());
    if(!publish_flag){
      num_failed++;
    }
  }
  data_packets_.clear(); // Clear packets

  if(num_failed > 0){
    return Status::WriteFailed("at Cloud Writer with " + \
                                std::to_string(num_failed) + "/" + \
                                std::to_string(options_.num_packets_per_batch) + \
                                " packets");
  }
  return Status::OK();
}

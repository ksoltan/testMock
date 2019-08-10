#include "cloud_writer.h"

CloudWriter::CloudWriter(const Options& options){
  options_ = options;
}

Status CloudWriter::AddDataPacket(const DataPacket& packet){
  data_packets_.push_back(packet);
  // Check if enough packets to write
  if(GetNumPacketsInBatch() >= options_.num_packets_per_batch){
    return Write();
  }
  return Status::OK();
}

int CloudWriter::GetNumPacketsInBatch(){
  return data_packets_.size();
}

Status CloudWriter::Write(){
  // initialize explicitly to prevent undefined behavior: https://stackoverflow.com/a/6032889
  int num_failed = 0;
  for(auto const& packet : data_packets_){
    bool publish_flag = Particle.publish(options_.event_name, packet.ToString());
    if(!publish_flag){
      num_failed++;
    }
  }
  data_packets_.clear(); // Clear packets

  if(num_failed > 0){ // Return number of packets failed in error msg
    // return Status::WriteFailed(" at Cloud Writer with " + \
    //                             std::to_string(num_failed) + "/" + \
    //                             std::to_string(options_.num_packets_per_batch) + \
    //                             " packets");
    // FOR PARTICLE COMPILE
    return Status::WriteFailed(" at Cloud Writer with " + \
                                String(num_failed) + "/" + \
                                String(options_.num_packets_per_batch) + \
                                " packets");
  }
  return Status::OK();
}

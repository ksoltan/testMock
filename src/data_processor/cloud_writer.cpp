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

unsigned int CloudWriter::GetNumPacketsInBatch(){
  return data_packets_.size();
}

Status CloudWriter::Write(){
  // initialize explicitly to prevent undefined behavior: https://stackoverflow.com/a/6032889
  unsigned int num_failed = 0;
  for(auto const& packet : data_packets_){
    bool publish_flag = Particle.publish(options_.event_name, packet.ToString());
    if(!publish_flag){
      num_failed++;
    }
  }
  data_packets_.clear(); // Clear packets

  if(num_failed > 0){ // Return number of packets failed in error msg
    // 12 is max num of chars to represent an uint, 31 is num of chars of rest of msg with slash
    char buf_msg[2*12 + 31];
    snprintf(buf_msg, sizeof(buf_msg), " at Cloud Writer with %u/%u packets", num_failed, options_.num_packets_per_batch);
    return Status::WriteFailed(buf_msg);
  }
  return Status::OK();
}

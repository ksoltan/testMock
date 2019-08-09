#include "timestamp_annotater.h"

TimestampAnnotater::TimestampAnnotater(const Options& options){
  options_ = options;
}

DataPacket TimestampAnnotater::Annotate(const DataPacket& raw_packet){
  // Copy contents of raw_packet to a new packet
  DataPacket annotated_packet = raw_packet;
  // Set the timestamp
  annotated_packet.timestamp = GetTime();
  return annotated_packet;
}

String TimestampAnnotater::GetTime(){
  // Get formatted string.
  return Time.format(options_.time_format_string); // Get formatted time string
}

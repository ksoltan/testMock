/** File: raw_data_packet.h
 *  Purpose: Instrument-specific packet which the Formatter accepts
 *
 *  TODO: Use protos for more efficiency, readibility, and mutability
**/
#ifndef RAW_PACKET_H
#define RAW_PACKET_H

#include <vector>

struct RawPacket {
  std::vector<uint16_t> input_register_vals;
  std::vector<uint16_t> discrete_input_vals;

  RawPacket(std::vector<uint16_t> input_vals = {}, std::vector<uint16_t> discrete_vals = {})
      : input_register_vals(input_vals), discrete_input_vals(discrete_vals) {}

  bool operator==(const RawPacket& other) const {
    return input_register_vals == other.input_register_vals &&
            discrete_input_vals == other.discrete_input_vals;
  }
};

#endif // RAW_PACKET_H

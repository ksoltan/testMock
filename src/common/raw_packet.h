/** File: raw_data_packet.h
 *  Purpose: Define instrument-specific data format
 *
 *  TODO: Use protos for more efficiency, readibility, and mutability
**/
#ifndef RAW_DATA_PACKET_H
#define RAW_DATA_PACKET_H

struct RawPacket {
  int temperature;
  String name;
  String timestamp;

  bool operator==(const RawPacket& other) const{
    return true; // for testing?
  }
};

#endif // RAW_DATA_PACKET_H

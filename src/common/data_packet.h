/** File: common/data_packet.h
 *  Purpose: Declare data packet used by Annotater and Batcher to store
 *            and write data.
 *
 *  In future, could consider using protos (there is a nanopb library).
 **/

#ifndef data_packet_h
#define data_packet_h

#include "Particle.h" // Required for String library def

struct DataPacket {
  String data;
  String timestamp;

  DataPacket(const DataPacket& other) = default;
  DataPacket& operator=(const DataPacket& other) = default;

  DataPacket(const String& data = "", const String& timestamp = "")
      : data(data), timestamp(timestamp) {}

  // // Return comma separated string with metadata fields first, followed by data
  // String ToString();
  bool operator==(const DataPacket& other) const; // to compare DataPackets in tests
};

#endif // data_packet_h

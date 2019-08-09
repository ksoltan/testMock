/** File: packet_with_status.h
 *  Purpose: Define structure for packing status code
 *          with any data type (RawPacket, DataPacket)
**/

#ifndef PACKET_WITH_STATUS_H
#define PACKET_WITH_STATUS_H

#include "status.h"

template <class T>
struct PacketWithStatus {
  Status status = Status::OK(); // default
  T packet;

  // Status OK and T
  PacketWithStatus(const T& packet) : packet(packet) {}

  // Non-OK Status and T
  PacketWithStatus(const Status& status, const T& packet)
      : status(status), packet(packet) {}

  // Non-OK Status and empty T packet
  PacketWithStatus(const Status& status) : status(status) {}

  bool operator==(const PacketWithStatus<T>& other) const{
    return status == status && packet == packet;
  }
};

#endif // PACKET_WITH_STATUS_H

#include "data_packet.h"

bool DataPacket::operator==(const DataPacket& other) const{
  return timestamp == other.timestamp && data == other.data;
}

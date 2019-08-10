/** File: instrument_reader_interface.h
 *  Purpose: Get raw data packet from instrument when queried
**/

#ifndef INSTRUMENT_READER_INTERFACE_H
#define INSTRUMENT_READER_INTERFACE_H

#include "../common/packet_with_status.h"
#include "../common/raw_packet.h"

class InstrumentReaderInterface {
public:
  virtual ~InstrumentReaderInterface(){}; // For mocking
  virtual PacketWithStatus<RawPacket> Read() = 0; // Read data from instrument
};

#endif // INSTRUMENT_READER_INTERFACE_H

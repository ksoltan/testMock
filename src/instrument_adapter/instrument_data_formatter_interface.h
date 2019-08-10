/** File: instrument_data_formatter_interface.h
 *  Purpose: Parse raw data (RawPacket) into DataPacket format
**/

#ifndef INSTRUMENT_DATA_FORMATTER_INTERFACE_H
#define INSTRUMENT_DATA_FORMATTER_INTERFACE_H

#include "../common/data_packet.h"
#include "../common/raw_packet.h"

class InstrumentDataFormatterInterface {
public:
  virtual ~InstrumentDataFormatterInterface(){};
  virtual DataPacket Format(const RawPacket&) = 0;
};

#endif // INSTRUMENT_DATA_FORMATTER_INTERFACE_H

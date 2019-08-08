/** File: instrument_data_formatter_interface.h
 *  Purpose: Parse raw data (InstrumentDataPacket) into DataPacket format
**/

#ifndef INSTRUMENT_DATA_FORMATTER_INTERFACE_H
#define INSTRUMENT_DATA_FORMATTER_INTERFACE_H

#include "../common/data_packet.h"

class InstrumentDataFormatterInterface {
public:
  InstrumentDataFormatterInterface();
  virtual ~InstrumentDataFormatterInterface();
  virtual DataPacket Format(const InstrumentDataPacket&); // pass by reference
};

#endif // INSTRUMENT_DATA_FORMATTER_INTERFACE_H

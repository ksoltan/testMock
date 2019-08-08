/** File: instrument_data_formatter_interface.h
 *  Purpose: Parse raw data (InstrumentDataPacket) into DataPacket format
**/

#ifndef instrument_data_formatter_interface_h
#define instrument_data_formatter_interface_h

#include "../common/data_packet.h"

class InstrumentDataFormatterInterface {
public:
  InstrumentDataFormatterInterface();
  virtual ~InstrumentDataFormatterInterface();
  virtual DataPacket Format(const InstrumentDataPacket&); // pass by reference
};

#endif // instrument_data_formatter_interface_h

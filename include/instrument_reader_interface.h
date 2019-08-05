/** File: instrument_ raw_data_aquirer
 *  Purpose: Get raw data packet from instrument when queried
**/

#ifndef instrument_reader_interface_h
#define instrument_reader_interface_h

#include "instrument_data_packet.h"

class InstrumentReaderInterface {
public:
  InstrumentReaderInterface();
  virtual ~InstrumentReaderInterface();
  virtual InstrumentDataPacket GetData();
}

#endif // instrument_reader_interface_h

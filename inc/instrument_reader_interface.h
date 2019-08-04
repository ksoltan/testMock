// TODO: - name change: InstrumentReader
//       - optional Options :)

// file: instrument_ raw_data_aquirer
// Purpose: Get raw data string from instrument at a specified rate

// This is instrument specific implementation (such as modbus).

#ifndef instrument_reader_interface_h
#define instrument_reader_interface_h

#include "instrument_data_packet.h"

class InstrumentReaderInterface {
public:
  InstrumentReaderInterface();
  int Connect(); // returns modbus status code
  InstrumentDataPacket GetData();
}

#endif // instrument_reader_interface_h

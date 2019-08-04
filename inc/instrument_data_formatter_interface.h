// file: instrument_data_formatter_interface.h
// Purpose: Parse raw data into comma-separated string

// This is instrument-specific implementation (ie modbus)

#ifndef instrument_data_formatter_interface_h
#define instrument_data_formatter_interface_h

class InstrumentDataFormatterInterface {
public:
  InstrumentDataFormatterInterface();
  String Format(const InstrumentDataPacket&); // pass by reference
}

#endif // instrument_data_formatter_interface_h

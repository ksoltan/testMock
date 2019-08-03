// file: instrument_raw_data_parser.h
// Purpose: Parse raw data into comma-separated string

// This is instrument-specific implementation (ie modbus)

#ifndef instrument_raw_data_parser_h
#define instrument_raw_data_parser_h

class InstrumentRawDataParser(){
public:
  InstrumentRawDataParser();
  String getParsedStr(InstrumentDataPacket);
}

#endif // instrument_raw_data_parser_h

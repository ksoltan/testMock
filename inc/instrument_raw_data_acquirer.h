// file: instrument_ raw_data_aquirer
// Purpose: Get raw data string from instrument at a specified rate

// This is instrument specific implementation (such as modbus).

#ifndef instrument_raw_data_acquirer_h
#define instrument_raw_data_acquirer_h

class InstrumentRawDataAcquirer(){
public:
  InstrumentRawDataAcquirer();
  InstrumentDataPacket getData();
}
#endif // instrument_raw_data_acquirer_h

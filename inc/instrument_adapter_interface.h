// file: instrument_adapter_interface.h
// Purpose: Handle interface with an instrument; respond with parsed data string to a request

#ifndef instrument_adapter_interface_h
#define instrument_adapter_intnerface_h

#include "instrument_raw_data_aquirer.h"
#include "instrument_raw_data_parser.h"
#include <memory>

class InstrumentAdapterInterface {
public:
  struct Options{
    int reading_rate_sec; // TODO: investigate absl::Duration
  }
  InstrumentAdapterInterface(std::unique_ptr<InstrumentRawDataAquirer>,
                    std::unique_ptr<InstrumentRawDataParser>,
                    const Options&);
  virtual ~InstrumentAdapter();
  virtual Setup(); // initialize the connection
  virtual String GetParsedDataStr() = 0; // Query instrument and return a parsed string QUESTION: STRINGS VS CHAR[]

private:
  std::unique_ptr<InstrumentRawDataAquirer> aquirer; // Communcate with instrument
  std::unique_ptr<InstrumentRawDataParser> parser; // Format string properly
  const Options initial_config;
}

#endif // instrument_adapter_interface_h

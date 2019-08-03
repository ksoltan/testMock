// file: instrument_handler.h
// Purpose: Handle interface with an instrument; respond with parsed data string to a request
#ifndef instrument_handler_h
#define instrument_handler_h

#include "instrument_raw_data_aquirer.h"
#include "instrument_raw_data_parser.h"

class InstrumentHandler(){
public:
  // Constructors
  InstrumentHandler(InstrumentRawDataAquirer, InstrumentRawDataParser, int); // Specify rate, (maybe a list of fields that you care about?)
  virtual ~InstrumentRawDataAquirer();

  // Functions
  virtual setup(); // initialize the connection
  virtual String getParsedDataStr(); // Query instrument and return a parsed string QUESTION: STRINGS VS CHAR[]

private:
  InstrumentRawDataAquirer aquirer; // Communcate with instrument
  InstrumentRawDataParser parser; // Format string properly
  int rate; // can change (not constant)
}

#endif // instrument_handler_h

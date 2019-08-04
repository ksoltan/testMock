/** File: instrument_adapter_interface.h
    Purpose: Handle interface with an instrument.
            When prompted, will use the provided Reader and Formatter
            to poll the instrument and return a formatted data packet.
**/

#ifndef instrument_adapter_interface_h
#define instrument_adapter_intnerface_h

#include <memory>

#include "data_packet.h"
#include "instrument_reader_interface.h"
#include "instrument_data_formatter.h"

class InstrumentAdapterInterface {
public:
  InstrumentAdapterInterface(std::unique_ptr<InstrumentRawDataAquirer>,
                    std::unique_ptr<InstrumentRawDataParser>);
  virtual ~InstrumentAdapter();
  virtual int ReadData() = 0; // Read data off of instrument, save internally, and return response code
  virtual DataPacket GetFormattedDataPacket() = 0; // Return internally saved data for annotation

private:
  std::unique_ptr<InstrumentReaderInterface> reader; // Communcate with instrument
  std::unique_ptr<InstrumentDataFormatterInterface> formatter; // Format string into standard form

}

#endif // instrument_adapter_interface_h

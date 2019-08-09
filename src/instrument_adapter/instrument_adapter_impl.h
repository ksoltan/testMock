/** File: instrument_adapter_impl.h
 *  Purpose: Handle interface with an instrument.
 *            When prompted, will use the provided Reader and Formatter
 *            to poll the instrument and return a formatted data packet.
**/

#ifndef INSTRUMENT_ADAPTER_IMPL_H
#define INSTRUMENT_ADAPTER_IMPL_H

#include <memory>

#include "instrument_adapter_interface.h"
#include "instrument_data_formatter_interface.h"
#include "instrument_reader_interface.h"

class InstrumentAdapterImpl : InstrumentAdapterInterface {
public:
  InstrumentAdapterImpl(std::unique_ptr<InstrumentReaderInterface>,
                    std::unique_ptr<InstrumentDataFormatterInterface>);
  PacketWithStatus<DataPacket> GetDataFromInstrument(); // Read data off of instrument and return a formatted DataPacket

private:
  std::unique_ptr<InstrumentReaderInterface> reader_; // Communcate with instrument
  std::unique_ptr<InstrumentDataFormatterInterface> formatter_; // Format string into standard form

};

#endif // INSTRUMENT_ADAPTER_IMPL_H

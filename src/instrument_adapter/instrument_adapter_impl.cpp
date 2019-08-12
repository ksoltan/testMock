#include "instrument_adapter_impl.h"

InstrumentAdapterImpl::InstrumentAdapterImpl(std::unique_ptr<InstrumentReaderInterface> reader,
                  std::unique_ptr<InstrumentDataFormatterInterface> formatter){
  reader_ = std::move(reader);
  formatter_ = std::move(formatter);
}

PacketWithStatus<DataPacket> InstrumentAdapterImpl::GetDataFromInstrument(){
  PacketWithStatus<RawPacket> raw_packet = reader_->Read();
  if(raw_packet.status.NotOK()){
    return PacketWithStatus<DataPacket>(raw_packet.status);
  }
  DataPacket formatted_data = formatter_->Format(raw_packet.packet);
  // Return formatted data and OK status
  return PacketWithStatus<DataPacket>(formatted_data);
}

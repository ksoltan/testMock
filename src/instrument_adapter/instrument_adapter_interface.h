/** File: instrument_adapter_interface.h
 *  Purpose: Handle interface with an instrument.
 *            When prompted, will use the provided Reader and Formatter
 *            to poll the instrument and return a formatted data packet.
 *
 *    Interface file exists in case you need to mock InstrumentAdapter
**/

#ifndef INSTRUMENT_ADAPTER_INTERFACE_H
#define INSTRUMENT_ADAPTER_INTERFACE_H

#include "../common/data_packet.h"
#include "../common/packet_with_status.h"

class InstrumentAdapterInterface {
public:
  virtual ~InstrumentAdapterInterface(){}
  virtual PacketWithStatus<DataPacket> GetDataFromInstrument() = 0; // Read data off of instrument and return a formatted DataPacket
};

#endif // INSTRUMENT_ADAPTER_INTERFACE_H

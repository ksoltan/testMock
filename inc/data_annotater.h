/** File: data_annotater.h
    Purpose: Add metadata (ie. timestamp, geo location) to a Data Packet
**/

#ifndef data_annotater_h
#define data_annotater_h

#include "batcher.h"
#include "cloud_publisher.h"
#include "data_packet.h"
#include "instrument_adapter.h"
#include "parsed_data_augmenter.h"
#include "sd_card_writer.h"

class DataAnnotater {
public:
  // Assumed InstrumentAdapter is alive during lifecycle of DataManager
  DataAnnotater(InstrumentAdapter*);
  DataPacket Annotate(DataPacket); // Add metadata to data packet stored in InstrumentAdapter

private:
  InstrumentAdapter* adapter;
}

#endif // data_annotater_h

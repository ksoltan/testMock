/** File: timestamp_annotater.h
    Purpose: Add  timestamp to a Data Packet
**/

#ifndef timestamp_annotater_h
#define timestamp_annotater_h

#include "annotater_interface.h"
#include "batcher.h"
#include "cloud_publisher.h"
#include "data_packet.h"
#include "instrument_adapter.h"
#include "parsed_data_augmenter.h"
#include "sd_card_writer.h"

class TimestampAnnotater : public AnnotaterInterface {
public:
  TimestampAnnotater();
  DataPacket Annotate(DataPacket); // Add timestamp to data packet
}

#endif // timestamp_annotater_h

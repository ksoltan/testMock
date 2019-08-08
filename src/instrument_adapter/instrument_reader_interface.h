/** File: instrument_ raw_data_aquirer
 *  Purpose: Get raw data packet from instrument when queried
**/

#ifndef INSTRUMENT_READER_INTERFACE_H
#define INSTRUMENT_READER_INTERFACE_H

#include "../common/data_packet.h"

class InstrumentReaderInterface {
public:
  InstrumentReaderInterface();
  virtual ~InstrumentReaderInterface();
  virtual InstrumentDataPacket GetData();
};

#endif // INSTRUMENT_READER_INTERFACE_H

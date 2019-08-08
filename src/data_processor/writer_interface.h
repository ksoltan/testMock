/** File: writer_interface.h
 *  Purpose: Batch data packets and write them to a location
**/

#ifndef WRITER_INTERFACE_H
#define WRITER_INTERFACE_H

#include "../common/status.h"
#include "../common/data_packet.h"

class WriterInterface {
public:
  virtual ~WriterInterface(){}; // for mocking
  virtual Status AddDataPacket(const DataPacket&)=0; // Add packet to batch
};

#endif // WRITER_INTERFACE_H

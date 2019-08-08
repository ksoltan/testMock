/** File: outputter_interface.h
 *  Purpose: Output an annotated data packet to all of the writers.
**/

#ifndef OUTPUTTER_INTERFACE_H
#define OUTPUTTER_INTERFACE_H

#include <memory>
#include <vector>

#include "../common/data_packet.h"
#include "outputter_interface.h"
#include "../common/status.h"
#include "writer_interface.h"

class OutputterInterface {
public:
  virtual ~OutputterInterface(){}; // for mocking
  virtual void AddWriter(std::unique_ptr<WriterInterface>) = 0;
  virtual void AddErrorWriter(std::unique_ptr<WriterInterface>) = 0;
  // Outputting to multiple Writers may result in multiple errors
  virtual std::vector<Status> Output(const DataPacket&) = 0;
  // If outputting error, there is no one else to handle it,
  // so do not return status
  virtual void OutputError(const DataPacket&) = 0;
};

#endif // OUTPUTTER_INTERFACE_H

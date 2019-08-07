/** File: outputter_interface.h
 *  Purpose: Output an annotated data packet to all of the writers.
**/

#ifndef outputter_interface_h
#define outputter_interface_h

#include <memory>
#include <vector>

#include "data_packet.h"
#include "outputter_interface.h"
#include "writer_interface.h"

class OutputterInterface {
public:
  virtual ~OutputterInterface(){}; // for mocking
  // Because passing around a vector of WriterInterfaces seemed maybe not great? Although, I can't imagine we'll have more than 2 writers.
  virtual void AddWriter(std::unique_ptr<WriterInterface>) = 0;
  virtual void Output(const DataPacket&) = 0;
};

#endif // outputter_interface_h

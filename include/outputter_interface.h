/** File: outputter_interface.h
 *  Purpose: Output an annotated data packet to all of the writers.
**/

#ifndef outputter_interface_h
#define outputter_interface_h

#include <memory>
#include <vector>

#include "data_packet.h"
#include "outputter_interface.h"
#include "common/status.h"
#include "writer_interface.h"

class OutputterInterface {
public:
  virtual ~OutputterInterface(){}; // for mocking
  virtual void AddWriter(std::unique_ptr<WriterInterface>) = 0;
  // Outputting to multiple Writers may result in multiple errors
  virtual std::vector<Status> Output(const DataPacket&) = 0;
  virtual Status OutputError(const DataPacket&) = 0;
};

#endif // outputter_interface_h

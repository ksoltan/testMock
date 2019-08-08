/** File: outputter_impl.h
 *  Purpose: Output an annotated data packet to all of the writers.
**/

#ifndef outputter_impl_h
#define outputter_impl_h

#include "outputter_interface.h"

class OutputterImpl : public OutputterInterface {
public:
  void AddWriter(std::unique_ptr<WriterInterface>);
  void AddErrorWriter(std::unique_ptr<WriterInterface>);
  int GetNumWriters();
  int GetNumErrorWriters();
  std::vector<Status> Output(const DataPacket&);
  void OutputError(const DataPacket&);

private:
  std::vector<std::unique_ptr<WriterInterface>> writers;
  std::vector<std::unique_ptr<WriterInterface>> error_writers;
};

#endif // outputter_impl_h

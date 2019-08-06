/** File: outputter_impl.h
 *  Purpose: Output an annotated data packet to all of the writers.
**/

#ifndef outputter_impl_h
#define outputter_impl_h

#include "outputter_interface.h"

class OutputterImpl : public OutputterInterface {
public:
  OutputterImpl(){};
  ~OutputterImpl(){};
  void AddWriter(std::unique_ptr<WriterInterface>);
  void Output(const DataPacket&);
  int GetNumWriters();

private:
  std::vector<std::unique_ptr<WriterInterface>> writer_ptrs;
};

#endif // outputter_impl_h

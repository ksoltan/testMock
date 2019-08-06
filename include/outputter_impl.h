/** File: outputter_impl.h
 *  Purpose: Output an annotated data packet to all of the writers.
**/

#ifndef outputter_impl_h
#define outputter_impl_h

// #include <memory>
#include "outputter_interface.h"

class Outputter : public OutputterInterface {
public:
  Outputter(std::unique_ptr<SDCardWriter>, std::unique_ptr<CloudWriter>);
  void Output(const DataPacket&);

private:
  SDCardWriter sd_writer;
  CloudWriter cloud_writer;
};

#endif // outputter_impl_h

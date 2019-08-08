/** File: writer_interface.h
 *  Purpose: Batch data packets and write them to a location
**/

#ifndef writer_interface_h
#define writer_interface_h

class WriterInterface {
public:
  virtual ~WriterInterface(){}; // for mocking
  virtual void AddDataPacket(const DataPacket&){}; // Add packet to batch
};

#endif // writer_interface_h

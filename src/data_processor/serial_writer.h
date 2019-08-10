/** File: serial_writer.h
 *  Purpose: Print data packets to serial
**/
#ifndef SERIAL_WRITER_H
#define SERIAL_WRITER_H

#include "Particle.h"
#include "writer_interface.h"

class SerialWriter : public WriterInterface {
public:
  SerialWriter(){
    Serial.begin(9600);
  }
  Status AddDataPacket(const DataPacket& packet){
    Serial.println(packet.ToString());
    return Status::OK();
  }
};

#endif // SERIAL_WRITER_H

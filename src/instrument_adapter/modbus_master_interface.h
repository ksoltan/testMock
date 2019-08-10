/** File: modbus_interface.h
 *  Purpose: Interface for ModbusMaster to allow mocking some functions.
*/

#ifndef MODBUS_MASTER_INTERFACE_H
#define MODBUS_MASTER_INTERFACE_H

#include "Particle.h"

class ModbusMasterInterface
{
  public:
    virtual ~ModbusMasterInterface(){} // For mocking

    virtual void begin(uint16_t){};

    static const uint8_t ku8MBIllegalFunction            = 0x01;
    static const uint8_t ku8MBIllegalDataAddress         = 0x02;
    static const uint8_t ku8MBIllegalDataValue           = 0x03;
    static const uint8_t ku8MBSlaveDeviceFailure         = 0x04;
    static const uint8_t ku8MBSuccess                    = 0x00;
    static const uint8_t ku8MBInvalidSlaveID             = 0xE0;
    static const uint8_t ku8MBInvalidFunction            = 0xE1;
    static const uint8_t ku8MBResponseTimedOut           = 0xE2;
    static const uint8_t ku8MBInvalidCRC                 = 0xE3;

    virtual uint16_t getResponseBuffer(uint8_t) = 0;
    virtual void     clearResponseBuffer(){};

    virtual uint8_t  readDiscreteInputs(uint16_t, uint16_t) = 0;
    virtual uint8_t  readInputRegisters(uint16_t, uint8_t) = 0;

};

#endif //MODBUS_MASTER_INTERFACE_H

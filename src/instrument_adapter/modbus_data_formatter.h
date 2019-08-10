/** File: modbus_formatter.h
 *  Purpose: Data formatter for Modbus instrument
**/

#ifndef MODBUS_FORMATTER_H
#define MODBUS_FORMATTER_H

#include <vector>

#include "instrument_data_formatter_interface.h"
#include "../common/T400_registers.h"

class ModbusDataFormatter : InstrumentDataFormatterInterface {
public:
  ModbusDataFormatter();
  ModbusDataFormatter(const std::map<int, DiscreteInputFlag>&);
  DataPacket Format(const RawPacket&);

  String FormatInputRegisters(const std::vector<uint16_t>&);
  String FormatDiscreteInputs(const std::vector<uint16_t>&);

private:
  void SetDiscreteInputFlags(const std::map<int, DiscreteInputFlag>&);
  String VectorToString(const std::vector<float>&);

  float GetFloatFromInt(uint16_t, uint16_t);
  std::vector<DiscreteInputFlag> discrete_input_flags_; // List of addresses of interest
};

#endif // MODBUS_FORMATTER_H

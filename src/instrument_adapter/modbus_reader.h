/** File: modbus_reader.h
 *  Purpose: Data reader for Modbus instrument
**/

#ifndef MODBUS_READER_H
#define MODBUS_READER_H

#include <map>
#include <memory>

#include "instrument_reader_interface.h"
#include "modbus_master_interface.h"
#include "../common/status.h"

#include "../common/T400_registers.h" // Instrument specific definitions

class ModbusReader : InstrumentReaderInterface {
public:
  ModbusReader(std::unique_ptr<ModbusMasterInterface>);
  // Constructor for testing: passing own DISCRETE_INPUTS and INPUT_REGISTERS
  ModbusReader(std::unique_ptr<ModbusMasterInterface>,
              const std::vector<int>&,
              const std::map<int, DiscreteInputFlag>&);
  PacketWithStatus<RawPacket> Read();

private:
  void SetInputRegisterRequestParams(const std::vector<int>&); // start and num addr
  void SetDiscreteInputRequestParams(const std::map<int, DiscreteInputFlag>&); // start and num addr
  void SetInputRegisters(const std::vector<int>&);
  void SetDiscreteInputs(const std::map<int, DiscreteInputFlag>&); // Isolate registers from Flags
  std::vector<uint16_t> GetInputRegisterValues();
  std::vector<uint16_t> GetDiscreteInputValues();
  Status GetErrorStatus(uint8_t /*error code*/, String /*msg*/);

  std::unique_ptr<ModbusMasterInterface> modbus_master_;
  std::vector<int> input_registers_; // List of addresses of interest
  unsigned int discrete_input_start_addr_;
  unsigned int discrete_input_num_addrs_;
  std::vector<int> discrete_inputs_; // List of addresses of interest
  unsigned int input_register_start_addr_;
  unsigned int input_register_num_addrs_;
};

#endif // MODBUS_READER_H

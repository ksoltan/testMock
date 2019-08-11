#include "modbus_reader.h"
#include "Particle.h"
#include <iostream>
ModbusReader::ModbusReader(std::unique_ptr<ModbusMasterInterface> modbus_master){
  modbus_master_ = std::move(modbus_master);
  SetInputRegisterRequestParams(INPUT_REGISTERS);
  SetDiscreteInputRequestParams(DISCRETE_INPUTS_MAP);
}

ModbusReader::ModbusReader(std::unique_ptr<ModbusMasterInterface> modbus_master,
            const std::vector<int>& input_registers,
            const std::map<int, DiscreteInputFlag>& discrete_inputs_map){
  modbus_master_ = std::move(modbus_master);
  SetInputRegisterRequestParams(input_registers);
  SetDiscreteInputRequestParams(discrete_inputs_map);
}

PacketWithStatus<RawPacket> ModbusReader::Read(){
  std::vector<uint16_t> input_register_vals;
  std::vector<uint16_t> discrete_input_vals;
  std::cout << "Attempting to read" << std::endl;
  if(input_register_num_addrs_ > 0){ // Request input registers
    uint8_t result = modbus_master_->readInputRegisters(input_register_start_addr_, input_register_num_addrs_);
    if(result != ModbusMasterInterface::ku8MBSuccess){
      // Return error
      return PacketWithStatus<RawPacket>(GetErrorStatus(result, " on input register read"));
    }
    input_register_vals = GetInputRegisterValues();
  }
  if(discrete_input_num_addrs_ > 0){ // Request discrete inputs
    uint8_t result = modbus_master_->readDiscreteInputs(discrete_input_start_addr_, discrete_input_num_addrs_);
    if(result != ModbusMasterInterface::ku8MBSuccess){
      // Return error
      return PacketWithStatus<RawPacket>(GetErrorStatus(result, " on discrete input read"));
    }
    discrete_input_vals = GetDiscreteInputValues();
  }
  return PacketWithStatus<RawPacket>(RawPacket(input_register_vals, discrete_input_vals));
}

void ModbusReader::SetInputRegisterRequestParams(const std::vector<int>& input_registers){
  if(input_registers.size() > 0){
    input_register_start_addr_ = input_registers.front();
    // Input registers come in pairs
    input_register_num_addrs_ = input_registers.back() - input_register_start_addr_ + 2;
  }
  else{
    input_register_start_addr_ = 0;
    input_register_num_addrs_ = 0;
  }
  SetInputRegisters(input_registers); // Save list of register addresses
}

void ModbusReader::SetDiscreteInputRequestParams(const std::map<int, DiscreteInputFlag>& discrete_inputs_map){
  if(discrete_inputs_map.size() > 0){
    discrete_input_start_addr_ = discrete_inputs_map.begin()->first;
    discrete_input_num_addrs_ = discrete_inputs_map.rbegin()->first - discrete_input_start_addr_ + 1;
  }
  else{
    discrete_input_start_addr_ = 0;
    discrete_input_num_addrs_ = 0;
  }
  SetDiscreteInputs(discrete_inputs_map); // Save list of register addresses
}

void ModbusReader::SetInputRegisters(const std::vector<int>& input_registers){
  input_registers_ = input_registers;
}

void ModbusReader::SetDiscreteInputs(const std::map<int, DiscreteInputFlag>& discrete_inputs_map){
  Serial.println("Setting discrete inputs");
  for(auto const& discrete_input : discrete_inputs_map){
    Serial.printf("%d : %d\n", discrete_input.first, discrete_input.second);
    discrete_inputs_.push_back(discrete_input.first); // Add just the address
  }
}

// Retrieve register values from ModbusMaster buffer (Input registers)
std::vector<uint16_t> ModbusReader::GetInputRegisterValues(){
  std::vector<uint16_t> values;
  for(auto const& input_register : input_registers_){
    int idx_in_buffer = input_register - input_register_start_addr_;
    values.push_back(modbus_master_->getResponseBuffer(idx_in_buffer));
    values.push_back(modbus_master_->getResponseBuffer(idx_in_buffer + 1));
  }
  return values;
}

// Retrieve register values from ModbusMaster buffer (Discrete inputs)
std::vector<uint16_t> ModbusReader::GetDiscreteInputValues(){
  std::vector<uint16_t> values;
  for(auto const& discrete_input : discrete_inputs_){
    int idx_in_buffer = discrete_input - discrete_input_start_addr_;
    values.push_back(modbus_master_->getResponseBuffer(idx_in_buffer));
  }
  return values;
}

// Return a Status with msg corresponding to the ModbusMaster error
Status ModbusReader::GetErrorStatus(uint8_t error_code, String msg){
  switch (error_code) {
    case ModbusMasterInterface::ku8MBIllegalFunction:
      return Status::ReadFailed(" with MB Illegal Function" + msg);
    case ModbusMasterInterface::ku8MBIllegalDataAddress:
      return Status::ReadFailed(" with MB Illegal Data Address" + msg);
    case ModbusMasterInterface::ku8MBIllegalDataValue:
      return Status::ReadFailed(" with MB Illegal Data Value" + msg);
    case ModbusMasterInterface::ku8MBSlaveDeviceFailure:
      return Status::ReadFailed(" with MB Slave Device Failure" + msg);
    case ModbusMasterInterface::ku8MBInvalidSlaveID:
      return Status::ReadFailed(" with MB Invalid Slave ID" + msg);
    case ModbusMasterInterface::ku8MBInvalidFunction:
      return Status::ReadFailed(" with MB Invalid Function" + msg);
    case ModbusMasterInterface::ku8MBResponseTimedOut:
      return Status::ReadFailed(" with MB Response Timed Out" + msg);
    case ModbusMasterInterface::ku8MBInvalidCRC:
      return Status::ReadFailed(" with MB Invalid CRC" + msg);
    default:
      return Status::ReadFailed(" with MB Master Unexpected Error" + msg);
  }
}

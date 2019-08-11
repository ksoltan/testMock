#include "modbus_data_formatter.h"

ModbusDataFormatter::ModbusDataFormatter(){
  SetDiscreteInputFlags(DISCRETE_INPUTS_MAP);
}

ModbusDataFormatter::ModbusDataFormatter(
          const std::map<int, DiscreteInputFlag>& discrete_inputs_map){
  SetDiscreteInputFlags(discrete_inputs_map);
}

DataPacket ModbusDataFormatter::Format(const RawPacket& raw_packet){
  DataPacket formatted_packet;
  String inputs_string = FormatInputRegisters(raw_packet.input_register_vals);
  String discrete_string = FormatDiscreteInputs(raw_packet.discrete_input_vals);

  // Assume that if no input register values arrived, none were expected.
  // Otherwise, the headers in the SD file will be thrown off unless we return
  // a string of commas for the missing input register values.
  if(inputs_string == ""){
    formatted_packet.data = discrete_string;
  } else if(discrete_string == ""){
    formatted_packet.data = inputs_string;
  } else {
    formatted_packet.data = inputs_string + "," + discrete_string;
  }
  return formatted_packet;
}

String ModbusDataFormatter::FormatInputRegisters(
                                          const std::vector<uint16_t>& input_register_vals){

  String res;

  for (uint8_t i = 0; i < input_register_vals.size(); i += 2){
    uint16_t r0 = input_register_vals.at(i);
    uint16_t r1 = input_register_vals.at(i + 1);
    float response = GetFloatFromInt(r0, r1);

    char buf[128];
    // Particle String class has function for stringifying float with set precision
    // Using snprintf because wasn't able to mock String class for unit testing
    snprintf(buf, sizeof(buf), "%.3f", response); // Format to 3 decimals
    res += buf;
    if(i < input_register_vals.size() - 2){
      res += ",";
    }
  }
  return res;
}

String ModbusDataFormatter::FormatDiscreteInputs(const std::vector<uint16_t>& discrete_input_vals){
  if(discrete_input_vals.size() == 0){
    return "";
  }
  uint8_t combined_flag = 0;
  for (uint8_t i = 0; i < discrete_input_vals.size(); i++){
    int flag_shift = discrete_input_flags_[i];
    int flag = (discrete_input_vals[i] == 0) ? 0 : 1;
    combined_flag |= flag << flag_shift;
  }
  char buf[4]; // 4 is max bytes to record uint8_t
  // Particle String class has function for stringifying float with set precision
  // Using snprintf because wasn't able to mock String class for unit testing
  snprintf(buf, sizeof(buf), "%d", combined_flag);
  return buf;
}

void ModbusDataFormatter::SetDiscreteInputFlags(const std::map<int, DiscreteInputFlag>& discrete_inputs_map){
  for(auto const& discrete_input : discrete_inputs_map){
    discrete_input_flags_.push_back(discrete_input.second); // Add just the flag
  }
}

float ModbusDataFormatter::GetFloatFromInt(uint16_t r0, uint16_t r1){
  // https://forum.arduino.cc/index.php?topic=528707.msg3606089#msg3606089
  union{
    uint32_t x;
    float f;
  } u;

  u.x = (((unsigned long) r0 << 16) | r1);
  return u.f;
}

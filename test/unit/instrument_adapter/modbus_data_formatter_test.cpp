#include "catch.hpp"

#include <map>
#include <memory>
#include <vector>

#include "modbus_data_formatter.h"
#include "T400_registers.h"

SCENARIO("Data Formatter returns a data packet with formatted input and discrete input vals"){
GIVEN("A Discrete Input Map and Formatter"){
  const std::map<int, DiscreteInputFlag> discrete_inputs = {
    {1, FLAG_MONITOR},
    {4, FLAG_SAMPLE},
    {9, FLAG_CALIBRATION}
  };
  ModbusDataFormatter modbus_data_formatter(discrete_inputs);

  WHEN("only an input response is received"){
    RawPacket raw_packet;
    raw_packet.input_register_vals = {16848, 52429, 17256, 55111, 50199, 16384};
    DataPacket formatted_packet = modbus_data_formatter.Format(raw_packet);

    THEN("return packet with string with floats formatted to 3 decimal places"){
      REQUIRE(formatted_packet.data == "26.100,232.841,-605.000");
    }
  }

  WHEN("only a discrete input response if received"){
    RawPacket raw_packet;
    raw_packet.discrete_input_vals = {0, 1, 0};
    DataPacket formatted_packet = modbus_data_formatter.Format(raw_packet);
    THEN("return packet with only the discrete flag"){
      REQUIRE(formatted_packet.data == "2");
    }
  }
  WHEN("both input and discrete input responses are received"){
    RawPacket raw_packet;
    raw_packet.input_register_vals = {16848, 52429, 17256, 55111, 50199, 16384};
    raw_packet.discrete_input_vals = {0, 0, 0};
    DataPacket formatted_packet = modbus_data_formatter.Format(raw_packet);

    THEN("return the input registers followed by the discrete flag"){
      REQUIRE(formatted_packet.data == "26.100,232.841,-605.000,0");
    }
  }
}
}

SCENARIO("Format input registers"){
GIVEN("A Formatter"){
  ModbusDataFormatter modbus_data_formatter;
  std::vector<uint16_t> input_register_vals;

  WHEN("No input register values are received"){
    input_register_vals = {};
    String res = modbus_data_formatter.FormatInputRegisters(input_register_vals);

    THEN("return empty string"){
      REQUIRE(res == "");
    }
  }
  WHEN("pairs of input registers are received"){
    input_register_vals = {16848, 52429, 17256, 55111, 50199, 16384};
    String res = modbus_data_formatter.FormatInputRegisters(input_register_vals);

    THEN("return a list of 32-bit signed floats formed from pairs of 16 bit unsigned ints"){
      REQUIRE(res == "26.100,232.841,-605.000");
    }
  }
}
}

SCENARIO("Format discrete input into 3 bit int where each bit corresponds to a flag"){
GIVEN("A Discrete Input Map and Formatter"){
  const std::map<int, DiscreteInputFlag> discrete_inputs = {
    {1, FLAG_MONITOR},
    {4, FLAG_SAMPLE},
    {9, FLAG_CALIBRATION}
  };
  ModbusDataFormatter modbus_data_formatter(discrete_inputs);
  std::vector<uint16_t> discrete_input_vals;

  WHEN("no discrete input data available"){
    discrete_input_vals = {};
    THEN("return empty string"){
      REQUIRE(modbus_data_formatter.FormatDiscreteInputs(discrete_input_vals) == "");
    }
  }
  WHEN("all flags are zero"){
    discrete_input_vals = {0, 0, 0};
    THEN("return 0"){
      REQUIRE(modbus_data_formatter.FormatDiscreteInputs(discrete_input_vals) == "0");
    }
  }
  WHEN("the FLAG_MONITOR is one"){
    discrete_input_vals = {1, 0, 0};
    THEN("the combined integer result has 1 in the rightmost bit position"){
      REQUIRE(modbus_data_formatter.FormatDiscreteInputs(discrete_input_vals) == "1");
    }
  }

  WHEN("the FLAG_SAMPLE is one"){
    discrete_input_vals = {0, 1, 0};
    THEN("the combined integer result has 1 in the second (from the right) bit position"){
      REQUIRE(modbus_data_formatter.FormatDiscreteInputs(discrete_input_vals) == "2");
    }
  }

  WHEN("the FLAG_CALIBRATION is one"){
    discrete_input_vals = {0, 0, 1};
    THEN("the combined integer result has 1 in the third (from the right) bit position"){
      REQUIRE(modbus_data_formatter.FormatDiscreteInputs(discrete_input_vals) == "4");
    }
  }

  WHEN("the FLAG_MONITOR AND FLAG_SAMPLE are both one"){
    discrete_input_vals = {1, 1, 0};
    THEN("the combined integer result has 1 in the two rightmost bit positions"){
      REQUIRE(modbus_data_formatter.FormatDiscreteInputs(discrete_input_vals) == "3");
    }
  }

  WHEN("the FLAG_MONITOR AND FLAG_CALIBRATION are both one"){
    discrete_input_vals = {1, 0, 1};
    THEN("the combined integer result has 1 in the first and third bit positions"){
      REQUIRE(modbus_data_formatter.FormatDiscreteInputs(discrete_input_vals) == "5");
    }
  }

  WHEN("the FLAG_SAMPLE AND FLAG_CALIBRATION are both one"){
    discrete_input_vals = {0, 1, 1};
    THEN("the combined integer result has 1 in the second and third bit positions"){
      REQUIRE(modbus_data_formatter.FormatDiscreteInputs(discrete_input_vals) == "6");
    }
  }

  WHEN("the ALL flags are one"){
    discrete_input_vals = {1, 1, 1};
    THEN("the combined integer result has 1 in all three bit positions"){
      REQUIRE(modbus_data_formatter.FormatDiscreteInputs(discrete_input_vals) == "7");
    }
  }
}
}

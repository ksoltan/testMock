#include "catch.hpp"
#include "fakeit.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "modbus_master_interface.h"
#include "modbus_reader.h"
#include "T400_registers.h"

SCENARIO("Modbus Reader returns register values"){
GIVEN("Modbus Mock"){
  fakeit::Mock<ModbusMasterInterface> mock_modbus;
  fakeit::Fake(Dtor(mock_modbus)); // Stub the dtor to do nothing!!
  ModbusMasterInterface * modbus = &mock_modbus.get();
  std::unique_ptr<ModbusMasterInterface> modbus_ptr(modbus);

  WHEN("input register data is successfully read"){
    // Initialize Modbus Reader with mock modbus
    const std::vector<int> input_registers = {2, 6, 10};
    const std::map<int, DiscreteInputFlag> discrete_inputs = {};
    ModbusReader modbus_reader(std::move(modbus_ptr), input_registers, discrete_inputs);

    // Set response
    std::vector<int> response = {1, 26, 12, 32123, 1212, 9890, 12, 423, 42, 671245};
    fakeit::When(Method(mock_modbus, readInputRegisters)).Return(0x00); // success
    fakeit::When(Method(mock_modbus, getResponseBuffer)).AlwaysDo([response](int i){
      std::cout << "RESPONSE AT " << i << " = " << response.at(i) << std::endl;
      return response.at(i);
      });
    RawPacket expected_raw_packet({1, 26, 1212, 9890, 42, 671245},{});
    PacketWithStatus<RawPacket> expected_packet_with_status(expected_raw_packet); // status OK
    PacketWithStatus<RawPacket> raw_packet_with_status = modbus_reader.Read();

    THEN("return a raw packet with only the register values of interest"){
      REQUIRE(raw_packet_with_status.packet.discrete_input_vals ==
              expected_packet_with_status.packet.discrete_input_vals);
      REQUIRE(raw_packet_with_status.packet.input_register_vals ==
              expected_packet_with_status.packet.input_register_vals);
      fakeit::Verify(Method(mock_modbus, readInputRegisters).Matching(
        [](auto start_addr, auto num_addrs){return start_addr == 2 && num_addrs == 10;})).Exactly(1); // get Response code
      fakeit::Verify(Method(mock_modbus, getResponseBuffer)).Exactly(6);
    }
  }

  // WHEN("discrete input data is successfully read"){
  //   // Initialize Modbus Reader with mock modbus
  //   const std::vector<int> input_registers = {};
  //   const std::map<int, DiscreteInputFlag> discrete_inputs = {
  //     {0, FLAG_SAMPLE},
  //     {1, FLAG_SAMPLE},
  //     {4, FLAG_MONITOR},
  //     {8, FLAG_CALIBRATION}
  //   };
  //   ModbusReader modbus_reader(std::move(modbus_ptr), input_registers, discrete_inputs);
  //
  //   // Set response
  //   std::vector<int> response = {1, 26, 12, 32123, 1212, 9890, 12, 423, 8889};
  //   fakeit::When(Method(mock_modbus, readDiscreteInputs)).Return(0x00); // success
  //   fakeit::When(Method(mock_modbus, getResponseBuffer)).AlwaysDo([response](int i){return response.at(i);});
  //
  //   RawPacket expected_raw_packet({},{1, 26, 1212, 8889});
  //   PacketWithStatus<RawPacket> expected_packet_with_status(expected_raw_packet); // status OK
  //   PacketWithStatus<RawPacket> raw_packet_with_status = modbus_reader.Read();
  //
  //   THEN("return a raw packet with only the discrete input values of interest"){
  //     REQUIRE(raw_packet_with_status.packet.discrete_input_vals ==
  //             expected_packet_with_status.packet.discrete_input_vals);
  //     REQUIRE(raw_packet_with_status.packet.input_register_vals ==
  //             expected_packet_with_status.packet.input_register_vals);
  //     fakeit::Verify(Method(mock_modbus, readDiscreteInputs).Matching(
  //       [](auto start_addr, auto num_addrs){return start_addr == 0 && num_addrs == 9;})).Exactly(1); // get Response code
  //     fakeit::Verify(Method(mock_modbus, getResponseBuffer)).Exactly(4);
  //   }
  // }
  //
  // WHEN("both input register and discrete input data is successfully read"){
  //   // Initialize Modbus Reader with mock modbus
  //   const std::vector<int> input_registers = {2, 6, 10};
  //   const std::map<int, DiscreteInputFlag> discrete_inputs = {
  //     {0, FLAG_SAMPLE},
  //     {1, FLAG_SAMPLE},
  //     {4, FLAG_MONITOR},
  //     {8, FLAG_CALIBRATION}
  //   };
  //   ModbusReader modbus_reader(std::move(modbus_ptr), input_registers, discrete_inputs);
  //
  //   // Set response
  //   std::vector<int> response = {1, 26, 12, 32123, 1212, 9890, 12, 423, 8889, 671245};
  //   fakeit::When(Method(mock_modbus, readInputRegisters)).Return(0x00); // success
  //   fakeit::When(Method(mock_modbus, readDiscreteInputs)).Return(0x00); // success
  //   fakeit::When(Method(mock_modbus, getResponseBuffer)).AlwaysDo([response](int i){return response.at(i);});
  //
  //   RawPacket expected_raw_packet({1, 26, 1212, 9890, 8889, 671245},
  //                                 {1, 26, 1212, 8889});
  //   PacketWithStatus<RawPacket> expected_packet_with_status(expected_raw_packet); // status OK
  //   PacketWithStatus<RawPacket> raw_packet_with_status = modbus_reader.Read();
  //
  //   THEN("return a raw packet with only the discrete input values of interest"){
  //     REQUIRE(raw_packet_with_status.packet.discrete_input_vals ==
  //             expected_packet_with_status.packet.discrete_input_vals);
  //     REQUIRE(raw_packet_with_status.packet.input_register_vals ==
  //             expected_packet_with_status.packet.input_register_vals);
  //     fakeit::Verify(Method(mock_modbus, readInputRegisters).Matching(
  //       [](auto start_addr, auto num_addrs){return start_addr == 2 && num_addrs == 10;})).Exactly(1); // get Response code
  //     fakeit::Verify(Method(mock_modbus, readDiscreteInputs).Matching(
  //       [](auto start_addr, auto num_addrs){return start_addr == 0 && num_addrs == 9;})).Exactly(1); // get Response code
  //     fakeit::Verify(Method(mock_modbus, getResponseBuffer)).Exactly(6+4);
  //   }
  // }
}
}
//
// SCENARIO("Reader returns Read Error"){
// GIVEN("Modbus Mock"){
//   fakeit::Mock<ModbusMasterInterface> mock_modbus;
//   fakeit::Fake(Dtor(mock_modbus)); // Stub the dtor to do nothing!!
//   ModbusMasterInterface * modbus = &mock_modbus.get();
//   std::unique_ptr<ModbusMasterInterface> modbus_ptr(modbus);
//
//   const std::vector<int> input_registers = {2};
//   const std::map<int, DiscreteInputFlag> discrete_inputs = {
//     {1, FLAG_SAMPLE},
//     {2, FLAG_CALIBRATION}
//   };
//   ModbusReader modbus_reader(std::move(modbus_ptr), input_registers, discrete_inputs);
//
//   WHEN("input registers return a non OK response"){
//     // Set response
//     std::vector<int> response = {1, 42};
//     fakeit::When(Method(mock_modbus, readInputRegisters)).Return(0xE2); // Response TimeOut
//
//     RawPacket expected_raw_packet;
//     PacketWithStatus<RawPacket> expected_packet_with_status(
//                 Status::ReadFailed(" with MB Response Timed Out on input register read"),
//                 expected_raw_packet);
//     PacketWithStatus<RawPacket> raw_packet_with_status = modbus_reader.Read();
//
//     THEN("return a non OK status without any other data"){
//       REQUIRE(raw_packet_with_status == expected_packet_with_status);
//       fakeit::Verify(Method(mock_modbus, readInputRegisters).Matching(
//         [](auto start_addr, auto num_addrs){return start_addr == 2 && num_addrs == 2;})).Exactly(1); // get Response code
//     }
//   }
//   // WHEN("discrete inputs return a non OK response"){
//   //   // Set response
//   //   std::vector<int> response = {1, 42};
//   //   fakeit::When(Method(mock_modbus, readInputRegisters)).Return(0x00); // success
//   //   fakeit::When(Method(mock_modbus, readDiscreteInputs)).Return(0x03); // Invalid CRC
//   //
//   //   RawPacket expected_raw_packet;
//   //   PacketWithStatus<RawPacket> expected_packet_with_status(
//   //               Status::ReadFailed(" with Response Timed Out on input register read"),
//   //               expected_raw_packet);
//   //   PacketWithStatus<RawPacket> raw_packet_with_status = modbus_reader.Read();
//   //
//   //   THEN("return a non OK status without any other data"){
//   //     REQUIRE(raw_packet_with_status == expected_packet_with_status);
//   //     fakeit::Verify(Method(mock_modbus, readInputRegisters).Matching(
//   //       [](auto start_addr, auto num_addrs){return start_addr == 2 && num_addrs == 2;})).Exactly(1); // get Response code
//   //   }
//   // }
//
// }
// }

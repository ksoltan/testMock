/** File: TIK_V0.cpp
 *
**/
#include <iostream>
#include <memory>

#include "Particle.h"
FakeParticle Particle;
FakeTime Time;

SerialPort Serial;
SerialPort Serial1;

#include "../../src/common/data_packet.h"
#include "../../src/common/packet_with_status.h"
// #include "../../src/data_processor/annotater_interface.h"
// // #include "../../src/data_processor/cloud_writer.h"
// #include "../../src/data_processor/data_processor_impl.h"
// #include "../../src/data_processor/outputter_impl.h"
// #include "../../src/data_processor/serial_writer.h"
// // #include "../../src/data_processor/sd_writer.h"
// #include "../../src/data_processor/timestamp_annotater.h"
// #include "../../src/data_processor/writer_interface.h"
#include "../../src/instrument_adapter/instrument_adapter_impl.h"
#include "../../src/instrument_adapter/modbus_data_formatter.h"
#include "../../src/instrument_adapter/modbus_master.h"
#include "../../src/instrument_adapter/modbus_reader.h"
#include "../../src/common/T400_registers.h"

// SYSTEM_MODE(MANUAL);

std::unique_ptr<ModbusMaster> modbus_master(new ModbusMaster(1)); // successful
std::unique_ptr<ModbusReader> reader;
std::unique_ptr<ModbusDataFormatter> data_formatter;
std::unique_ptr<InstrumentAdapterImpl> adapter;

void setup(){
  Serial.begin(9600);
  reader = std::make_unique<ModbusReader>(std::move(modbus_master));
  data_formatter = std::make_unique<ModbusDataFormatter>();
  adapter = std::make_unique<InstrumentAdapterImpl>(std::move(reader), std::move(data_formatter));
}

int main(){ // FOR PARTICLE COMPILE: void loop()
  setup();
  while(true){
    for(auto const& s: DISCRETE_INPUTS_MAP){
      std::cout << s.first << " : " << s.second << std::endl;
    }
    PacketWithStatus<DataPacket> packet = adapter->GetDataFromInstrument();
    std::cout << packet.status.msg << "\n" << packet.packet.data << std::endl;
    delay(1000);
  }
  return 0;

}

// // // Instrument Adapter
// // std::unique_ptr<InstrumentDataFormatterInterface> data_formatter(new ModbusDataFormatter());
// // std::unique_ptr<ModbusReader> reader;
// // std::unique_ptr<ModbusMaster> modbus_master;
// // std::unique_ptr<InstrumentAdapterImpl> adapter;
//
// // Data Processor
// std::unique_ptr<DataProcessorImpl> data_processor;
// std::unique_ptr<TimestampAnnotater> timestamp_annotater;
// std::unique_ptr<OutputterImpl> outputter;
// std::unique_ptr<SerialWriter> serial_writer;
// // std::unique_ptr<SDWriter> sd_writer;
// // std::unique_ptr<CloudWriter> cloud_writer;
// // std::unique_ptr<SDWriter> error_sd_writer;
// // std::unique_ptr<CloudWriter> error_cloud_writer;
//
//
// enum State{
//   READ_DATA,
//   WAIT
// };
// State state;
//
// void read_data() {
//   state = READ_DATA;
// }
//
// int data_read_rate_s = 1;
// Timer timer(data_read_rate_s * 1000, read_data);
//
// void setup() {
//   state = WAIT;
//   // Modbus Adapter
//   // modbus_master = std::make_unique<ModbusMaster>();
//   // reader = std::make_unique<ModbusReader>(std::move(modbus_master)); // Initialize with T400_registers
//   // data_formatter = std::make_unique<ModbusDataFormatter>();
//   // adapter = std::make_unique<InstrumentAdapterImpl>(std::move(reader), std::move(data_formatter));
//
//   timestamp_annotater = std::make_unique<TimestampAnnotater>();
//   outputter = std::make_unique<OutputterImpl>();
//   serial_writer = std::make_unique<SerialWriter>();
//   outputter->AddWriter(std::move(serial_writer));
//
//   // Writers
//   // SDWriter::Options sd_writer_options;
//   // sd_writer_options.num_packets_per_batch = 10;
//   // sd_writer = new SDWriter(sd_writer_options);
//   // outputter.AddWriter(std::move(sd_writer));
//   //
//   // CloudWriter::Options cloud_writer_options;
//   // cloud_writer_options.num_packets_per_batch = 3;
//   // cloud_writer_options.event_name = "topic";
//   // cloud_writer = new CloudWriter(cloud_writer_options);
//   // outputter.AddWriter(std::move(cloud_writer));
//
//   // Error Writers
//   // SDWriter::Options error_sd_writer_options;
//   // error_sd_writer_options.num_packets_per_batch = 1;
//   // error_sd_writer = new SDWriter(sd_writer_options);
//   // outputter.AddErrorWriter(std::move(error_sd_writer));
//   //
//   // CloudWriter::Options error_cloud_writer_options;
//   // error_cloud_writer_options.num_packets_per_batch = 1;
//   // error_cloud_writer_options.event_name = "error_topic";
//   // error_cloud_writer = new CloudWriter(error_cloud_writer_options);
//   // outputter.AddErrorWriter(std::move(error_cloud_writer));
//
//
//   data_processor = std::make_unique<DataProcessorImpl>(std::move(timestamp_annotater),
//                                       std::move(outputter));
//
//   timer.start();
// }
//
// void loop(){
//   if(state == READ_DATA){
//     // PacketWithStatus<DataPacket> packet = adapter->GetDataFromInstrument();
//     DataPacket p;
//     PacketWithStatus<DataPacket> packet(p);
//     data_processor->ProcessPacket(packet);
//     state = WAIT; // Reset and wait for next timer-triggered state change
//   }
// }

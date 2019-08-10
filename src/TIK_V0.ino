/** File: TIK_V0.cpp
 *
**/
#include <memory>

#include "Particle.h"

#include "common/data_packet.h"
#include "common/packet_with_status.h"
#include "data_processor/annotater_interface.h"
// #include "data_processor/cloud_writer.h"
#include "data_processor/data_processor_impl.h"
#include "data_processor/outputter_impl.h"
#include "data_processor/serial_writer.h"
// #include "data_processor/sd_writer.h"
#include "data_processor/timestamp_annotater.h"
#include "data_processor/writer_interface.h"
#include "instrument_adapter/instrument_adapter_impl.h"
#include "instrument_adapter/modbus_data_formatter.h"
#include "instrument_adapter/modbus_master.h"
#include "instrument_adapter/modbus_reader.h"
#include "common/T400_registers.h"

SYSTEM_MODE(MANUAL);

std::unique_ptr<ModbusMaster> modbus_master;
std::unique_ptr<ModbusReader> reader;
std::unique_ptr<ModbusDataFormatter> data_formatter;
std::unique_ptr<InstrumentAdapterImpl> adapter;

// Data Processor
std::unique_ptr<DataProcessorImpl> data_processor;
std::unique_ptr<TimestampAnnotater> timestamp_annotater;
std::unique_ptr<OutputterImpl> outputter;
std::unique_ptr<SerialWriter> serial_writer;
std::unique_ptr<SerialWriter> error_serial_writer;
// std::unique_ptr<SDWriter> sd_writer;
// std::unique_ptr<CloudWriter> cloud_writer;
// std::unique_ptr<SDWriter> error_sd_writer;
// std::unique_ptr<CloudWriter> error_cloud_writer;


enum State{
  READ_DATA,
  WAIT
};
State state;

void read_data() {
  state = READ_DATA;
}

int data_read_rate_s = 1;
Timer timer(data_read_rate_s * 1000, read_data);

void setup() {
  state = WAIT;
  Serial.begin(9600);

  // Modbus Adapter
  modbus_master = std::make_unique<ModbusMaster>(1);
  reader = std::make_unique<ModbusReader>(std::move(modbus_master));
  data_formatter = std::make_unique<ModbusDataFormatter>();
  adapter = std::make_unique<InstrumentAdapterImpl>(std::move(reader), std::move(data_formatter));

  timestamp_annotater = std::make_unique<TimestampAnnotater>();
  outputter = std::make_unique<OutputterImpl>();
  serial_writer = std::make_unique<SerialWriter>();
  outputter->AddWriter(std::move(serial_writer));

  error_serial_writer = std::make_unique<SerialWriter>();
  outputter->AddErrorWriter(std::move(error_serial_writer));

  // Writers
  // SDWriter::Options sd_writer_options;
  // sd_writer_options.num_packets_per_batch = 10;
  // sd_writer = new SDWriter(sd_writer_options);
  // outputter.AddWriter(std::move(sd_writer));
  //
  // CloudWriter::Options cloud_writer_options;
  // cloud_writer_options.num_packets_per_batch = 3;
  // cloud_writer_options.event_name = "topic";
  // cloud_writer = new CloudWriter(cloud_writer_options);
  // outputter.AddWriter(std::move(cloud_writer));

  // Error Writers
  // SDWriter::Options error_sd_writer_options;
  // error_sd_writer_options.num_packets_per_batch = 1;
  // error_sd_writer = new SDWriter(sd_writer_options);
  // outputter.AddErrorWriter(std::move(error_sd_writer));
  //
  // CloudWriter::Options error_cloud_writer_options;
  // error_cloud_writer_options.num_packets_per_batch = 1;
  // error_cloud_writer_options.event_name = "error_topic";
  // error_cloud_writer = new CloudWriter(error_cloud_writer_options);
  // outputter.AddErrorWriter(std::move(error_cloud_writer));


  data_processor = std::make_unique<DataProcessorImpl>(std::move(timestamp_annotater),
                                      std::move(outputter));

  timer.start();
}

void loop(){
  if(state == READ_DATA){
    PacketWithStatus<DataPacket> packet = adapter->GetDataFromInstrument();
    data_processor->ProcessPacket(packet);
    state = WAIT; // Reset and wait for next timer-triggered state change
  }
}

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
#include "../../src/data_processor/annotater_interface.h"
// #include "../../src/data_processor/cloud_writer.h"
#include "../../src/data_processor/data_processor_impl.h"
#include "../../src/data_processor/outputter_impl.h"
#include "../../src/data_processor/serial_writer.h"
// #include "../../src/data_processor/sd_writer.h"
#include "../../src/data_processor/timestamp_annotater.h"
#include "../../src/data_processor/writer_interface.h"
#include "../../src/instrument_adapter/instrument_adapter_impl.h"
#include "../../src/instrument_adapter/modbus_data_formatter.h"
#include "../../src/instrument_adapter/modbus_master.h"
#include "../../src/instrument_adapter/modbus_reader.h"
#include "../../src/common/T400_registers.h"

//Instrument Adapter
std::unique_ptr<ModbusMaster> modbus_master(new ModbusMaster(1)); // successful
std::unique_ptr<ModbusReader> reader;
std::unique_ptr<ModbusDataFormatter> data_formatter;
std::unique_ptr<InstrumentAdapterImpl> adapter;

// Data Processor
std::unique_ptr<DataProcessorImpl> data_processor;
std::unique_ptr<TimestampAnnotater> timestamp_annotater;
std::unique_ptr<OutputterImpl> outputter;
std::unique_ptr<SerialWriter> serial_writer;
std::unique_ptr<SerialWriter> error_serial_writer;

enum State{
  READ_DATA,
  WAIT
};
State state;
void read_data() {
  state = READ_DATA;
}
int data_read_rate_s = 1;

void setup(){
  state = WAIT;
  Serial.begin(9600);
  // Modbus Adapter
  modbus_master->begin(57600);
  reader = std::make_unique<ModbusReader>(std::move(modbus_master));
  data_formatter = std::make_unique<ModbusDataFormatter>();
  adapter = std::make_unique<InstrumentAdapterImpl>(std::move(reader), std::move(data_formatter));
  // Data Processor
  timestamp_annotater = std::make_unique<TimestampAnnotater>();
  outputter = std::make_unique<OutputterImpl>();
  serial_writer = std::make_unique<SerialWriter>();
  outputter->AddWriter(std::move(serial_writer));
  error_serial_writer = std::make_unique<SerialWriter>();
  outputter->AddErrorWriter(std::move(error_serial_writer));
  data_processor = std::make_unique<DataProcessorImpl>(std::move(timestamp_annotater), std::move(outputter));
  // timer.start();
  // delay(20000); // Wait 20 seconds to allow particle serial monitor to connect for debugging
}

int main(){ // FOR PARTICLE COMPILE: void loop()
  setup();
  while(true){
    if(state == READ_DATA){
      digitalWrite(D7, HIGH);
      PacketWithStatus<DataPacket> packet = adapter->GetDataFromInstrument();
      data_processor->ProcessPacket(packet);
      digitalWrite(D7, LOW);
      state = WAIT; // Reset and wait for next timer-triggered state change
    }
    // Timer function in .ino file (approximated behavior here)
    delay(data_read_rate_s * 1000);
    state = READ_DATA;
  }
  return 0;

}

// /** File: main.cpp
//     Using main file to understand where objects are being initialized.
//     -> Not all of the necessary inits and includes have been written!
// **/
// #include "application.h" // Required to use Particle libraries
// #include "common/data_packet.h"
//
// std::unique_ptr<InstrumentReader> reader;
// std::unique_ptr<InstrumentDataFormatter> formatter;
// std::unique_ptr<InstrumentAdapter> instrument_adapter; // (reader, formatter);
//
// std::unique_ptr<DataProcessor> data_processor;
// std::unique_ptr<Outputter> outputter;
// std::unique_ptr<SDCardWriter> sd_writer;
// std::unique_ptr<CloudPublisher> publisher;
//
// enum State{
//   READ_DATA,
//   WAIT
// }
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
//   reader = new InstrumentReader();
//   formatter = new InstrumentDataFormatter();
//   adapter = new InstrumentAdapter(reader, formatter);
//   data_processor = new DataProcessor();
//
//   timer.start();
// }
//
// void loop(){
//   if(state == READ_DATA){
//      // Error logging is take care of within this class. If you get an empty packet,
//      // then something went wrong here.
//     const DataPacket raw_packet = instrument_adapter.GetDataFromInstrument(); // TODO: Make RawDataPacket class
//     if(packet){
//       data_processor.ProcessPacket(raw_packet);
//     }
//     state = WAIT; // Reset and wait for next timer-triggered state change
//   }
// }

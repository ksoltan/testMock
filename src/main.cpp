/** File: main.cpp
    Using main file to understand where objects are being initialized.
    -> Not all of the necessary inits and includes have been written!
**/

#include "data_packet.h"
std::unique_ptr<InstrumentReader> reader();
std::unique_ptr<InstrumentDataFormatter> formatter();
std::unique_ptr<InstrumentAdapter> adapter(reader, formatter);

std::unique_ptr<Batcher> batcher;
std::unique_ptr<SDCardWriter> sd_writer(batcher);
std::unique_ptr<CloudPublisher> publisher(batcher);

enum State{
  READ_DATA,
  WAIT
}
State state;

void read_data() {
  state = READ_DATA;
}

int data_read_rate_s = 1;
Timer timer(data_read_rate_s * 1000, read_data);

void setup(){
  state = WAIT;
  timer.start();
}

void loop(){
  if(state == READ_DATA){
    adapter.ReadData();
    DataPacket annotated_data = annotater.Annotate();
    batcher.AddToBatch(annotated_data);
    sd_writer.WriteIfReady();
    publisher.PublishIfReady();
    state = WAIT; // Reset and wait for next timer-triggered state change
  }
}

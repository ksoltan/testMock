/** File: data_processor_test.h
 *
**/
#include <memory>
#include <vector>

#include "catch.hpp"
#include "fakeit.hpp"

#include "annotater_interface.h"
#include "data_packet.h"
#include "data_processor_impl.h"
#include "outputter_interface.h"
#include "status.h"

SCENARIO("DataProcessor processes packet"){
GIVEN("A mock outputter and annotater"){
  // Create a mock annotater without expectations (no definition for Annotate method)
  fakeit::Mock<AnnotaterInterface> mock_annotater;
  fakeit::Fake(Dtor(mock_annotater)); // Stub the dtor to do nothing!!
  AnnotaterInterface * annotater = &mock_annotater.get();
  std::unique_ptr<AnnotaterInterface> a_ptr(annotater);
  // Create a mock outputter that acts just as a placeholder.
  fakeit::Mock<OutputterInterface> mock_outputter;
  fakeit::Fake(Dtor(mock_outputter)); // Stub the dtor to do nothing!!
  OutputterInterface * outputter = &mock_outputter.get();
  std::unique_ptr<OutputterInterface> o_ptr(outputter);
  // Initialize DataProcessor with mock annotater and outputter
  DataProcessorImpl data_processor(std::move(a_ptr), std::move(o_ptr));

  WHEN("DataProcessor receives a data packet with data") {
    DataPacket raw_packet("some data");
    PacketWithStatus<DataPacket> raw_packet_with_status(raw_packet);
    DataPacket annotated_packet("some data", "timestamp");

    fakeit::When(Method(mock_annotater, Annotate).Using(raw_packet)).Return(annotated_packet);
    fakeit::When(Method(mock_outputter, Output).Using(annotated_packet)).Return({});

    data_processor.ProcessPacket(raw_packet_with_status);

    THEN("the packet is annotated and outputted") {
      fakeit::Verify(Method(mock_annotater, Annotate)).Exactly(1);
      fakeit::Verify(Method(mock_outputter, Output)).Exactly(1);
    }
  }

  WHEN("DataProcessor receives an empty packet to annotate"){
    DataPacket raw_packet(""); // empty packet
    PacketWithStatus<DataPacket> raw_packet_with_status(raw_packet);
    DataPacket annotated_packet("", "timestamp");

    fakeit::When(Method(mock_annotater, Annotate).Using(raw_packet)).Return(annotated_packet);
    fakeit::When(Method(mock_outputter, Output).Using(annotated_packet)).Return({});

    data_processor.ProcessPacket(raw_packet_with_status);

    THEN("the packet is annotated and outputted") {
      fakeit::Verify(Method(mock_annotater, Annotate)).Exactly(1);
      fakeit::Verify(Method(mock_outputter, Output)).Exactly(1);
    }
  }

  WHEN("DataProcessor receives one WRITE_FAILED status from Outputter"){
    DataPacket raw_packet("some data"); // empty packet
    PacketWithStatus<DataPacket> raw_packet_with_status(raw_packet);
    DataPacket annotated_packet("some data", "timestamp");
    DataPacket error_packet("Write Failed by SD Writer", "timestamp");
    fakeit::When(Method(mock_annotater, Annotate)).Return(annotated_packet, error_packet);
    fakeit::When(Method(mock_outputter, Output).Using(annotated_packet)).Return({Status::WriteFailed("by SD Writer")});
    fakeit::When(Method(mock_outputter, OutputError).Using(error_packet)).Return();

    data_processor.ProcessPacket(raw_packet_with_status);

    THEN("output a new data packet with error msg"){
      // annotate original packet and 1 error packet
      fakeit::Verify(Method(mock_annotater, Annotate)).Exactly(2);
      fakeit::Verify(Method(mock_outputter, Output)).Exactly(1);
      fakeit::Verify(Method(mock_outputter, OutputError)).Exactly(1);
    }
  }

  WHEN("DataProcessor receives two WRITE_FAILED status from Outputter"){
    DataPacket raw_packet("some data"); // empty packet
    PacketWithStatus<DataPacket> raw_packet_with_status(raw_packet);
    DataPacket annotated_packet("some data", "timestamp");
    DataPacket error_packet1("Write Failed by SD Writer", "timestamp");
    DataPacket error_packet2("Write Failed by Cloud Writer", "timestamp");
    fakeit::When(Method(mock_annotater, Annotate)).Return(annotated_packet,
                                                          error_packet1,
                                                          error_packet2);
    fakeit::When(Method(mock_outputter, Output).Using(annotated_packet)).Return({
                                    Status::WriteFailed("by SD Writer"),
                                    Status::WriteFailed("by Cloud Writer")});
    fakeit::When(Method(mock_outputter, OutputError).Using(error_packet1)).Return();
    fakeit::When(Method(mock_outputter, OutputError).Using(error_packet2)).Return();

    data_processor.ProcessPacket(raw_packet_with_status);

    THEN("output two new data packets with error msgs"){
      // annotate original packet and 2 error packets
      fakeit::Verify(Method(mock_annotater, Annotate)).Exactly(3);
      fakeit::Verify(Method(mock_outputter, Output)).Exactly(1);
      fakeit::Verify(Method(mock_outputter, OutputError)).Exactly(2);
    }
  }

}
}
SCENARIO("DataProcessor processes packet with failed read"){
GIVEN("A mock outputter and annotater"){
  // Create a mock annotater without expectations (no definition for Annotate method)
  fakeit::Mock<AnnotaterInterface> mock_annotater;
  fakeit::Fake(Dtor(mock_annotater)); // Stub the dtor to do nothing!!
  AnnotaterInterface * annotater = &mock_annotater.get();
  std::unique_ptr<AnnotaterInterface> a_ptr(annotater);
  // Create a mock outputter that acts just as a placeholder.
  fakeit::Mock<OutputterInterface> mock_outputter;
  fakeit::Fake(Dtor(mock_outputter)); // Stub the dtor to do nothing!!
  OutputterInterface * outputter = &mock_outputter.get();
  std::unique_ptr<OutputterInterface> o_ptr(outputter);
  // Initialize DataProcessor with mock annotater and outputter
  DataProcessorImpl data_processor(std::move(a_ptr), std::move(o_ptr));

  WHEN("DataProcessor receives a data packet with Read Failed status") {
    Status error = Status::ReadFailed(" with some error");
    PacketWithStatus<DataPacket> raw_packet_with_status(error);
    DataPacket error_packet("Read failed with some error");
    DataPacket annotated_packet("Read failed with some error", "timestamp");

    fakeit::When(Method(mock_annotater, Annotate).Using(error_packet)).Return(annotated_packet);
    fakeit::When(Method(mock_outputter, OutputError).Using(annotated_packet)).Return();

    data_processor.ProcessPacket(raw_packet_with_status);

    THEN("the packet is annotated and outputted") {
      fakeit::Verify(Method(mock_annotater, Annotate)).Exactly(1);
      fakeit::Verify(Method(mock_outputter, OutputError)).Exactly(1);
    }
  }
}
}

/** File: data_processor_test.h
 *
**/
// TODO: How to test Using const ref args
// TODO: How does it deal with failures. More tests. Does Outputter deal with errors? DataProcessor should handle all errors
#include <iostream>
#include <memory>
#include <vector>

#include "catch.hpp"
#include "fakeit.hpp"

#include "annotater_interface.h"
#include "data_packet.h"
#include "data_processor_impl.h"
#include "outputter_interface.h"
#include "common/status.h"

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
    DataPacket annotated_packet("some data", "timestamp");

    fakeit::When(Method(mock_annotater, Annotate).Using(raw_packet)).Return(annotated_packet);
    fakeit::When(Method(mock_outputter, Output).Using(annotated_packet)).Return({});

    data_processor.ProcessPacket(raw_packet);

    THEN("the packet is annotated and outputted") {
      fakeit::Verify(Method(mock_annotater, Annotate)).Exactly(1);
      fakeit::Verify(Method(mock_outputter, Output)).Exactly(1);
    }
  }

  WHEN("DataProcessor receives an empty packet to annotate"){
    DataPacket raw_packet(""); // empty packet
    DataPacket annotated_packet("", "timestamp");

    fakeit::When(Method(mock_annotater, Annotate).Using(raw_packet)).Return(annotated_packet);
    fakeit::When(Method(mock_outputter, Output).Using(annotated_packet)).Return({});

    data_processor.ProcessPacket(raw_packet);

    THEN("the packet is annotated and outputted") {
      fakeit::Verify(Method(mock_annotater, Annotate)).Exactly(1);
      fakeit::Verify(Method(mock_outputter, Output)).Exactly(1);
    }
  }

  WHEN("DataProcessor receives one WRITE_FAILED status from Outputter"){
    DataPacket raw_packet("some data"); // empty packet
    DataPacket annotated_packet("some data", "timestamp");
    DataPacket error_packet("Write Failed by SD Writer", "timestamp");
    fakeit::When(Method(mock_annotater, Annotate)).Return(annotated_packet, error_packet);
    fakeit::When(Method(mock_outputter, Output).Using(annotated_packet)).Return({Status::WriteFailed("by SD Writer")});
    fakeit::When(Method(mock_outputter, OutputError).Using(error_packet)).Return(Status::OK());

    data_processor.ProcessPacket(raw_packet);

    THEN("output a new data packet with error msg"){
      // annotate original packet and 1 error packet
      fakeit::Verify(Method(mock_annotater, Annotate)).Exactly(2);
      fakeit::Verify(Method(mock_outputter, Output)).Exactly(1);
      fakeit::Verify(Method(mock_outputter, OutputError)).Exactly(1);
    }
  }

  WHEN("DataProcessor receives two WRITE_FAILED status from Outputter"){
    DataPacket raw_packet("some data"); // empty packet
    DataPacket annotated_packet("some data", "timestamp");
    DataPacket error_packet1("Write Failed by SD Writer", "timestamp");
    DataPacket error_packet2("Write Failed by Cloud Writer", "timestamp");
    fakeit::When(Method(mock_annotater, Annotate)).Return(annotated_packet,
                                                          error_packet1,
                                                          error_packet2);
    fakeit::When(Method(mock_outputter, Output).Using(annotated_packet)).Return({
                                    Status::WriteFailed("by SD Writer"),
                                    Status::WriteFailed("by Cloud Writer")});
    fakeit::When(Method(mock_outputter, OutputError).Using(error_packet1)).Return(Status::OK());
    fakeit::When(Method(mock_outputter, OutputError).Using(error_packet2)).Return(Status::OK());

    data_processor.ProcessPacket(raw_packet);

    THEN("output two new data packets with error msgs"){
      // annotate original packet and 2 error packets
      fakeit::Verify(Method(mock_annotater, Annotate)).Exactly(3);
      fakeit::Verify(Method(mock_outputter, Output)).Exactly(1);
      fakeit::Verify(Method(mock_outputter, OutputError)).Exactly(2);
    }
  }
  WHEN("DataProcessor receives WRITE_FAILED status from outputting error msg"){
    DataPacket raw_packet("some data"); // empty packet
    DataPacket annotated_packet("some data", "timestamp");
    DataPacket error_packet("Write Failed by SD Writer", "timestamp");
    fakeit::When(Method(mock_annotater, Annotate)).Return(annotated_packet, error_packet);
    fakeit::When(Method(mock_outputter, Output).Using(annotated_packet)).Return({Status::WriteFailed("by SD Writer")});
    // Change OutputError to return an error as compared to the When statement above
    fakeit::When(Method(mock_outputter, OutputError).Using(error_packet)).Return(Status::WriteFailed());

    data_processor.ProcessPacket(raw_packet);

    THEN("it does not take additional action"){
      fakeit::Verify(Method(mock_annotater, Annotate)).Exactly(2);
      fakeit::Verify(Method(mock_outputter, Output)).Exactly(1);
      fakeit::Verify(Method(mock_outputter, OutputError)).Exactly(1);
    }
  }
}
}

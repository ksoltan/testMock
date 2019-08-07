/** File: data_processor_test.h
 *
**/
// TODO: How to test Using const ref args
// TODO: How does it deal with failures. More tests. Does Outputter deal with errors? DataProcessor should handle all errors
#include <iostream>
#include <memory>

#include "catch.hpp"
#include "fakeit.hpp"

#include "annotater_interface.h"
#include "data_packet.h"
#include "data_processor_impl.h"
#include "outputter_interface.h"

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
  fakeit::When(Method(mock_outputter, Output)).Return(); // do nothing
  OutputterInterface * outputter = &mock_outputter.get();
  std::unique_ptr<OutputterInterface> o_ptr(outputter);
  // Initialize DataProcessor with mock annotater and outputter
  DataProcessorImpl data_processor(std::move(a_ptr), std::move(o_ptr));

  WHEN("DataProcessor receives a data packet with data"){
    DataPacket raw_packet;
    raw_packet.data = "some data";

    DataPacket annotated_packet;
    annotated_packet.data = raw_packet.data; // in case we change raw data above
    annotated_packet.timestamp = "timestamp";
    fakeit::When(Method(mock_annotater, Annotate)).Return(annotated_packet);
    data_processor.ProcessPacket(raw_packet);

    THEN("the packet is annotated and outputted"){
      // Annotator should not be called on empty packet
      fakeit::Verify(Method(mock_annotater, Annotate).Using(raw_packet)).Exactly(1);
      // Outputter should be called
      // TODO(@ksoltan) Verify use of AnnotatedPacket
      // The first verify call below succeeds. The second one below (with Using()) fails.
      // Possible because fakeit does not handle const refs: https://github.com/eranpeer/FakeIt/issues/31
      // Both verifications work if Output's arg is changes to a DataPacket pointer.
      fakeit::Verify(Method(mock_outputter, Output)).Exactly(1);
      // fakeit::Verify(Method(mock_outputter, Output).Using(annotated_packet)).Exactly(1);
    }
  }

  WHEN("DataProcessor receives an empty packet to annotate"){
    // Define annotater function to add timestamp
    DataPacket annotated_packet;
    annotated_packet.timestamp = "timestamp";
    fakeit::When(Method(mock_annotater, Annotate)).Return(annotated_packet);

    DataPacket empty_packet;
    data_processor.ProcessPacket(empty_packet);

    THEN("the packet is still annotated and outputted"){
      // Annotator should not be called on empty packet
      fakeit::Verify(Method(mock_annotater, Annotate).Using(empty_packet)).Exactly(1);
      // Outputter should be called
      fakeit::Verify(Method(mock_outputter, Output)).Exactly(1);
    }
  }

  // This should not happen because we wil tests Annotater.
  // Assume that annotater returns an annotated packet
  // WHEN("DataProcessor's Annotater does not add a timestamp"){
  //   THEN("no packet is outputted"){
  //
  //   }
  // }

}
}

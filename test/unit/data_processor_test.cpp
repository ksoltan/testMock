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

TEST_CASE("DataProcessor processes packet properly"){
  // Create mock annotater that returns a data packet with metadata.
  // We check if the annotater gets called with the correct raw data packet.
  // How to pass mock as unique_ptr: https://github.com/eranpeer/FakeIt/issues/10
  fakeit::Mock<AnnotaterInterface> mock_annotater;
  fakeit::Fake(Dtor(mock_annotater)); // Stub the dtor to do nothing!!
  DataPacket annotated_packet = "annotated";
  fakeit::When(Method(mock_annotater, Annotate)).Return(annotated_packet); // return once
  AnnotaterInterface * annotater = &mock_annotater.get();

  // Create a mock outputter that acts just as a placeholder.
  // We check if the outputter was called with the annotated data packet
  // that the mock annotater returns.
  fakeit::Mock<OutputterInterface> mock_outputter;
  fakeit::Fake(Dtor(mock_outputter)); // Stub the dtor to do nothing!!
  fakeit::When(Method(mock_outputter, Output)).Return(); // do nothing
  OutputterInterface * outputter = &mock_outputter.get();

  // Initialize the class-under-test (DataProcessorImpl)
  std::unique_ptr<AnnotaterInterface> a_ptr(annotater);
  std::unique_ptr<OutputterInterface> o_ptr(outputter);
  DataProcessorImpl dp(std::move(a_ptr), std::move(o_ptr)); // Annotater, Outputter

  // Call function under test with a raw packet to process
  const DataPacket& raw_packet = "raw";
  dp.ProcessPacket(raw_packet);

  // // Verify: Annotate method was called with the raw data packet exactly once
  // fakeit::Verify(Method(mock_annotater, Annotate).Using(raw_packet)).Exactly(1);
  //
  // // Verify: Outputter was called with the annotated Data Packet arg, also called once.
  // // The first verify call below succeeds. The second one below (with Using()) fails.
  // // Possible because fakeit does not handle const refs: https://github.com/eranpeer/FakeIt/issues/31
  // // Both verifications work if Output's arg is changes to a DataPacket pointer.
  // fakeit::Verify(Method(mock_outputter, Output)).Exactly(1);
  // // fakeit::Verify(Method(mock_outputter, Output).Using(annotated_packet)).Exactly(1);
}

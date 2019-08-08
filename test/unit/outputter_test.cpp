/** File: outputter_test.cpp
 *
**/
#include <memory>
#include <vector>
#include "catch.hpp"
#include "fakeit.hpp"

#include "data_packet.h"
#include "outputter_impl.h"
#include "writer_interface.h"
#include "status.h"

SCENARIO("Adding Writers to Outputter"){
GIVEN("Some mock Writers"){
  fakeit::Mock<WriterInterface> mock_writer_1;
  fakeit::Fake(Dtor(mock_writer_1));
  fakeit::Fake(Method(mock_writer_1, AddDataPacket));
  WriterInterface * writer_1 = &mock_writer_1.get();

  fakeit::Mock<WriterInterface> mock_writer_2;
  fakeit::Fake(Dtor(mock_writer_2));
  fakeit::Fake(Method(mock_writer_2, AddDataPacket));
  WriterInterface * writer_2 = &mock_writer_2.get();

  fakeit::Mock<WriterInterface> mock_writer_3;
  fakeit::Fake(Dtor(mock_writer_3));
  fakeit::Fake(Method(mock_writer_3, AddDataPacket));
  WriterInterface * writer_3 = &mock_writer_3.get();

  std::unique_ptr<WriterInterface> writer_1_ptr(writer_1);
  std::unique_ptr<WriterInterface> writer_2_ptr(writer_2);
  std::unique_ptr<WriterInterface> writer_3_ptr(writer_3);

  WHEN("no Writers are added"){
    OutputterImpl outputter;
    THEN("return 0 total Writers"){
      REQUIRE(outputter.GetNumWriters() == 0);
    }
  }

  WHEN("one Writer is added"){
    OutputterImpl outputter;
    outputter.AddWriter(std::move(writer_1_ptr));
    THEN("return 1 total Writers"){
      // Check that writers were added.
      REQUIRE(outputter.GetNumWriters() == 1);
    }
  }

  WHEN("three Writers are added"){
    OutputterImpl outputter;
    outputter.AddWriter(std::move(writer_1_ptr));
    outputter.AddWriter(std::move(writer_2_ptr));
    outputter.AddWriter(std::move(writer_3_ptr));
    THEN("return 3 total Writers"){
      // Check that writers were added.
      REQUIRE(outputter.GetNumWriters() == 3);
    }
  }
}
}

SCENARIO("Outputter distributes annotated packet to list of writers successfully"){
GIVEN("Two mock Writers"){
  // Initialize three WriterInterfaces
  // Not doing programatically because need to verify the calls separately for each mock
  fakeit::Mock<WriterInterface> mock_writer_1;
  fakeit::Fake(Dtor(mock_writer_1));
  WriterInterface * writer_1 = &mock_writer_1.get();

  fakeit::Mock<WriterInterface> mock_writer_2;
  fakeit::Fake(Dtor(mock_writer_2));
  WriterInterface * writer_2 = &mock_writer_2.get();

  std::unique_ptr<WriterInterface> writer_1_ptr(writer_1);
  std::unique_ptr<WriterInterface> writer_2_ptr(writer_2);

  OutputterImpl outputter;
  // Add the writers
  outputter.AddWriter(std::move(writer_1_ptr));
  outputter.AddWriter(std::move(writer_2_ptr));

  WHEN("all writers successfully write the packet"){
    DataPacket annotated_packet("some data", "timestamp");

    fakeit::When(Method(mock_writer_1, AddDataPacket).Using(annotated_packet)).Return(Status::OK());
    fakeit::When(Method(mock_writer_2, AddDataPacket).Using(annotated_packet)).Return(Status::OK());

    std::vector<Status> errors = outputter.Output(annotated_packet);

    THEN("Outputter will return no status codes"){
      // Verify: annotated packet was added to both writers
      fakeit::Verify(Method(mock_writer_1, AddDataPacket)).Exactly(1);
      fakeit::Verify(Method(mock_writer_2, AddDataPacket)).Exactly(1);
      std::vector<Status> empty_vector;
      REQUIRE(errors == empty_vector);
    }
  }

  WHEN("the first writer returns an error code"){
    DataPacket annotated_packet("some data", "timestamp");

    fakeit::When(Method(mock_writer_1, AddDataPacket).Using(annotated_packet)).Return(Status::WriteFailed());
    fakeit::When(Method(mock_writer_2, AddDataPacket).Using(annotated_packet)).Return(Status::OK());

    std::vector<Status> errors = outputter.Output(annotated_packet);

    THEN("Outputter will return the error code"){
      // Verify both writers still called
      fakeit::Verify(Method(mock_writer_1, AddDataPacket)).Exactly(1);
      fakeit::Verify(Method(mock_writer_2, AddDataPacket)).Exactly(1);
      std::vector<Status> expected_errors = {Status::WriteFailed()};
      REQUIRE(errors == expected_errors);
    }
  }

  WHEN("the both writers returns an error code"){
    DataPacket annotated_packet("some data", "timestamp");

    fakeit::When(Method(mock_writer_1, AddDataPacket).Using(annotated_packet)).Return(Status::WriteFailed());
    fakeit::When(Method(mock_writer_2, AddDataPacket).Using(annotated_packet)).Return(Status::WriteFailed());

    std::vector<Status> errors = outputter.Output(annotated_packet);

    THEN("Outputter will return both error codes"){
      // Verify both writers still called
      fakeit::Verify(Method(mock_writer_1, AddDataPacket)).Exactly(1);
      fakeit::Verify(Method(mock_writer_2, AddDataPacket)).Exactly(1);
      std::vector<Status> expected_errors = {Status::WriteFailed(), Status::WriteFailed()};
      REQUIRE(errors == expected_errors);
    }
  }
}
}

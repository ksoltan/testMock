// /** File: outputter_test.cpp
//  *
// **/
// #include <memory>
// #include <vector>
// #include <iostream>
// #include "catch.hpp"
// #include "fakeit.hpp"
//
// #include "outputter_impl.h"
// #include "writer_interface.h"
//
// // SCENARIO("Adding writers to Outputter"){
// // GIVEN("An outputter"){
// //   OutputterImpl outputter;
// //   //
// //   // WHEN("no writers are added"){
// //   //   THEN("return total of 0 writers"){
// //   //     REQUIRE(outputter.GetNumWriters() == 0);
// //   //   }
// //   // }
// //
// //   WHEN("one writer is added"){
// //     OutputterImpl outputter1;
// //     fakeit::Mock<WriterInterface> mock_writer;
// //     fakeit::Fake(Dtor(mock_writer));
// //     WriterInterface * writer = &mock_writer.get();
// //     std::unique_ptr<WriterInterface> writer_ptr(writer);
// //
// //     outputter1.AddWriter(std::move(writer_ptr));
// //
// //     // THEN("return total of 1 writers"){
// //     //   REQUIRE(outputter.GetNumWriters() == 1);
// //     // }
// //   }
// //   //
// //   // WHEN("adding many writers"){
// //   //   int num_writers = 5;
// //   //   for(int i = 0; i < num_writers; i++){
// //   //     fakeit::Mock<WriterInterface> mock_writer;
// //   //     fakeit::Fake(Dtor(mock_writer));
// //   //     WriterInterface * writer = &mock_writer.get();
// //   //     std::unique_ptr<WriterInterface> writer_ptr(writer);
// //   //
// //   //     outputter.AddWriter(std::move(writer_ptr));
// //   //   }
// //   //   THEN("return the proper total of writers (> 1)"){
// //   //     REQUIRE(outputter.GetNumWriters() == num_writers);
// //   //     std::cout << "Required 5\n";
// //   //   }
// //   // }
// // }
// // }
// SCENARIO("Outputter distributes annotated packet to list of writers successfully"){
//   GIVEN("Three mocks of writers"){
//     // Initialize three WriterInterfaces
//     // Not doing programatically because need to verify the calls separately for each mock
//     fakeit::Mock<WriterInterface> mock_writer_1;
//     fakeit::Fake(Dtor(mock_writer_1));
//     fakeit::Fake(Method(mock_writer_1, AddDataPacket)); // TODO: possibly returns success code (like added to batch, or written to file?)
//     WriterInterface * writer_1 = &mock_writer_1.get();
//
//     fakeit::Mock<WriterInterface> mock_writer_2;
//     fakeit::Fake(Dtor(mock_writer_2));
//     fakeit::Fake(Method(mock_writer_2, AddDataPacket)); // TODO: possibly returns success code (like added to batch, or written to file?)
//     WriterInterface * writer_2 = &mock_writer_2.get();
//
//     fakeit::Mock<WriterInterface> mock_writer_3;
//     fakeit::Fake(Dtor(mock_writer_3));
//     fakeit::Fake(Method(mock_writer_3, AddDataPacket)); // TODO: possibly returns success code (like added to batch, or written to file?)
//     WriterInterface * writer_3 = &mock_writer_3.get();
//
//     std::unique_ptr<WriterInterface> writer_1_ptr(writer_1);
//     std::unique_ptr<WriterInterface> writer_2_ptr(writer_2);
//     std::unique_ptr<WriterInterface> writer_3_ptr(writer_3);
//
//     WHEN("the writers are added to an Outputter"){
//       OutputterImpl outputter; // Ctor does not take arguments, so do not use parens
//       // Add the writers
//       outputter.AddWriter(std::move(writer_1_ptr));
//       outputter.AddWriter(std::move(writer_2_ptr));
//       outputter.AddWriter(std::move(writer_3_ptr));
//       // Check that writers were added.
//       REQUIRE(outputter.GetNumWriters() == 3);
//
//       THEN("Outputter will output a DataPacket to all three writers"){
//         DataPacket annotated_packet;
//         annotated_packet.timestamp = "timestamp";
//         outputter.Output(annotated_packet);
//
//         // Verify: annotated packet was added to both writers
//         // Currently not using the Using param due to const ref & limitations.
//         fakeit::Verify(Method(mock_writer_1, AddDataPacket)).Exactly(1);
//         fakeit::Verify(Method(mock_writer_2, AddDataPacket)).Exactly(1);
//         fakeit::Verify(Method(mock_writer_3, AddDataPacket)).Exactly(1);
//         // fakeit::Verify(Method(mock_sd_writer, AddDataPacket).Using(annotated_packet)).Exactly(1);
//         // fakeit::Verify(Method(mock_cloud_writer, AddDataPacket).Using(annotated_packet)).Exactly(1);
//       }
//     }
//   }
// }

/** File: cloud_writer_test.h
 *
**/
#include "catch.hpp"
#include "cloud_writer.h"
#include "data_packet.h"
#include "Particle.h"
FakeParticle Particle;

TEST_CASE("CloudWriter adds packet to batch"){
  CloudWriter::Options options;
  options.num_packets_per_batch = 3;

  CloudWriter cloud_writer = CloudWriter(options);
  SECTION("No packets have been added"){
    REQUIRE(cloud_writer.GetNumPacketsInBatch() == 0);
  }
  SECTION("Add one packet, batch increases"){
    cloud_writer.AddDataPacket(DataPacket("some data", "timestamp"));
    REQUIRE(cloud_writer.GetNumPacketsInBatch() == 1);
  }
  SECTION("Add three packets and write batch"){
    cloud_writer.AddDataPacket(DataPacket("some data", "timestamp 1"));
    cloud_writer.AddDataPacket(DataPacket("some more data", "timestamp 2"));
    REQUIRE(cloud_writer.GetNumPacketsInBatch() == 2);
    cloud_writer.AddDataPacket(DataPacket("even more data", "timestamp 3"));
    REQUIRE(cloud_writer.GetNumPacketsInBatch() == 0); // Write and clear data
  }
  SECTION("Add three packets, write batch, and add more packets"){
    cloud_writer.AddDataPacket(DataPacket("some data", "timestamp 1"));
    cloud_writer.AddDataPacket(DataPacket("some more data", "timestamp 2"));
    cloud_writer.AddDataPacket(DataPacket("even more data", "timestamp 3"));
    REQUIRE(cloud_writer.GetNumPacketsInBatch() == 0); // Write and clear data
    cloud_writer.AddDataPacket(DataPacket("more more data", "timestamp 4"));
    cloud_writer.AddDataPacket(DataPacket("even more more data", "timestamp 5"));
    REQUIRE(cloud_writer.GetNumPacketsInBatch() == 2);
  }
  SECTION("Return OK status"){
    Particle.SetPublishFlag(true);
    cloud_writer.AddDataPacket(DataPacket("some data", "timestamp 1"));
    cloud_writer.AddDataPacket(DataPacket("some more data", "timestamp 2"));
    Status status = cloud_writer.AddDataPacket(DataPacket("even more data", "timestamp 3"));
    REQUIRE(status == Status::OK());
    REQUIRE(Particle.GetPublishedDataAt(0) == "timestamp 1,some data");
    REQUIRE(Particle.GetPublishedDataAt(1) == "timestamp 2,some more data");
    REQUIRE(Particle.GetPublishedDataAt(2) == "timestamp 3,even more data");
  }
  SECTION("Return NOT OK status"){
    Particle.SetPublishFlag(false);
    cloud_writer.AddDataPacket(DataPacket("some data", "timestamp 1"));
    cloud_writer.AddDataPacket(DataPacket("some more data", "timestamp 2"));
    Status status = cloud_writer.AddDataPacket(DataPacket("even more data", "timestamp 3"));
    Status expected_status = Status::WriteFailed("at Cloud Writer with 3/3 packets");
    REQUIRE(status == expected_status);
  }
}

/** File: cloud_writer_test.h
 *
**/
#include "catch.hpp"
#include "cloud_writer.h"
#include "data_packet.h"
#include "Particle.h"

SCENARIO("CloudWriter batches packets and writes them to the cloud"){
GIVEN("A cloudwriter with batch number of 3"){
  CloudWriter::Options options;
  options.num_packets_per_batch = 3;
  options.event_name = "topic";
  CloudWriter cloud_writer = CloudWriter(options);

  WHEN("no packets have been added"){
    THEN("the batch is empty"){
      REQUIRE(cloud_writer.GetNumPacketsInBatch() == 0);
    }
  }

  WHEN("one packet is added"){
    cloud_writer.AddDataPacket(DataPacket("some data", "timestamp"));
    THEN("add packet to batch"){
      REQUIRE(cloud_writer.GetNumPacketsInBatch() == 1);
    }
  }

  WHEN("three packets are added and successfully published"){
      Particle.SetPublishReturnFlags({true, true, true});
      cloud_writer.AddDataPacket(DataPacket("data", "timestamp 1"));
      cloud_writer.AddDataPacket(DataPacket("more data", "timestamp 2"));
      Status status = cloud_writer.AddDataPacket(
                                  DataPacket("even more data", "timestamp 3"));

      // Check published successfully
      REQUIRE(Particle.GetPublishedDataAt(0) == "timestamp 1,data");
      REQUIRE(Particle.GetPublishedDataAt(1) == "timestamp 2,more data");
      REQUIRE(Particle.GetPublishedDataAt(2) == "timestamp 3,even more data");
      REQUIRE(status == Status::OK());

    THEN("clear the batch and return OK status"){
      REQUIRE(cloud_writer.GetNumPacketsInBatch() == 0); // Write and clear data
      Particle.Reset();
    }
  }

  WHEN("five packets are added in total"){
    Particle.SetPublishReturnFlags({true, true, true});
    cloud_writer.AddDataPacket(DataPacket("data", "timestamp 1"));
    cloud_writer.AddDataPacket(DataPacket("more data", "timestamp 2"));
    cloud_writer.AddDataPacket(DataPacket("even more data", "timestamp 3"));
    cloud_writer.AddDataPacket(DataPacket("data", "timestamp 4"));
    cloud_writer.AddDataPacket(DataPacket("more data", "timestamp 5"));

    THEN("publish only the first batch of 3 and queue the other 2 packets"){
      // Check published successfully
      REQUIRE(Particle.GetPublishedDataAt(0) == "timestamp 1,data");
      REQUIRE(Particle.GetPublishedDataAt(1) == "timestamp 2,more data");
      REQUIRE(Particle.GetPublishedDataAt(2) == "timestamp 3,even more data");
      // Check other packets added to batch
      REQUIRE(cloud_writer.GetNumPacketsInBatch() == 2);
      Particle.Reset();
    }
  }

  WHEN("all packets in batch of 3 fail to publish"){
    Particle.SetPublishReturnFlags({false, false, false});
    cloud_writer.AddDataPacket(DataPacket("data", "timestamp 1"));
    cloud_writer.AddDataPacket(DataPacket("more data", "timestamp 2"));
    Status status = cloud_writer.AddDataPacket(
                                  DataPacket("even more data", "timestamp 3"));
    THEN("clear batch and return an error saying 3/3 packets failed"){
      REQUIRE(cloud_writer.GetNumPacketsInBatch() == 0);
      Status expected_status = Status::WriteFailed(" at Cloud Writer with 3/3 packets");
      REQUIRE(status == expected_status);
      Particle.Reset();
    }
  }

  WHEN("only 2 packets in batch fail to publish"){
    Particle.SetPublishReturnFlags({false, true, false});
    cloud_writer.AddDataPacket(DataPacket("data", "timestamp 1"));
    cloud_writer.AddDataPacket(DataPacket("more data", "timestamp 2"));
    Status status = cloud_writer.AddDataPacket(
                                  DataPacket("even more data", "timestamp 3"));
    THEN("clear batch and return an error saying 2/3 packets failed"){
      REQUIRE(cloud_writer.GetNumPacketsInBatch() == 0);
      Status expected_status = Status::WriteFailed(" at Cloud Writer with 2/3 packets");
      REQUIRE(status == expected_status);
      Particle.Reset();
    }
  }
}
}

SCENARIO("CloudWriter pushes data as soon as it receives it (ie. error logging config))"){
GIVEN("A cloudwriter with batch number of 1"){
  CloudWriter::Options options;
  options.num_packets_per_batch = 1;
  options.event_name = "error topic";
  CloudWriter cloud_writer = CloudWriter(options);

  WHEN("one packet is added"){
    Particle.SetPublishReturnFlags({true});
    Status status = cloud_writer.AddDataPacket(
                                  DataPacket("some data", "timestamp"));
    THEN("publish packet and clear batch"){
      REQUIRE(status == Status::OK());
      REQUIRE(Particle.GetPublishedDataAt(0) == "timestamp,some data");
      REQUIRE(cloud_writer.GetNumPacketsInBatch() == 0);
      Particle.Reset();
    }
  }

  WHEN("one failing packet is added"){
    Particle.SetPublishReturnFlags({false});
    Status status = cloud_writer.AddDataPacket(
                                  DataPacket("some data", "timestamp"));
    THEN("return error code and clear batch"){
      Status expected_status = Status::WriteFailed(" at Cloud Writer with 1/1 packets");
      REQUIRE(status == expected_status);
      REQUIRE(cloud_writer.GetNumPacketsInBatch() == 0);
      Particle.Reset();
    }
  }
}
}

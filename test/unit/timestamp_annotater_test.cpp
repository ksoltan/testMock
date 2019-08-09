/** File: timestamp_annotater_test.cpp
 *
 *    Current unittest does not test setting different format strings
 *    because the Time.format() function is stubbed.
**/

#include "catch.hpp"
#include "timestamp_annotater.h"

SCENARIO("Annotate data packet with timestamp"){
GIVEN("A Timestamp Annotater"){
  TimestampAnnotater timestamp_annotater;

  WHEN("annotating an empty packet"){
    String curr_time = "2019-01-01T03:00:48Z";
    Time.SetTimeStr(curr_time); // ISO 8601 standard string
    DataPacket empty_packet;

    THEN("add timestamp and return with empty data"){
      DataPacket expected_annotated_packet = DataPacket("", curr_time);
      REQUIRE(timestamp_annotater.Annotate(empty_packet) ==
                  expected_annotated_packet);
    }
  }

  WHEN("annotating a packet with data"){
    String curr_time = "2088-08-08T08:08:08Z";
    Time.SetTimeStr(curr_time); // ISO 8601 standard string
    DataPacket raw_packet = DataPacket("some data");

    THEN("add timestamp and return with original data"){
      DataPacket expected_annotated_packet = DataPacket("some data", curr_time);
      REQUIRE(timestamp_annotater.Annotate(raw_packet) ==
                  expected_annotated_packet);
    }
  }

  WHEN("annotating a packet which already contains a timestamp"){
    String curr_time = "2088-08-08T08:08:08Z";
    Time.SetTimeStr(curr_time); // ISO 8601 standard string
    DataPacket raw_packet = DataPacket("some data", "2019-01-01T03:00:48Z");

    THEN("overwrite the original timestamp"){
      DataPacket expected_annotated_packet = DataPacket("some data", curr_time);
      REQUIRE(timestamp_annotater.Annotate(raw_packet) ==
                  expected_annotated_packet);
    }
  }
}
}

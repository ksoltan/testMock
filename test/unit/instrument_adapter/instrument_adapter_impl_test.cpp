#include "catch.hpp"
#include "fakeit.hpp"

#include "instrument_adapter_impl.h"
#include "instrument_data_formatter_interface.h"
#include "instrument_reader_interface.h"

SCENARIO("Instruments Adapter get data from instrument"){
GIVEN("Mock Reader and Formatter"){
  // Mock Reader
  fakeit::Mock<InstrumentReaderInterface> mock_reader;
  fakeit::Fake(Dtor(mock_reader)); // Stub the dtor to do nothing!!
  InstrumentReaderInterface * reader = &mock_reader.get();
  std::unique_ptr<InstrumentReaderInterface> reader_ptr(reader);
  // Mock Data Formatter
  fakeit::Mock<InstrumentDataFormatterInterface> mock_formatter;
  fakeit::Fake(Dtor(mock_formatter)); // Stub the dtor to do nothing!!
  InstrumentDataFormatterInterface * formatter = &mock_formatter.get();
  std::unique_ptr<InstrumentDataFormatterInterface> formatter_ptr(formatter);

  // Initialize InstrumentAdapter with mock reader and formatter
  InstrumentAdapterImpl adapter(std::move(reader_ptr), std::move(formatter_ptr));

  WHEN("some data is successfully read and formatted"){
    RawPacket raw_packet;
    PacketWithStatus<RawPacket> raw_response(raw_packet); // Status OK
    DataPacket formatted_data;
    PacketWithStatus<DataPacket> formatted_response(formatted_data); // Status OK

    fakeit::When(Method(mock_reader, Read)).Return(raw_response);
    fakeit::When(Method(mock_formatter, Format).Using(raw_packet)).Return(formatted_data);

    PacketWithStatus<DataPacket> response = adapter.GetDataFromInstrument();

    THEN("return the formatted packet and Status OK"){
      REQUIRE(response == formatted_response);
      fakeit::Verify(Method(mock_reader, Read)).Exactly(1);
      fakeit::Verify(Method(mock_formatter, Format)).Exactly(1);
    }
  }

  WHEN("the data is unsuccessfully read"){
    PacketWithStatus<RawPacket> raw_response(Status::ReadFailed(" with some error msg"));
    fakeit::When(Method(mock_reader, Read)).Return(raw_response);

    PacketWithStatus<DataPacket> response = adapter.GetDataFromInstrument();

    THEN("return an empty packet and Status with Error"){
      PacketWithStatus<DataPacket> error_response(Status::ReadFailed(" with some error msg"));
      REQUIRE(response == error_response);
      fakeit::Verify(Method(mock_reader, Read)).Exactly(1);
    }
  }
}
}

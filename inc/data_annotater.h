// Polls instrumentAdapter, adds metadata, and augment with timestamps.
// Send to Batcher.

// file: data_annotater.h
// Purpose: Direct a parsed string to QA/QC, SD logging, and Cloud Publishing
#ifndef data_annotater_h
#define data_annotater_h

#include "sd_card_writer.h"
#include "cloud_publisher.h"
#include "instrument_adapter.h"
#include "parsed_data_augmenter.h"

class DataAnnotater {
public:
  struct Options {
    int instrument_handler_poll_rate_sec;
  }
  // Assumed InstrumentAdapter is alive during lifecycle of DataManager
  DataAnnotater(InstrumentAdapter*, const Options&); // need data log rate?
  boolean setup(); // initialize the loggers
  boolean saveData(); // eh, needs better name... it's really the main function...
                      // augments the data and sends it to be logged by SD and publisher

private:
  SDCardWriter sdWriter;
  CloudPublisher cloudPublisher;
  String currentDataStr;
}

#endif // data_annotater_h

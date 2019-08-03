// file: manager.h
// Purpose: Direct a parsed string to QA/QC, SD logging, and Cloud Publishing
#ifndef data_manager_h
#define data_manager_h

#include "data_logger.h"
#include "data_publisher.h"
#include "instrument_handler.h"
#include "parsed_data_augmenter.h"

class DataManager(){
public:
  DataManager(InstrumentHandler, int); // need data log rate?
  boolean setup(); // initialize the loggers
  boolean saveData(); // eh, needs better name... it's really the main function...
                      // augments the data and sends it to be logged by SD and publisher

private:
  DataLogger dataLogger;
  DataPublisher publisher;
  String currentDataStr;
}

#endif // data_manager_h

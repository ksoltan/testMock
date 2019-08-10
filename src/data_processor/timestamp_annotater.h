/** File: timestamp_annotater.h
 *  Purpose: Add timestamp to data packet
**/

#ifndef TIMESTAMP_ANNOTATER_H
#define TIMESTAMP_ANNOTATER_H

#include "annotater_interface.h"

class TimestampAnnotater : public AnnotaterInterface {
public:
  struct Options {
    // Use Particle's predefined ISO 8601 format string as default
    // Custom format based on http://www.cplusplus.com/reference/ctime/strftime/
    String time_format_string = TIME_FORMAT_ISO8601_FULL;
  };
  TimestampAnnotater(){}; // Default Options are initialized
  TimestampAnnotater(const Options&);
  DataPacket Annotate(const DataPacket& /*raw_packet*/);
  String GetTime();

private:
  Options options_;
};

#endif // TIMESTAMP_ANNOTATER_H

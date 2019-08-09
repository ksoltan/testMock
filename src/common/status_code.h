/** File: status_codes.h
 *  Purpose: Define shared error codes from instrument communication
 *            and writing a packet.
**/
#ifndef STATUS_CODE_H
#define STATUS_CODE_H

enum StatusCode {
  OK,
  READ_FAILED,
  WRITE_FAILED
};

#endif // STATUS_CODE_H

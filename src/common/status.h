/** File: status.h
 *  Purpose: Define
**/
#ifndef STATUS_H
#define STATUS_H

#include "Particle.h"
#include "status_code.h"

struct Status {
  StatusCode code;
  String msg; // Optional msg

  Status(){};
  Status(StatusCode code, const String& msg = "")
      : code(code), msg(msg) {}

  bool operator==(const Status& other) const{
    return code == other.code && msg == other.msg;
  }


  static Status OK(){return Status(StatusCode::OK);}

  static Status WriteFailed(const String& msg = ""){
    return Status(StatusCode::WRITE_FAILED, "Write failed" + msg);
  }

  static Status ReadFailed(const String& msg = ""){
    return Status(StatusCode::READ_FAILED, "Read failed" + msg);
  }

  bool NotOK () const{return code != StatusCode::OK;}
};

#endif // STATUS_H

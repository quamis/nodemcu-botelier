#ifndef _NODE_BOTELIERLIB_RESPONSE_
#define _NODE_BOTELIERLIB_RESPONSE_

#include <Arduino.h>

class Response {
};

class Response_sysInfo : public Response {
  public:
    char* time;
    char* ip;
    char* uptime;
};


#endif
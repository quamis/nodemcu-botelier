#ifndef _NODE_BOTELIERLIB_RESPONSE_
#define _NODE_BOTELIERLIB_RESPONSE_

#include <Arduino.h>
#include <queue>



class Response {
};

class Response_sysInfo : public Response {
  public:
    char* time;
    char* ip;
    char* uptime;
};

class ResponseQueue {
  public:
    std::queue<Response> queue;
};

#endif
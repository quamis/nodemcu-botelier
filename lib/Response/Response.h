#ifndef _NODE_BOTELIERLIB_RESPONSE_
#define _NODE_BOTELIERLIB_RESPONSE_

#include <Arduino.h>
#include <queue>
#include <string.h>


class Response {
  public:
    String toJson() { String s; return s; };
};

class Response_heartbeat : public Response {
  public:
    String toJson();
    uint commandsExecuted = 0;
};

class Response_sysInfo : public Response {
  public:
    String toJson();
    time_t time = 0;
    uint32_t free_heap_size = 0;
};




class ResponseQueue {
  public:
    std::queue<Response> queue;
};

#endif
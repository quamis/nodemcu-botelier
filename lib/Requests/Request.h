#ifndef _NODE_BOTELIERLIB_REQUEST_
#define _NODE_BOTELIERLIB_REQUEST_

#include <Arduino.h>
#include <queue>
#include "Response.h"
#include <string.h>

class Request {
    public:
        Request() { };
        int request;

};

#define _rq_getHeartbeat_ 0x0001
class Request_getHeartbeat : public Request {
  public:
    Request_getHeartbeat () { request = _rq_getHeartbeat_; };
};

#define _rq_GetSysInfo_ 0x0002
class Request_getSysInfo : public Request {
  public:
    Request_getSysInfo () { request = _rq_GetSysInfo_; };
};










class RequestQueue {
  private:
    uint commandsExecuted = 0;
  public:
    std::queue<Request> queue;
    void executeQueue(ResponseQueue responseQueue);
};


#endif
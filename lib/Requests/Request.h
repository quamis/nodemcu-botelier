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

#define _rq_GetSysInfo_ 0x0001
class Request_getSysInfo : public Request {
  public:
    Request_getSysInfo () { request = _rq_GetSysInfo_; };
};

class RequestQueue {
  public:
    std::queue<Request> queue;
    void executeQueue(ResponseQueue responseQueue);
};


#endif
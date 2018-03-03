#ifndef _NODE_BOTELIERLIB_REQUEST_
#define _NODE_BOTELIERLIB_REQUEST_

#include <Arduino.h>
#include <queue>
#include "Response.h"
#include <string.h>

// base class
class Request {
    public:
        Request() { };
        int request;

};

// queue class
class RequestQueue {
  private:
    uint commandsExecuted = 0;
  public:
    std::queue<Request *> queue;
    void executeQueue(ResponseQueue responseQueue);
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


#define _rq_LightOn_ 0x0011
class Request_lightOn : public Request {
  public:
    Request_lightOn () { request = _rq_LightOn_; };

    uint location = 0;
};

#define _rq_LightOff_ 0x0012
class Request_lightOff : public Request {
  public:
    Request_lightOff () { request = _rq_LightOff_; };

    uint location = 0;
};


#define _rq_getWifiList_ 0x0101
class Request_getWifiList : public Request {
  public:
    Request_getWifiList () { request = _rq_getWifiList_; };
};




#endif
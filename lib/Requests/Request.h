#ifndef _NODE_BOTELIERLIB_REQUEST_
#define _NODE_BOTELIERLIB_REQUEST_

#include <Arduino.h>
#include <queue>

class Request {
    public:
        Request() { };
        
        
    protected:
        const char* request;

};

class Request_getSysInfo : public Request {
  public:
    Request_getSysInfo () { request = "getSysInfo"; };
};


class RequestQueue {
  public:
    std::queue<Request> queue;
    void executeQueue();
};


#endif
#ifndef _NODE_BOTELIERLIB_COMMANDS_
#define _NODE_BOTELIERLIB_COMMANDS_

#include <Arduino.h>
#include "Response.h"
#include "Request.h"

class Command {
    public:
        Command() { };
        virtual void execute(ResponseQueue *responseQueue);
};


class Command_getHeartbeat : public Command {
  public:
    void execute(ResponseQueue *responseQueue, uint commandsExecuted);
};

class Command_getSysInfo : public Command {
  public:
    void execute(ResponseQueue *responseQueue);
};


class Command_wait : public Command {
  public:
    void execute(ResponseQueue *responseQueue);

    Request_wait* rq = NULL;
};


class Command_lightOn : public Command {
  public:
    void execute(ResponseQueue *responseQueue);

    Request_lightOn* rq = NULL;
};

class Command_lightOff : public Command {
  public:
    void execute(ResponseQueue *responseQueue);

    Request_lightOff* rq = NULL;
};



class Command_getWifiList : public Command {
  public:
    void execute(ResponseQueue *responseQueue);
};



#endif
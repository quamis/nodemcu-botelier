#ifndef _NODE_BOTELIERLIB_COMMANDS_
#define _NODE_BOTELIERLIB_COMMANDS_

#include <Arduino.h>
#include "Response.h"
#include "Request.h"

class Command {
    public:
        Command() { };
        void execute(ResponseQueue responseQueue);
};


class Command_getHeartbeat : public Command {
  public:
    //using Command::execute;
    void execute(ResponseQueue responseQueue, uint commandsExecuted);
};

class Command_getSysInfo : public Command {
  public:
    using Command::execute;
    void execute(ResponseQueue responseQueue);
};

class Command_lightOn : public Command {
  public:
    using Command::execute;
    void execute(ResponseQueue responseQueue);

    Request_lightOn* rq = NULL;
};

class Command_lightOff : public Command {
  public:
    using Command::execute;
    void execute(ResponseQueue responseQueue);

    Request_lightOff* rq = NULL;
};

#endif
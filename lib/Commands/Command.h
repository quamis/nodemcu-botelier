#ifndef _NODE_BOTELIERLIB_COMMANDS_
#define _NODE_BOTELIERLIB_COMMANDS_

#include <Arduino.h>
#include "Response.h"

class Command {
    public:
        Command() { };
        void execute(ResponseQueue responseQueue);

    protected:
        const char* command;

};

class Command_getSysInfo : public Command {
  public:
    Command_getSysInfo () { command = "getSysInfo"; };

    using Command::execute;
    void execute(ResponseQueue responseQueue);
};


#endif
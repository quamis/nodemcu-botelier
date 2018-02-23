#include <Arduino.h>
#include "Command.h"
#include "Response.h"

void Command::execute(ResponseQueue responseQueue) {
}

void Command_getSysInfo::execute(ResponseQueue responseQueue) {
    // fill in something in the reponse
    Command::execute(responseQueue);
}

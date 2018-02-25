#include <Arduino.h>
#include <sys/time.h>
#include "stdexcept"
#include "Utils.h"
#include "Command.h"
#include "Response.h"
#include "Request.h"

extern "C" {
  #include "user_interface.h"
}

void Command::execute(ResponseQueue responseQueue) {
}

void Command_getHeartbeat::execute(ResponseQueue responseQueue, uint commandsExecuted) {
    Response_heartbeat rs;
    rs.commandsExecuted = commandsExecuted;
    responseQueue.queue.push(rs);
}


void Command_getSysInfo::execute(ResponseQueue responseQueue) {
    // fill in something in the reponse
    // Command::execute(responseQueue);
    Response_sysInfo rs;

    struct timeval now;
    if (gettimeofday(&now, NULL)==0) {
        rs.time = now.tv_sec;
    }

    rs.free_heap_size = system_get_free_heap_size();

    responseQueue.queue.push(rs);
}

void Command_lightOn::execute(ResponseQueue responseQueue) {
    switch (rq->location) {
        case 1:
            digitalWrite(BUILTIN_LED, LOW);
        break;
        case 2:
            digitalWrite(D4, LOW);
        break;
    }
}

void Command_lightOff::execute(ResponseQueue responseQueue) {
    switch (rq->location) {
        case 1:
            digitalWrite(BUILTIN_LED, HIGH);
        break;
        case 2:
            digitalWrite(D4, HIGH);
        break;
    }
}

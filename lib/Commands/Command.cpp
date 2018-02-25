#include <Arduino.h>
#include <sys/time.h>
#include "Utils.h"
#include "Command.h"
#include "Response.h"
#include "Request.h"
#include "Utils.h"

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

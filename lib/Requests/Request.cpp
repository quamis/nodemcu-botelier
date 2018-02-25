#include <Arduino.h>
#include <queue>
#include "Utils.h"
#include "Request.h"
#include "Response.h"
#include "Command.h"
#include <string.h>

void RequestQueue::executeQueue(ResponseQueue responseQueue) {
    int executedItems = 0;
    while (!queue.empty()) {
        Request &rq = queue.front();
        p("  <execute queue item %d, 0x%04x\n", executedItems, rq.request);

        switch (rq.request) {
            case _rq_getHeartbeat_: {
                Command_getHeartbeat c;
                c.execute(responseQueue, commandsExecuted);
            }
            break;

            case _rq_GetSysInfo_: {
                Command_getSysInfo c;
                c.execute(responseQueue);
            }
            break;
        }

        commandsExecuted+=1;

        queue.pop();
        executedItems++;
    };
}

#include <Arduino.h>
#include <queue>
#include "Utils.h"
#include "Request.h"
#include "Response.h"
#include "Command.h"
#include <string.h>

void RequestQueue::executeQueue(ResponseQueue *responseQueue) {
    int executedItems = 0;

    p("  <execute queue, items: %d\n", queue.size());
    while (!queue.empty()) {
        Request* rq = queue.front();
        // Request_lightOn* rq = reinterpret_cast<Request_lightOn*>(&queue.front());
        switch (rq->request) {
            case _rq_getHeartbeat_: {
                Command_getHeartbeat c;
                c.execute(responseQueue, commandsExecuted);
                p("  <    %s\n", "Command_getHeartbeat");
            }
            break;

            case _rq_GetSysInfo_: {
                Command_getSysInfo c;
                c.execute(responseQueue);
                p("  <  %s\n", "Command_getSysInfo");
            }
            break;

            case _rq_wait_: {
                Command_wait c;
                c.rq = reinterpret_cast<Request_wait*>(queue.front());
                c.execute(responseQueue);
                p("  <  %s\n", "Command_wait");
            }
            break;

            case _rq_LightOn_: {
                Command_lightOn c;
                c.rq = reinterpret_cast<Request_lightOn*>(queue.front());
                c.execute(responseQueue);
                p("  <  %s, %d\n", "Command_lightOn", c.rq->location);
            }
            break;

            case _rq_LightOff_: {
                Command_lightOff c;
                c.rq = reinterpret_cast<Request_lightOff*>(queue.front());
                c.execute(responseQueue);
                p("  <  %s, %d\n", "Command_lightOff", c.rq->location);
            }
            break;

            case _rq_getWifiList_: {
                Command_getWifiList c;
                c.execute(responseQueue);
                p("  <  %s\n", "Command_getWifiList");
            }
            break;

            default:
                p("<    unknown request! (0x%4x)\n", rq->request);
        }

        commandsExecuted++;
        executedItems++;

        delete queue.front();
        queue.pop();
        /*
        Remember that there is a lot of code that needs to run on the chip besides the sketch 
        when WiFi is connected. WiFi and TCP/IP libraries get a chance to handle any pending 
        events each time the loop() function completes, OR when delay is called. 
        If you have a loop somewhere in your sketch that takes a lot of time (>50ms) without 
        calling delay, you might consider adding a call to delay function to keep the WiFi 
        stack running smoothly.
        There is also a yield() function which is equivalent to delay(0)
        */
        yield();
    };
}

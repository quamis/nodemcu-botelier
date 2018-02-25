#include <Arduino.h>
#include <queue>
#include <stdarg.h>
#include <string.h>

#include "Utils.h"
#include "Command.h"
#include "Response.h"
#include "Request.h"

#define WIFI_SSID "xxxx";
#define WIFI_PASSWORD "xxxx";

extern "C" {
  #include "user_interface.h"
}


class WIFI {
  public:
    String SSID = "";
    String password = "";
    
    void connect() {
      p("Connecting to wifi %s", SSID.c_str());
    }
};
WIFI wifi;

// https://playground.arduino.cc/Code/QueueList



RequestQueue requestQueue;
ResponseQueue responseQueue;

void setup(void) {
  Serial.begin(921600);

  // name comes from https://en.wikipedia.org/wiki/Butler
  p("************************************************************\n");
  p("Starting up Boutellier");

  // pinMode(D4, OUTPUT); 
  // pinMode(BUILTIN_LED, OUTPUT); 

  Request_getSysInfo c;
  requestQueue.queue.push(c);


  
  // initialize random seed 
  randomSeed(analogRead(D0));
  

  wifi.connect();
}

void loop(void) {
  delay(250);
  p("\nLooping, ram: %d\n", system_get_free_heap_size());

  if (!requestQueue.queue.empty()) {
    p("Process queue, %d requests\n", requestQueue.queue.size());
    requestQueue.executeQueue(responseQueue);
  }

  if (!responseQueue.queue.empty()) {
    String response;
    while (!responseQueue.queue.empty()) {
      Response &rs = responseQueue.queue.front();
      response+= rs.toJson();

      p(">> %s\n", response.c_str());
      
      responseQueue.queue.pop();
    }
  }

  while(random(100)<70) {
    p("+push new elements\n");

    if (random(100)<25) {
      Request_getHeartbeat c;
      requestQueue.queue.push(c);
    }
    else {
      Request_getSysInfo c;
      requestQueue.queue.push(c);
    }
  }
}

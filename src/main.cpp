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

  pinMode(D4, OUTPUT); 
  digitalWrite(D4, HIGH);


  pinMode(BUILTIN_LED, OUTPUT); 
  digitalWrite(BUILTIN_LED, HIGH);

 
  // initialize random seed 
  randomSeed(analogRead(D0));
}

void loop(void) {
  delay(100);
  p("\nLooping, ram: %d\n", system_get_free_heap_size());


  if (!requestQueue.queue.empty()) {
    p("Process queue, %d requests\n", requestQueue.queue.size());
    requestQueue.executeQueue(&responseQueue);
    p("Processed queue, %d responses\n", responseQueue.queue.size());
  }

  if (!responseQueue.queue.empty()) {
    String response;
    p("------------------");
    while (!responseQueue.queue.empty()) {
      Response *rs = responseQueue.queue.front();
      response+= rs->toJson();

      responseQueue.queue.pop();
      delete rs;
    }
    p(">>>>    %s\n", response.c_str());
  }


  // fill in request queue for next iteration
  // p("+push new elements\n");
  while(random(100)<30) {
    if (random(100)<25) {
      Request_getHeartbeat* c = new Request_getHeartbeat();
      requestQueue.queue.push(c);
      p("  >    %s\n", "Request_getHeartbeat");
    }
    else if (random(100)<25) {
      Request_getWifiList* c = new Request_getWifiList();
      requestQueue.queue.push(c);
      p("  >    %s\n", "Request_getWifiList");
    }
    else if (random(100)<25) {
      Request_lightOn* c = new Request_lightOn();
      c->location = 1;
      c->power = random(0, 255);
      requestQueue.queue.push(c);
      p("  >    %s, %d, %d\n", "Request_lightOn", c->location, c->power);
    }
    else if (random(100)<25) {
      Request_lightOn* c = new Request_lightOn();
      c->location = 2;
      c->power = random(0, 255);
      requestQueue.queue.push(c);
      p("  >    %s, %d, %d\n", "Request_lightOn", c->location, c->power);
    }
    else if (random(100)<25) {
      Request_lightOff* c = new Request_lightOff();
      c->location = 1;
      requestQueue.queue.push(c);
      p("  >    %s, %d\n", "Request_lightOff", c->location);
    }
    else if (random(100)<25) {
      Request_lightOff* c = new Request_lightOff();
      c->location = 2;
      requestQueue.queue.push(c);
      p("  >    %s, %d\n", "Request_lightOff", c->location);
    }
    else if (random(100)<25) {
      Request_getSysInfo* c = new Request_getSysInfo();
      requestQueue.queue.push(c);
      p("  >    %s\n", "Request_getSysInfo");
    }
  }
}

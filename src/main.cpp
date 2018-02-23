#include <Arduino.h>
#include <queue>
#include <stdarg.h>
#include <string.h>
#include "Command.h"
#include "Response.h"
#include "Request.h"

#define WIFI_SSID "xxxx";
#define WIFI_PASSWORD "xxxx";

// printf replacement
void p(const char *fmt, ... ) {
  char buf[256]; // resulting string limited in size
  va_list args;
  va_start (args, fmt );
  vsnprintf(buf, 256, fmt, args);
  va_end (args);
  Serial.print(buf);
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

int freq = 1000;
float mul = 0.75;
void setup(void) {
  Serial.begin(921600);

  // name comes from https://en.wikipedia.org/wiki/Butler
  p("************************************************************\n");
  p("Starting up Boutellier");

  // queue.reset();
  // queue.append();
  pinMode(D4, OUTPUT); 
  pinMode(BUILTIN_LED, OUTPUT); 

  Request_getSysInfo c;
  requestQueue.queue.push(c);


  
  // initialize random seed 
  randomSeed(analogRead(D0));
  

  wifi.connect();
}

void loop(void) {
  delay(freq);
  digitalWrite(D4, LOW);
  digitalWrite(BUILTIN_LED, HIGH);

  p("Looping");

  delay(freq);                      
  digitalWrite(D4, HIGH);  
  digitalWrite(BUILTIN_LED, LOW);

  freq = freq*mul;

  if (freq<50) {
    mul = 1/mul;
    freq = 50;
  }
  if (freq>1000) {
    mul = 1/mul;
    freq = 1000;

    if (random(100)<50) {
      mul+= random(100)/1000;
    }
  }
}


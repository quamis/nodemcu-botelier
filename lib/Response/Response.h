#ifndef _NODE_BOTELIERLIB_RESPONSE_
#define _NODE_BOTELIERLIB_RESPONSE_

#include <Arduino.h>
#include <queue>
#include <string.h>


class Response {
  public:
    virtual String toJson();
    virtual ~Response() {};
  
  protected:
    String jsKeyStr(char* key, char* str) {
      return String(key) + "\"" + String(str) + "\"";
    }
};

class Response_heartbeat : public Response {
  public:
    virtual String toJson();
    uint commandsExecuted = 0;
};

class Response_sysInfo : public Response {
  public:
    virtual String toJson();
    time_t time = 0;
    uint32_t free_heap_size = 0;
};


class WifiAp {
  public:
    // @see https://github.com/esp8266/Arduino/blob/4897e0006b5b0123a2fa31f67b14a3fff65ce561/doc/esp8266wifi/scan-class.md
    String SSID;
    String encryptionType;
    int32_t RSSI;
    String BSSID;
    int32_t channel;
    bool isHidden;
};

class Response_wifiList : public Response {
  public:
    virtual String toJson();

    std::queue<WifiAp *> networks;

    virtual ~Response_wifiList() {
      while (!networks.empty()) {
        WifiAp *ap = networks.front();
        networks.pop();
        delete ap;
      }
    }
};







class ResponseQueue {
  public:
    std::queue<Response*> queue;
};

#endif
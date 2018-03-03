#ifndef _NODE_BOTELIERLIB_COMMANDS_
#define _NODE_BOTELIERLIB_COMMANDS_

#include <Arduino.h>
#include "Response.h"
#include "Request.h"

class Command {
    public:
        Command() { };
        void execute(ResponseQueue responseQueue);
};


class Command_getHeartbeat : public Command {
  public:
    //using Command::execute;
    void execute(ResponseQueue responseQueue, uint commandsExecuted);
};

class Command_getSysInfo : public Command {
  public:
    using Command::execute;
    void execute(ResponseQueue responseQueue);
};

class Command_lightOn : public Command {
  public:
    using Command::execute;
    void execute(ResponseQueue responseQueue);

    Request_lightOn* rq = NULL;
};

class Command_lightOff : public Command {
  public:
    using Command::execute;
    void execute(ResponseQueue responseQueue);

    Request_lightOff* rq = NULL;
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

class Command_getWifiList : public Command {
  public:
    using Command::execute;
    void execute(ResponseQueue responseQueue);

    std::queue<WifiAp *> networks;

    ~Command_getWifiList() {
      while (!networks.empty()) {
        WifiAp *ap = networks.front();
        networks.pop();
        delete ap;
      }
    }
};



#endif
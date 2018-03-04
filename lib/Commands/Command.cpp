#include <Arduino.h>
#include <sys/time.h>
#include "stdexcept"
#include "Utils.h"
#include "Command.h"
#include "Response.h"
#include "Request.h"

#include "ESP8266WiFi.h"

extern "C" {
  #include "user_interface.h"
}

void Command::execute(ResponseQueue *responseQueue) {
}

void Command_getHeartbeat::execute(ResponseQueue *responseQueue, uint commandsExecuted) {
    Response_heartbeat* rs = new Response_heartbeat();
    rs->commandsExecuted = commandsExecuted;
    responseQueue->queue.push(rs);
}


void Command_getSysInfo::execute(ResponseQueue *responseQueue) {
    Response_sysInfo* rs = new Response_sysInfo();

    struct timeval now;
    if (gettimeofday(&now, NULL)==0) {
        rs->time = now.tv_sec;
    }

    rs->free_heap_size = system_get_free_heap_size();

    responseQueue->queue.push(rs);
}


void Command_wait::execute(ResponseQueue *responseQueue) {
    delay(rq->duration*1000);
}


void Command_lightOn::execute(ResponseQueue *responseQueue) {
    switch (rq->location) {
        case 1:
            digitalWrite(BUILTIN_LED, LOW);
        break;
        case 2:
            digitalWrite(D4, LOW);
        break;
    }
}

void Command_lightOff::execute(ResponseQueue *responseQueue) {
    switch (rq->location) {
        case 1:
            digitalWrite(BUILTIN_LED, HIGH);
        break;
        case 2:
            digitalWrite(D4, HIGH);
        break;
    }
}

void Command_getWifiList::execute(ResponseQueue *responseQueue) {
    // @see https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiScan/WiFiScan.ino
    //  @see http://esp8266.github.io/Arduino/versions/2.1.0-rc1/doc/libraries.html
    //  @see https://github.com/esp8266/Arduino/blob/4897e0006b5b0123a2fa31f67b14a3fff65ce561/doc/esp8266wifi/scan-class.md#bssid
    
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks(false, true);
    Response_wifiList* rs = new Response_wifiList();

    for (int i = 0; i < n; ++i) {
        WifiAp *ap = new WifiAp();        
        ap->SSID = WiFi.SSID(i);
        switch (WiFi.encryptionType(i)) {
            case ENC_TYPE_WEP:      ap->encryptionType = "WEP";break;
            case ENC_TYPE_TKIP:     ap->encryptionType = "WPA/PSK";break;
            case ENC_TYPE_CCMP:     ap->encryptionType = "WPA2/PSK";break;
            case ENC_TYPE_NONE:     ap->encryptionType = "open network";break;
            case ENC_TYPE_AUTO:     ap->encryptionType = "WPA/WPA2/PSK (auto)";break;
            default:                ap->encryptionType = "(uknown)";break;
        }
        
        ap->RSSI = WiFi.RSSI(i);
        ap->BSSID = WiFi.BSSIDstr(i);
        ap->channel = WiFi.channel(i);
        ap->isHidden = WiFi.isHidden(i);
        rs->networks.push(ap);

        /*
        p("Command_getWifiList: %s(%s), %d dBm, %s/ ch%d, %s\n"
            , ap->SSID.c_str()
            , ap->encryptionType.c_str()
            , ap->RSSI
            , ap->BSSID.c_str()
            , ap->channel
            , (ap->isHidden?"hidden":"visible")
        );
        */
    }

    WiFi.mode(WIFI_OFF);
    responseQueue->queue.push(rs);
}

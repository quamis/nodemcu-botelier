#include "string.h"

#include "Utils.h"
#include "Response.h"

String Response::toJson() {
    String s;
    return s;
}

String Response_heartbeat::toJson() {
    String s;
    return s;
}

String Response_sysInfo::toJson() {
    // fill in something in the reponse
    // Command::execute(responseQueue);
    String s;
    return s;
}

String Response_wifiList::toJson() {
    String s;
    s+= "{networks: {";
    String sep = "";
    while (!networks.empty()) {
        String sap;
        WifiAp *ap = networks.front();

        sap+= sep+"{";
        sap+= fmt("  SSID:\"%s\"", ap->SSID.c_str());
        sap+= fmt(", encryptionType:\"%s\"", ap->encryptionType.c_str());
        sap+= fmt(", RSSI:%d", ap->RSSI);
        sap+= fmt(", BSSID:\"%s\"", ap->BSSID.c_str());
        sap+= fmt(", channel:%d", ap->channel);
        sap+= fmt(", isHidden:%s", (ap->isHidden?"true":"false"));
        sap+= "}";

        networks.pop();
        delete ap;
        s+=sap;

        sep=", ";
    }
    s+="}";

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
    return s;
}
// TODO
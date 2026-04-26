#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WiFi.h>

class WifiManager {
private:
    const char* _SSID;
    const char* _MDP_WIFI;

public:
    WifiManager(const char* SSID, const char* MDP_WIFI);
    void begin();
    bool isConnected();
};

#endif
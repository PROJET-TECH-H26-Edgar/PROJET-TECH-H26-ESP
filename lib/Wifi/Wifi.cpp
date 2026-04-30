#include "WifiManager.h"

WifiManager::WifiManager(const char* SSID, const char* MDP_WIFI)
    : _SSID(SSID), _MDP_WIFI(MDP_WIFI){}

void WifiManager::begin() {
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);
    WiFi.begin(_SSID, _MDP_WIFI);

    Serial.print("Connexion WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connecté !");
}

bool WifiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}
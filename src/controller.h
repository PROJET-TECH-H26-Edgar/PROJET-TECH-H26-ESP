#include <Arduino.h>
#include "WifiManager.h"
#include "Mqtt.h"
#include "Solenoide.h"
#include "RFID.h"

#define MAX_SOLENOIDES 5

class Controller {
public:
    Controller(
        const char* ssid,
        const char* password,
        const char* mqttServer,
        int mqttPort,
        const char* mqttUser,
        const char* mqttPassword
    );

    void begin();
    void loop();

private:
    WifiManager _wifi;
    MqttConn _mqtt;

    Solenoide* _solenoides[MAX_SOLENOIDES];
    RFID _rfid;

    void handleMqttMessage(const char* topic, const char* message);
    void sendUID(const String& uid);
};
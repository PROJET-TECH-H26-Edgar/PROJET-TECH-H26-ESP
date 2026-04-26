#include <Arduino.h>
#include "WifiManager.h"
#include "Mqtt.h"
#include "Solenoide.h"
#include "RFID.h"

#define MAX_SOLENOIDES 5
#define SOLENOIDE_PORTE 4
#define SOLENOIDE1 12
#define SOLENOIDE2 16
#define SOLENOIDE3 17
#define SOLENOIDE4 5

const char* SSID        = "iPhone de Edgar ";
const char* MDP_WIFI    = "edgar1011";
const char* MQTT_SERVER = "138.68.23.149";
const int   MQTT_PORT   = 8883;
const char* MQTT_USER   = "apiuser";
const char* MQTT_MDP    = "ApiPass10!";

WifiManager wifi(SSID, MDP_WIFI);
MqttConn    mqttConn(wifi, MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_MDP);

Solenoide* solenoides[MAX_SOLENOIDES];
RFID rfid;

void sendUID(const String& uid) {
    mqttConn.publish("distributeur/rfid", uid.c_str());
}

void setup() {
    Serial.begin(115200);
    mqttConn.begin();

    solenoides[0] = new Solenoide(SOLENOIDE_PORTE);
    solenoides[1] = new Solenoide(SOLENOIDE1);
    solenoides[2] = new Solenoide(SOLENOIDE2);
    solenoides[3] = new Solenoide(SOLENOIDE3);
    solenoides[4] = new Solenoide(SOLENOIDE4);

    for (int i = 0; i < MAX_SOLENOIDES; i++) {
        solenoides[i]->begin();
    }

    rfid.begin();

    mqttConn.onMessage([](const char* topic, const char* message) {
        int separateur = String(message).indexOf(';');
        if (separateur > 0) {
            int numero    = String(message).substring(0, separateur).toInt();
            String action = String(message).substring(separateur + 1);

            if (numero >= 0 && numero < MAX_SOLENOIDES) {
                if (action == "ouvrir") {
                    solenoides[numero]->open();
                    solenoides[0]->openDoor();
                } else if (action == "fermer") {
                    solenoides[numero]->close();
                }
            }
        }
    });
}

void loop() {
    mqttConn.loop();
    delay(50);

    bool wasActive = false;
    for (int i = 0; i < MAX_SOLENOIDES; i++) {
        bool before = solenoides[i]->getIsActive();
        solenoides[i]->update();
        if (before && !solenoides[i]->getIsActive()) {
            wasActive = true;
        }
    }
    if (wasActive) rfid.reset();

    if (rfid.isCardPresent()) {
        String uid = rfid.getCardUID();
        Serial.println("RFID 1 : " + uid);
        sendUID(uid);
        delay(300);
    }
}
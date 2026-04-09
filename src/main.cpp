#include <Arduino.h>
#include "Mqtt.h"
#include "Solenoide.h"
#include "RFID.h"

#define MAX_SOLENOIDES 4

// const char * ssid = "iPhone de Edgar";
// const char* user_wifi = "2435196";
// const char * mdp_wifi = "S4Pf!qy0";
const char * ssid = "iPhone de Edgar ";
// const char* user_wifi = "2435196";
const char * mdp_wifi = "edgar1011";

const char* mqtt_serveur = "138.68.23.149";
const int mqtt_port = 8883;

const char* mqtt_user = "apiuser";
const char* mqtt_mdp = "ApiPass10!";

Solenoide* solenoides[MAX_SOLENOIDES];
RFID rfid;

// MqttConn mqttConn(ssid,
//                  user_wifi,
//                  mdp_wifi,
//                  mqtt_serveur,
//                  mqtt_port,
//                  mqtt_user,
//                  mqtt_mdp);
MqttConn mqttConn(ssid,
                 mdp_wifi,
                 mqtt_serveur,
                 mqtt_port,
                 mqtt_user,
                 mqtt_mdp);

void sendUID(const String& uid) {
    mqttConn.publish("distributeur/rfid", uid.c_str());
}

void setup() {
    mqttConn.begin();

    solenoides[0] = new Solenoide(2);
    solenoides[1] = new Solenoide(4);
    solenoides[2] = new Solenoide(16);
    solenoides[3] = new Solenoide(17);

    for (int i = 0; i < MAX_SOLENOIDES; i++) {
      solenoides[i]->begin();
    }

  rfid.begin();

  mqttConn.onMessage([](const char* topic, const char* message) {
    int separateur = String(message).indexOf(';');
    if (separateur > 0) {
      int numero = String(message).substring(0, separateur).toInt();
      String action = String(message).substring(separateur + 1);

      if (numero >= 0 && numero < MAX_SOLENOIDES) {
        if (action == "ouvrir")
        { 
          solenoides[numero]->open();
        }
        else if (action == "fermer") solenoides[numero]->close();
      }
    }
  });
  
}

void loop() {
    mqttConn.loop();

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
        Serial.println("Carte détectée : " + uid);
        sendUID(uid);
    }
}
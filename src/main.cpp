#include <Arduino.h>
#include "MqttConn.h"
#include "Solenoide.h"
#include "RFID.h"

#define MAX_SOLENOIDES 4

const char * ssid = "CegepRDL";
const char* user_wifi = "2435196";
const char * mdp_wifi = "S4Pf!qy0";

const char* mqtt_serveur = "138.68.23.149";
const int mqtt_port = 8883;

const char* mqtt_user = "apiuser";
const char* mqtt_mdp = "ApiPass10!";

Solenoide* solenoides[MAX_SOLENOIDES];
RFID rfid;

MqttConn mqttConn(ssid,
                 user_wifi,
                 mdp_wifi,
                 mqtt_serveur,
                 mqtt_port,
                 mqtt_user,
                 mqtt_mdp);

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
        if (action == "ouvrir") solenoides[numero]->ouvrir(5000);
        else if (action == "fermer") solenoides[numero]->fermer();
      }
    }
  });
}

void loop() {
    mqttConn.loop();

      
    for (int i = 0; i < MAX_SOLENOIDES; i++) {
    solenoides[i]->update();
  }

    if (rfid.isCardPresent()) {
      String uid = rfid.getCardUID();
      Serial.println("Carte détectée : " + uid);
    }
}
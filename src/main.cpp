#include <Arduino.h>
#include "Mqtt.h"
#include "Solenoide.h"
#include "RFID.h"

#define MAX_SOLENOIDES 5

// const char * SSID = "iPhone de Edgar";
// const char* USER_WIFI = "2435196";
// const char * MDP_WIFI = "S4Pf!qy0";
const char * SSID = "iPhone de Edgar ";
const char * MDP_WIFI = "edgar1011";

const char* MQTT_SERVER = "138.68.23.149";
const int MQTT_PORT = 8883;

const char* MQTT_USER = "apiuser";
const char* MQTT_MDP = "ApiPass10!";

Solenoide* solenoides[MAX_SOLENOIDES];
RFID rfid;

// MqttConn mqttConn(SSID,
//                  USER_WIFI
//                  MDP_WIFI,
//                  MQTT_SERVER,
//                  MQTT_PORT,
//                  MQTT_USER,
//                  MQTT_MDP);
MqttConn mqttConn(SSID,
                 MDP_WIFI,
                 MQTT_SERVER,
                 MQTT_PORT,
                 MQTT_USER,
                 MQTT_MDP);

void sendUID(const String& uid) {
    mqttConn.publish("distributeur/rfid", uid.c_str());
}

void setup() {
    mqttConn.begin();

    solenoides[0] = new Solenoide(4);
    solenoides[1] = new Solenoide(12);
    solenoides[2] = new Solenoide(16);
    solenoides[3] = new Solenoide(17);
    solenoides[4] = new Solenoide(5);

    for (int i = 0; i < MAX_SOLENOIDES; i++) {
      solenoides[i]->begin();
    }

  rfid.begin();
    // aide de l'ia pour decoder mon message mqtt
    //l'ai ma donner un exemple et j'ai écrit le code moi même
  mqttConn.onMessage([](const char* topic, const char* message) {
    int separateur = String(message).indexOf(';');
    if (separateur > 0) {
      int numero = String(message).substring(0, separateur).toInt();
      String action = String(message).substring(separateur + 1);

      if (numero >= 0 && numero < MAX_SOLENOIDES) {
        if (action == "ouvrir")
        { 
          solenoides[numero]->open();
          solenoides[0]->openDoor();
        }
        else if (action == "fermer") solenoides[numero]->close();
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
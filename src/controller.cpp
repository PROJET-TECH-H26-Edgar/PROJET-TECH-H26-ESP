#include "Controller.h"

#define SOLENOIDE_PORTE 4
#define SOLENOIDE1 12
#define SOLENOIDE2 16
#define SOLENOIDE3 17
#define SOLENOIDE4 5

Controller::Controller(
    const char* ssid,
    const char* password,
    const char* mqttServer,
    int mqttPort,
    const char* mqttUser,
    const char* mqttPassword
)
: _wifi(ssid, password),
  _mqtt(_wifi, mqttServer, mqttPort, mqttUser, mqttPassword)
{}

void Controller::begin() {
    Serial.begin(115200);
    _mqtt.begin();

    _solenoides[0] = new Solenoide(SOLENOIDE_PORTE);
    _solenoides[1] = new Solenoide(SOLENOIDE1);
    _solenoides[2] = new Solenoide(SOLENOIDE2);
    _solenoides[3] = new Solenoide(SOLENOIDE3);
    _solenoides[4] = new Solenoide(SOLENOIDE4);

    for (int i = 0; i < MAX_SOLENOIDES; i++) {
        _solenoides[i]->begin();
    }

    _rfid.begin();

    _mqtt.onMessage([this](const char* topic, const char* message) {
        handleMqttMessage(topic, message);
});
}

void Controller::loop() {
    _mqtt.loop();
    delay(50);

    bool wasActive = false;

    for (int i = 0; i < MAX_SOLENOIDES; i++) {
        bool before = _solenoides[i]->getIsActive();
        _solenoides[i]->update();

        if (before && !_solenoides[i]->getIsActive()) {
            wasActive = true;
        }
    }

    if (wasActive) {
        _rfid.reset();
    }

    if (_rfid.isCardPresent()) {
        String uid = _rfid.getCardUID();
        Serial.println("RFID : " + uid);
        sendUID(uid);
        delay(300);
    }
}

void Controller::handleMqttMessage(const char* topic, const char* message) {
    int separateur = String(message).indexOf(';');

    if (separateur > 0) {
        int numero = String(message).substring(0, separateur).toInt();
        String action = String(message).substring(separateur + 1);

        if (numero >= 0 && numero < MAX_SOLENOIDES) {
            if (action == "ouvrir") {
                _solenoides[numero]->open();
                _solenoides[0]->openDoor();
            } 
            else if (action == "fermer") {
                _solenoides[numero]->close();
            }
        }
    }
}

void Controller::sendUID(const String& uid) {
    _mqtt.publish("distributeur/rfid", uid.c_str());
}
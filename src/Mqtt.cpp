#include "Mqtt.h"

MessageCallback MqttConn::_userCallback = nullptr;

MqttConn::MqttConn(WifiManager& wifi, const char* MQTT_SERVER, int PORT,
                   const char* MQTT_USER, const char* MQTT_MDP)
    : _wifi(wifi),
      _MQTT_SERVER(MQTT_SERVER),
      _port(PORT),
      _MQTT_USER(MQTT_USER),
      _MQTT_MDP(MQTT_MDP)
{}

void MqttConn::begin() {
    _wifi.begin();

    _secureClient.setInsecure();
    _client.setClient(_secureClient);
    _client.setServer(_MQTT_SERVER, _port);
    _client.setCallback(_callback);
}

void MqttConn::reconnect() {
    while (!_client.connected()) {
        if (_client.connect("ESP32_Client", _MQTT_USER, _MQTT_MDP)) {
            Serial.println("MQTTS connecté !");
            _client.subscribe("distributeur/cle");
        } else {
            Serial.println("Erreur de connexion au MQTT");
            delay(5000);
        }
    }
}

void MqttConn::loop() {
    if (!_client.connected()) reconnect();
    _client.loop();
}

void MqttConn::publish(const char* topic, const char* message) {
    _client.publish(topic, message);
}

void MqttConn::onMessage(MessageCallback cb) {
    _userCallback = cb;
}

void MqttConn::_callback(char* topic, byte* payload, unsigned int length) {
    char message[length + 1];
    memcpy(message, payload, length);
    message[length] = '\0';

    Serial.println("Message reçu: " + String(message));

    if (_userCallback) _userCallback(topic, message);
}
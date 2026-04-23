#include "Mqtt.h"

// MqttConn::MqttConn(const char* ssid,const char * user_wifi, const char* mdp_wifi, const char* mqtt_serveur, int port, const char* mqtt_user, const char* mqtt_mdp) : 
//     _ssid(ssid),
//     _user_wifi(user_wifi),
//     _mdp_wifi(mdp_wifi),
//     _mqtt_serveur(mqtt_serveur),
//     _port(port),
//     _mqtt_user(mqtt_user),
//     _mqtt_mdp(mqtt_mdp),
//     _client(_secureClient) {};
MqttConn::MqttConn(const char* ssid, const char* mdp_wifi, const char* mqtt_serveur, int port, const char* mqtt_user, const char* mqtt_mdp) : 
    _ssid(ssid),
    _mdp_wifi(mdp_wifi),
    _mqtt_serveur(mqtt_serveur),
    _port(port),
    _mqtt_user(mqtt_user),
    _mqtt_mdp(mqtt_mdp),
    _client(_secureClient) {};
    
    
void MqttConn::begin() {
    Serial.begin(115200);
    setupWifi();

    _secureClient.setInsecure();
    _client.setServer(_mqtt_serveur, _port);
    _client.setCallback(MqttConn::callback); 
    }


void MqttConn::setupWifi() {
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);

    // esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)_user_wifi, strlen(_user_wifi));
    // esp_wifi_sta_wpa2_ent_set_username((uint8_t *)_user_wifi, strlen(_user_wifi));
    // esp_wifi_sta_wpa2_ent_set_password((uint8_t *)_mdp_wifi, strlen(_mdp_wifi));

    // esp_wifi_sta_wpa2_ent_enable();

    WiFi.begin(_ssid, _mdp_wifi);

    Serial.print("Connexion WiFi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi connecté !");
}


void MqttConn::reconnect() {
    while (!_client.connected()) {

        if (_client.connect("ESP32_Client",_mqtt_user,_mqtt_mdp)) {

        Serial.println("MQTTS connecté !");
        _client.subscribe("distributeur/cle");

        } else {
        Serial.println("Erreur de connexion au MQTT");
        delay(5000);
        }
    }
}

void MqttConn::loop() {
    if (!_client.connected()) {
        reconnect();
    }
    _client.loop();
}

void MqttConn::publish(const char* topic, const char* message) {
    _client.publish(topic, message);
}

MessageCallback MqttConn::_userCallback = nullptr;


void MqttConn::onMessage(MessageCallback cb) {
    _userCallback = cb;
}

void MqttConn::callback(char* topic, byte* payload, unsigned int length) {
    String message;
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.println("Message reçu: " + message);

    // Appelle le callback utilisateur si défini
    if (_userCallback) {
        _userCallback(topic, message.c_str());
    }
}


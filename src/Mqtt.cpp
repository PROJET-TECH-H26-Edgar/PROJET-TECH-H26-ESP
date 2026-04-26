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
MqttConn::MqttConn(const char* SSID, const char* MDP_WIFI, const char* MQTT_SERVER, int PORT, const char* MQTT_USER, const char* MQTT_MDP) :
    _SSID(SSID),
    _MDP_WIFI(MDP_WIFI),
    _MQTT_SERVER(MQTT_SERVER),
    _port(PORT),
    _MQTT_USER(MQTT_USER),
    _MQTT_MDP(MQTT_MDP),
    _client(_secureClient)
{}
    
    
void MqttConn::begin() {
    Serial.begin(115200);
    setupWifi();

    _secureClient.setInsecure();
    _client.setServer(_MQTT_SERVER, _port);
    _client.setCallback(MqttConn::callback); 
    }


void MqttConn::setupWifi() {
    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);

    // esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)_user_wifi, strlen(_user_wifi));
    // esp_wifi_sta_wpa2_ent_set_username((uint8_t *)_user_wifi, strlen(_user_wifi));
    // esp_wifi_sta_wpa2_ent_set_password((uint8_t *)_mdp_wifi, strlen(_mdp_wifi));

    // esp_wifi_sta_wpa2_ent_enable();

    WiFi.begin(_SSID, _MDP_WIFI);

    Serial.print("Connexion WiFi");
    //petite boucle par chat gpt pour savoir si la connexion est en cours car je ne savais jamais si ca marchait
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi connecté !");
}


void MqttConn::reconnect() {
    while (!_client.connected()) {

        if (_client.connect("ESP32_Client",_MQTT_USER,_MQTT_MDP)) {

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

#if defined(ESP8266) || defined(ESP32)
    std::function<void(char*, uint8_t*, unsigned int)> MqttConn::callback = nullptr;
#else
    void (*MqttConn::callback)(char*, uint8_t*, unsigned int) = nullptr;
#endif

void MqttConn::onMessage(MQTT_CALLBACK_SIGNATURE) {
    MqttConn::callback = callback;
}

void MqttConn::_internalCallback(char* topic, byte* payload, unsigned int length) {
    String message;
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.println("Message reçu: " + message);

    // Appelle le callback utilisateur si défini
    if (callback) {
        callback(topic, (uint8_t*)payload, length);
    }
}


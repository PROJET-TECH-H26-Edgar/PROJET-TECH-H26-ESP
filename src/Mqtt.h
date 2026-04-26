#ifndef MQTTCONN_H
#define MQTTCONN_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// Type de callback pour notifier le main Arduino (donné par l'ia)
typedef void (*MessageCallback)(const char* topic, const char* message);

class MqttConn {

    private:
    void setupWifi();
    void reconnect();
    static MQTT_CALLBACK_SIGNATURE;
    static void _internalCallback(char* topic, byte* payload, unsigned int length);
    const char* _SSID;
    // const char * _USER_WIFI;
    const char* _MDP_WIFI;
    int _port;
    const char* _MQTT_SERVER;
    const char* _MQTT_USER;
    const char* _MQTT_MDP;
    int _mqtt_port;

    WiFiClientSecure _secureClient;
    PubSubClient _client;
   
    public: 
   // MqttConn(const char* SSID, cont char* USER_WIFI, const char* MDP_WIFI, const char* MQTT_SERVER, int PORT, const char* MQTT_USER, const char* MQTT_MDP);
    MqttConn(const char* SSID, const char* MDP_WIFI, const char* MQTT_SERVER, int PORT, const char* MQTT_USER, const char* MQTT_MDP);
    void begin();
    void loop();
    void publish(const char* TOPIC, const char* MESSAGE);
    void onMessage(MQTT_CALLBACK_SIGNATURE cb);
};


#endif
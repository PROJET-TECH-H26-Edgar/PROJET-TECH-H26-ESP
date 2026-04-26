#ifndef MQTTCONN_H
#define MQTTCONN_H

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "WifiManager.h"

#include <functional>

typedef std::function<void(const char*, const char*)> MessageCallback;

class MqttConn {
private:
    WifiManager& _wifi;
    const char* _MQTT_SERVER;
    int _port;
    const char* _MQTT_USER;
    const char* _MQTT_MDP;

    WiFiClientSecure _secureClient;
    PubSubClient _client;

    static MqttConn* _instance;
    static MessageCallback _userCallback;
    
    void reconnect();

public:
    MqttConn(WifiManager& wifi, const char* MQTT_SERVER, int PORT,
             const char* MQTT_USER, const char* MQTT_MDP);

    void begin();
    void loop();
    static void _callback(char* topic, byte* payload, unsigned int length);
    void publish(const char* topic, const char* message);
    void onMessage(MessageCallback cb);
};

#endif
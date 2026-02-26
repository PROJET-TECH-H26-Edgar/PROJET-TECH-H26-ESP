#ifndef MQTTCONN_H
#define MQTTCONN_H

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

class MqttConn {

    public: 
    MqttConn(const char* ssid, const char* mdp_wifi, const char* mqtt_serveur, int port, const char* mqtt_user, const char* mqtt_mdp, const char* ca_cert);
    void begin();
    void loop();
    void publish(const char* topic, const char* message);

    private:
    void setupWifi();
    void reconnect();
    static void callbackk(char* topic, byte* payload, unsigned int length);
    const char* _ssid;
    const char* _wifi_password;
    const char* _mqtt_server;
    const char* _mqtt_user;
    const char* _mqtt_password;
    const char* _ca_cert;
    int _mqtt_port;

    WiFiClientSecure _secureClient;
    PubSubClient _client;

};


#endif
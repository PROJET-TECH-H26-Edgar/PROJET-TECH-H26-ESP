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
    static void callback(char* topic, byte* payload, unsigned int length);
    const char* _ssid;
    // const char * _user_wifi;
    const char* _mdp_wifi;
    int _port;
    const char* _mqtt_serveur;
    const char* _mqtt_user;
    const char* _mqtt_mdp;
    int _mqtt_port;

    WiFiClientSecure _secureClient;
    PubSubClient _client;
    static MessageCallback _userCallback; // callback défini par le main (donné par l'ia)

    public: 
    // MqttConn(const char* ssid,const char* user_wifi, const char* mdp_wifi, const char* mqtt_serveur, int port, const char* mqtt_user, const char* mqtt_mdp);
    MqttConn(const char* ssid, const char* mdp_wifi, const char* mqtt_serveur, int port, const char* mqtt_user, const char* mqtt_mdp);
    void begin();
    void loop();
    void publish(const char* topic, const char* message);
    void onMessage(MessageCallback cb);
};


#endif
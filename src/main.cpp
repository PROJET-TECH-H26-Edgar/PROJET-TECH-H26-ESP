#include <Arduino.h>
#include "Controller.h"

const char* SSID        = "iPhone de Edgar ";
const char* MDP_WIFI    = "edgar1011";
const char* MQTT_SERVER = "138.68.23.149";
const int   MQTT_PORT   = 8883;
const char* MQTT_USER   = "apiuser";
const char* MQTT_MDP    = "ApiPass10!";

Controller controller(
    SSID,
    MDP_WIFI,
    MQTT_SERVER,
    MQTT_PORT,
    MQTT_USER,
    MQTT_MDP
);

void setup() {
    controller.begin();
}

void loop() {
    controller.loop();
}
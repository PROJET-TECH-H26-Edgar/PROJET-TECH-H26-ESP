# Code de l'esp pour le distributeur de clé

## Mise en place :

### Avoir PlatformIO

### Si besoin installation des bibliothéques suivantes

- PubSubClient
- MFRC522

### Modifier les paramètres de connexion dans le fichier main.cpp

- Information de connexion WIFI
  Il n'est pas possible d'utiliser une réseau d'entreprise avec un nom d'utilisateur.
  ```bash
  const char* SSID = "Votre nom de réseau ";
  const char* MDP_WIFI = "Votre mot de passe";
  ```

- Serveur MQTT
  ```bash
  const char* MQTT_SERVER = "Ip de votre serveur MQTT";
  const int MQTT_PORT = 8883; (Port du mqtts normalement inchangé)
  const char* MQTT_USER = "Votre nom d'utilisateur pour le mqtt";
  const char\* MQTT_MDP = "Votre mot de passe pour le mqtt";
  ```
### Compiler le projet dans votre ESP32 du système

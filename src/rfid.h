#ifndef RFID_H
#define RFID_H
 
#include <SPI.h>
#include <MFRC522.h>
 
// Brochages ESP32
#define RST_PIN 21
#define SS_PIN  5
 
class RFID {
public:
    RFID();
    void begin();
    bool isCardPresent();
    String getCardUID();
    void reset();
    void sendUID();
 
private:
    MFRC522 mfrc522;
};
 
#endif
 
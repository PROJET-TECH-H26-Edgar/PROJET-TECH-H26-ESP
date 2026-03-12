#ifndef RFID_H
#define RFID_H
 
#include <SPI.h>
#include <MFRC522.h>
 
// Brochages ESP32
#define RST_PIN 22
#define SS_PIN  21
 
class RFID {
public:
    RFID();
    void begin();
    bool isCardPresent();
    String getCardUID();
 
private:
    MFRC522 mfrc522;
};
 
#endif
 
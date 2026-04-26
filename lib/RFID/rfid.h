#ifndef RFID_H
#define RFID_H
 
#include <SPI.h>
#include <MFRC522.h>
 
#define SS 2
#define RST 21
#define SCK 18
#define MISO 19
#define MOSI 23

class RFID {
public:
    RFID();
    void begin();
    bool isCardPresent();
    String getCardUID();
    void reset();
    void sendUID();
    void setActive(int reader);
 
private:
    MFRC522 rfid;
};
 
#endif
 
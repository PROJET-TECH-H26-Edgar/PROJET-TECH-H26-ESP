#include "RFID.h"
 
RFID::RFID() : mfrc522(SS_PIN, RST_PIN) {}
 
void RFID::begin() {
    SPI.begin();
    mfrc522.PCD_Init();
    byte version = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
    Serial.print("Version MFRC522 : 0x");
    Serial.println(version, HEX);
    Serial.println("Lecteur RFID initialisé.");
}
 
bool RFID::isCardPresent() {
    return mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial();
}
 
String RFID::getCardUID() {
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
        if (mfrc522.uid.uidByte[i] < 0x10) uid += "0";
        uid += String(mfrc522.uid.uidByte[i], HEX);
        if (i < mfrc522.uid.size - 1) uid += ":";
    }
    uid.toUpperCase();
    mfrc522.PICC_HaltA();
    return uid;
}
 
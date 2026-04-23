#include "RFID.h"

RFID::RFID(): rfid(SS, RST) {}

void RFID::begin() {
    SPI.begin(18, 19, 23);

    rfid.PCD_Init();


    Serial.println("RFID initialisé");
}

bool RFID::isCardPresent() {
    return rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial();
}

String RFID::getCardUID() {
    //aide de l'ia pour le lecture de la carte rfid
    String uid = "";

    for (byte i = 0; i < rfid.uid.size; i++) {
        if (rfid.uid.uidByte[i] < 0x10) uid += "0";
        uid += String(rfid.uid.uidByte[i], HEX);
        if (i < rfid.uid.size - 1) uid += ":";
    }

    uid.toUpperCase();

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();

    return uid;
}

void RFID::reset() {
    rfid.PCD_Reset();
}
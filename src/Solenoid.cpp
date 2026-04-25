#include "Solenoide.h"

#define ETAT_VERROUILLE LOW   
#define ETAT_OUVERT HIGH 

Solenoide::Solenoide(uint8_t pin):
    pin(pin),
    tempsDebut(0),
    duree(0),
    isActive(false) {}

void Solenoide::begin() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, ETAT_VERROUILLE);

}

void Solenoide::open() {
  isActive = true;
  digitalWrite(pin, ETAT_OUVERT);
  delay(500);
  digitalWrite(pin, ETAT_VERROUILLE);
  delay(500);
  digitalWrite(pin, ETAT_OUVERT);
  delay(500);
  digitalWrite(pin, ETAT_VERROUILLE);
}

void Solenoide::openDoor(){
  digitalWrite(pin, ETAT_OUVERT);
  delay(8000);
  digitalWrite(pin, ETAT_VERROUILLE);
  delay(1000);
  digitalWrite(pin, ETAT_OUVERT);
  delay(200);
  digitalWrite(pin, ETAT_VERROUILLE);
}

void Solenoide::update() {
  if (isActive && millis() - tempsDebut >= duree) {
    close();
  }
}

void Solenoide::close() {
  digitalWrite(pin, ETAT_VERROUILLE);
  isActive = false;
}

bool Solenoide::getIsActive(){
  return isActive;
}
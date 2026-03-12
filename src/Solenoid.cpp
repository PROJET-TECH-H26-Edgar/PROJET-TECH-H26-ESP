#include "Solenoide.h"

#define ETAT_VERROUILLE HIGH   
#define ETAT_OUVERT LOW 

Solenoide::Solenoide(uint8_t pin):
    pin(pin),
    tempsDebut(0),
    duree(0),
    isActive(false) {}

void Solenoide::begin() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, ETAT_VERROUILLE);

}

void Solenoide::ouvrir(unsigned long durationMs) {
  duree = durationMs;
  tempsDebut = millis();
  isActive = true;
  digitalWrite(pin, ETAT_OUVERT);
}

void Solenoide::update() {
  if (isActive && millis() - tempsDebut >= duree) {
    fermer();
  }
}

void Solenoide::fermer() {
  digitalWrite(pin, ETAT_VERROUILLE);
  isActive = false;
}
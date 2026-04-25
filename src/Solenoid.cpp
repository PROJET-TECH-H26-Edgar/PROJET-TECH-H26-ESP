#include "Solenoide.h"

#define CLOSE LOW   
#define OPEN HIGH 

Solenoide::Solenoide(uint8_t pin):
    pin(pin),
    startTime(0),
    time(0),
    isActive(false) {}

void Solenoide::begin() {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, CLOSE);

}

void Solenoide::open() {
  isActive = true;
  digitalWrite(pin, OPEN);
  delay(500);
  digitalWrite(pin, CLOSE);
  delay(500);
  digitalWrite(pin, OPEN);
  delay(500);
  digitalWrite(pin, CLOSE);
}

void Solenoide::openDoor(){
  digitalWrite(pin, OPEN);
  delay(8000);
  digitalWrite(pin, CLOSE);
  delay(1000);
  digitalWrite(pin, OPEN);
  delay(200);
  digitalWrite(pin, CLOSE);
}

void Solenoide::update() {
  if (isActive && millis() - startTime >= time) {
    close();
  }
}

void Solenoide::close() {
  digitalWrite(pin, CLOSE);
  isActive = false;
}

bool Solenoide::getIsActive(){
  return isActive;
}
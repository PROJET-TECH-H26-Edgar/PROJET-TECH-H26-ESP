#ifndef SOLENOIDE_H
#define SOLENOIDE_H

#include <Arduino.h>


class Solenoide {
    private : 
        uint8_t pin;
        unsigned long tempsDebut;
        unsigned long duree;
        bool isActive;

    public : 
        Solenoide(uint8_t pin = 0);
        void begin();
        void open();
        void update();
        void close();
        void openDoor();
        bool getIsActive() const { return isActive; }

};



#endif
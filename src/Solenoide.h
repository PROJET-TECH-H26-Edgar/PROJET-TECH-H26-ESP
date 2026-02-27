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
        void ouvrir(unsigned long durationMs);
        void update();
        void fermer();

};



#endif
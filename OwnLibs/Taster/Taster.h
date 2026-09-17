#ifndef TASTER_H
#define TASTER_H

#include <Arduino.h>

class Taster {
public:
    // pin: Pin-Nummer des Tasters
    // negativeLogic: true = Taster zieht auf LOW (INPUT_PULLUP), false = Taster zieht auf HIGH (INPUT)
    // longPressDuration: Dauer in ms, ab der ein Druck als "lang" gilt (in dieser Version noch ungenutzt)
    Taster(uint8_t pin);
    Taster(uint8_t pin, bool negativeLogic);
    Taster(uint8_t pin, bool negativeLogic, unsigned long longPressDuration);

    // Muss in loop() als erstes aufgerufen werden
    void update();

    // Liefert einmalig true, wenn seit dem letzten Aufruf ein neuer Tastendruck erkannt wurde
    bool wasPressed();

private:
    uint8_t pin;
    bool negativeLogic;
    unsigned long longPressDuration;

    bool pressed;
    bool lastPressed;
    bool pressedEvent;
};

#endif

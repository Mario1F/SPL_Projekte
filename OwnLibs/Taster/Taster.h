#ifndef TASTER_H
#define TASTER_H

#include <Arduino.h>

class Taster {
public:
    // pin: Pin-Nummer des Tasters
    // negativeLogic: true = Taster zieht auf LOW (INPUT_PULLUP), false = Taster zieht auf HIGH (INPUT)
    // longPressDuration: Dauer in ms, ab der ein Druck als "lang" gilt (ab dieser Dauer zaehlt ein Druck als lang)
    Taster(uint8_t pin);
    Taster(uint8_t pin, bool negativeLogic);
    Taster(uint8_t pin, bool negativeLogic, unsigned long longPressDuration);

    // Muss in loop() als erstes aufgerufen werden
    void update();

    // Liefert einmalig true, wenn seit dem letzten Aufruf ein neuer Tastendruck erkannt wurde
    bool wasPressed();

    // Liefert einmalig true, wenn der Taster losgelassen wurde und der Druck kuerzer als longPressDuration war
    bool shortPress();

    // Liefert einmalig true, wenn der Taster losgelassen wurde und der Druck mindestens longPressDuration lang war
    bool longPress();

private:
    uint8_t pin;
    bool negativeLogic;
    unsigned long longPressDuration;

    bool pressed;
    bool lastPressed;
    bool pressedEvent;
    bool shortPressEvent;
    bool longPressEvent;
    unsigned long pressStartTime;
};

#endif

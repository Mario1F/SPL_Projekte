#ifndef TASTER_H
#define TASTER_H

#include <Arduino.h>

class Taster {
public:
    // pin: Pin-Nummer des Tasters
    // negativeLogic: true = Taster zieht auf LOW (INPUT_PULLUP), false = Taster zieht auf HIGH (INPUT)
    // longPressDuration: Dauer in ms, ab der ein Druck als "lang" gilt (ab dieser Dauer zaehlt ein Druck als lang)
    // debounceTime: Zeit in ms, die ein neuer Pegel stabil anliegen muss, bevor er uebernommen wird
    Taster(uint8_t pin);
    Taster(uint8_t pin, bool negativeLogic);
    Taster(uint8_t pin, bool negativeLogic, unsigned long longPressDuration);
    Taster(uint8_t pin, bool negativeLogic, unsigned long longPressDuration, unsigned long debounceTime);

    // Muss in loop() als erstes aufgerufen werden
    void update();

    // Liefert einmalig true, wenn seit dem letzten Aufruf ein neuer Tastendruck erkannt wurde
    bool wasPressed();

    // Liefert einmalig true, wenn der Taster losgelassen wurde und der Druck kuerzer als longPressDuration war
    bool shortPress();

    // Liefert einmalig true, wenn der Taster losgelassen wurde und der Druck mindestens longPressDuration lang war
    bool longPress();

    // Liefert true, solange der Taster (nach Entprellen) gedrueckt ist
    bool isPressed() const;

    // Liefert true, wenn der Taster seit mindestens ms Millisekunden ununterbrochen gedrueckt ist
    bool isPressedFor(unsigned long ms) const;

    // Liefert true, wenn in den letzten ms Millisekunden ein Tastendruck erkannt wurde (nicht verbrauchend)
    bool wasPressedWithin(unsigned long ms) const;

private:
    uint8_t pin;
    bool negativeLogic;
    unsigned long longPressDuration;
    unsigned long debounceTime;

    bool rawPressed;
    unsigned long rawChangeTime;
    bool hasPressed;
    unsigned long lastPressTime;
    bool pressed;
    bool lastPressed;
    bool pressedEvent;
    bool shortPressEvent;
    bool longPressEvent;
    unsigned long pressStartTime;
};

#endif

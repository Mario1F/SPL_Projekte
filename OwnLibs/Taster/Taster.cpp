#include "Taster.h"

Taster::Taster(uint8_t pin)
    : Taster(pin, true, 1000, 20) {
}

Taster::Taster(uint8_t pin, bool negativeLogic)
    : Taster(pin, negativeLogic, 1000, 20) {
}

Taster::Taster(uint8_t pin, bool negativeLogic, unsigned long longPressDuration)
    : Taster(pin, negativeLogic, longPressDuration, 20) {
}

Taster::Taster(uint8_t pin, bool negativeLogic, unsigned long longPressDuration, unsigned long debounceTime)
    : pin(pin),
      negativeLogic(negativeLogic),
      longPressDuration(longPressDuration),
      debounceTime(debounceTime),
      rawPressed(false),
      rawChangeTime(0),
      hasPressed(false),
      lastPressTime(0),
      pressed(false),
      lastPressed(false),
      pressedEvent(false),
      shortPressEvent(false),
      longPressEvent(false),
      pressStartTime(0) {
    if (negativeLogic) {
        pinMode(pin, INPUT_PULLUP);
    } else {
        pinMode(pin, INPUT);
    }
}

void Taster::update() {
    unsigned long now = millis();
    bool rawState = digitalRead(pin);
    bool raw = negativeLogic ? !rawState : rawState;

    // Entprellen: neuer Pegel wird erst uebernommen, wenn er debounceTime lang stabil war
    if (raw != rawPressed) {
        rawPressed = raw;
        rawChangeTime = now;
    }
    if (rawPressed != pressed && now - rawChangeTime >= debounceTime) {
        pressed = rawPressed;
    }

    if (pressed && !lastPressed) {
        pressedEvent = true;
        pressStartTime = now;
        lastPressTime = now;
        hasPressed = true;
    } else if (!pressed && lastPressed) {
        if (now - pressStartTime >= longPressDuration) {
            longPressEvent = true;
        } else {
            shortPressEvent = true;
        }
    }
    lastPressed = pressed;
}

bool Taster::wasPressed() {
    if (pressedEvent) {
        pressedEvent = false;
        return true;
    }
    return false;
}

bool Taster::shortPress() {
    if (shortPressEvent) {
        shortPressEvent = false;
        return true;
    }
    return false;
}

bool Taster::longPress() {
    if (longPressEvent) {
        longPressEvent = false;
        return true;
    }
    return false;
}

bool Taster::isPressed() const {
    return pressed;
}

bool Taster::isPressedFor(unsigned long ms) const {
    return pressed && millis() - pressStartTime >= ms;
}

bool Taster::wasPressedWithin(unsigned long ms) const {
    return hasPressed && millis() - lastPressTime <= ms;
}

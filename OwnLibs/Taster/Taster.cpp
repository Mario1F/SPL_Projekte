#include "Taster.h"

Taster::Taster(uint8_t pin)
    : Taster(pin, true, 1000) {
}

Taster::Taster(uint8_t pin, bool negativeLogic)
    : Taster(pin, negativeLogic, 1000) {
}

Taster::Taster(uint8_t pin, bool negativeLogic, unsigned long longPressDuration)
    : pin(pin),
      negativeLogic(negativeLogic),
      longPressDuration(longPressDuration),
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
    bool rawState = digitalRead(pin);
    pressed = negativeLogic ? !rawState : rawState;

    if (pressed && !lastPressed) {
        pressedEvent = true;
        pressStartTime = millis();
    } else if (!pressed && lastPressed) {
        if (millis() - pressStartTime >= longPressDuration) {
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

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
      pressedEvent(false) {
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

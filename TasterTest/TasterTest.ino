#include <Taster.h>

const uint8_t BUTTON_PIN = 2;
const uint8_t LED_PIN = LED_BUILTIN;
const unsigned long LED_ON_DURATION = 5000; // ms

Taster button(BUTTON_PIN);

bool ledOn = false;
unsigned long ledStartTime = 0;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
}

void loop() {
    button.update(); // must be the first statement in loop()

    if (button.wasPressed()) {
        // (Re)start the 5 second timer; an already running time is not added to
        ledOn = true;
        ledStartTime = millis();
        digitalWrite(LED_PIN, HIGH);
    }

    if (ledOn && millis() - ledStartTime >= LED_ON_DURATION) {
        ledOn = false;
        digitalWrite(LED_PIN, LOW);
    }
}

#include <Taster.h>
#include <LedStrip.h>

const uint8_t BUTTON_PIN = 2;
const uint8_t STRIP_PIN = 6;
const uint16_t LED_COUNT = 30;
const uint8_t BRIGHTNESS = 64; // 0-255, limits the current draw

Taster button(BUTTON_PIN);
LedStrip strip(STRIP_PIN, LED_COUNT);

// Shared between the button part (writes) and the strip part (reads)
Pattern pattern = PATTERN_RED;

void setup() {
    strip.begin();
    strip.setBrightness(BRIGHTNESS);
}

void loop() {
    button.update();

    if (button.wasPressed()) {
        pattern = (Pattern)((pattern + 1) % PATTERN_COUNT);
    }

    strip.update(pattern);
}

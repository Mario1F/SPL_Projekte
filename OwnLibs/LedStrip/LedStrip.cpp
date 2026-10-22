#include "LedStrip.h"

LedStrip::LedStrip(uint8_t pin, uint16_t ledCount)
    : LedStrip(pin, ledCount, 40) {}

LedStrip::LedStrip(uint8_t pin, uint16_t ledCount, unsigned long frameInterval)
    : strip(ledCount, pin, NEO_GRB + NEO_KHZ800),
      frameInterval(frameInterval),
      lastShowTime(0) {}

void LedStrip::begin() {
    strip.begin();
    strip.show();
}

void LedStrip::setBrightness(uint8_t brightness) {
    strip.setBrightness(brightness);
}

void LedStrip::update(Pattern pattern) {
    switch (pattern) {
        case PATTERN_RED:  patternRed();  break;
        case PATTERN_BLUE: patternBlue(); break;
        default: break;
    }

    // The only place where show() is called
    unsigned long now = millis();
    if (now - lastShowTime >= frameInterval) {
        lastShowTime = now;
        strip.show();
    }
}

void LedStrip::patternRed() {
    strip.fill(strip.Color(255, 0, 0));
}

void LedStrip::patternBlue() {
    strip.fill(strip.Color(0, 0, 255));
}

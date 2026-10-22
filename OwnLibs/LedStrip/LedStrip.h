#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// Available patterns. PATTERN_COUNT must stay last (used for the modulo wrap-around).
enum Pattern : uint8_t {
    PATTERN_RED,
    PATTERN_BLUE,
    PATTERN_COUNT
};

class LedStrip {
public:
    // pin: data pin of the strip
    // ledCount: number of LEDs
    // frameInterval: minimum time in ms between two show() calls (default 40 ms = 25 fps)
    LedStrip(uint8_t pin, uint16_t ledCount);
    LedStrip(uint8_t pin, uint16_t ledCount, unsigned long frameInterval);

    // Call once in setup()
    void begin();

    // Sets the brightness (0-255)
    void setBrightness(uint8_t brightness);

    // Call in every loop(): renders the pattern and, if frameInterval has elapsed, shows it
    void update(Pattern pattern);

private:
    void patternRed();
    void patternBlue();

    Adafruit_NeoPixel strip;
    unsigned long frameInterval;
    unsigned long lastShowTime;
};

#endif

#ifndef LEDSTRIP_H
#define LEDSTRIP_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// Available patterns. PATTERN_COUNT must stay last (used for the modulo wrap-around).
// Always append new patterns at the end: the index is stored in the EEPROM.
enum Pattern : uint8_t {
    PATTERN_RED,
    PATTERN_BLUE,
    PATTERN_COUNT
};

class LedStrip {
public:
    // pin: data pin of the strip
    // maxLedCount: number of LEDs physically connected (upper limit for setLedCount)
    // frameInterval: minimum time in ms between two show() calls (default 40 ms = 25 fps)
    LedStrip(uint8_t pin, uint16_t maxLedCount);
    LedStrip(uint8_t pin, uint16_t maxLedCount, unsigned long frameInterval);

    // Call once in setup()
    void begin();

    // Sets the brightness (0-255)
    void setBrightness(uint8_t brightness);

    // Number of LEDs the patterns use (1..maxLedCount); LEDs behind it stay dark
    void setLedCount(uint16_t ledCount);
    uint16_t getLedCount() const;
    uint16_t getMaxLedCount() const;

    // Starts the confirmation feedback: first 5 LEDs blink green 3 times (non-blocking)
    void startFeedback();

    // While > 0, the first count LEDs (up to maxLedCount) are lit white instead of the pattern; 0 = off
    void setPreviewCount(uint16_t count);

    // Call in every loop(): renders the pattern and, if frameInterval has elapsed, shows it
    void update(Pattern pattern);

private:
    void patternRed();
    void patternBlue();
    void renderFeedback();

    Adafruit_NeoPixel strip;
    uint16_t maxLedCount;
    uint16_t ledCount;
    unsigned long frameInterval;
    unsigned long lastShowTime;
    uint16_t previewCount;
    bool feedbackActive;
    uint8_t feedbackPhase;
    unsigned long feedbackPhaseStart;
};

#endif

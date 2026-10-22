#include <Taster.h>
#include <LedStrip.h>
#include <Settings.h>

const uint8_t BUTTON_PIN = 2;
const uint8_t STRIP_PIN = 6;
const uint16_t MAX_LED_COUNT = 30;
const uint8_t BRIGHTNESS = 64; // 0-255, limits the current draw

const unsigned long LONG_PRESS_DURATION = 1000;   // ms, from here a press saves the pattern
const unsigned long COUNT_MODE_DURATION = 3000;   // ms, from here the LED count is entered
const unsigned long COUNT_STEP_INTERVAL = 200;    // ms per additional LED while counting

Taster button(BUTTON_PIN, true, LONG_PRESS_DURATION);
LedStrip strip(STRIP_PIN, MAX_LED_COUNT);
Settings settings(PATTERN_COUNT, MAX_LED_COUNT, PATTERN_RED, MAX_LED_COUNT);

// Shared between the button part (writes) and the strip part (reads)
Pattern pattern = PATTERN_RED;

// State of the LED count input (held longer than COUNT_MODE_DURATION)
bool counting = false;
uint16_t countedLeds = 0;
unsigned long lastCountStep = 0;

void setup() {
    settings.begin();
    pattern = (Pattern)settings.getPattern();

    strip.begin();
    strip.setBrightness(BRIGHTNESS);
    strip.setLedCount(settings.getLedCount());
}

void loop() {
    button.update();

    // Held long enough: light one more LED every COUNT_STEP_INTERVAL
    if (button.isPressedFor(COUNT_MODE_DURATION)) {
        unsigned long now = millis();
        if (!counting) {
            counting = true;
            countedLeds = 1;
            lastCountStep = now;
        } else if (now - lastCountStep >= COUNT_STEP_INTERVAL && countedLeds < strip.getMaxLedCount()) {
            countedLeds++;
            lastCountStep = now;
        }
        strip.setPreviewCount(countedLeds);
    }

    // Short press: next pattern, after the last one back to the first
    if (button.shortPress()) {
        pattern = (Pattern)((pattern + 1) % PATTERN_COUNT);
    }

    // Released after a long press: save the LED count (if counting) or the pattern
    if (button.longPress()) {
        if (counting) {
            counting = false;
            strip.setPreviewCount(0);
            strip.setLedCount(countedLeds);
            settings.saveLedCount(countedLeds);
        } else {
            settings.savePattern(pattern);
        }
        strip.startFeedback();
    }

    strip.update(pattern);
}

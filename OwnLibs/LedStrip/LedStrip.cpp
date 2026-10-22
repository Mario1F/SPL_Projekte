#include "LedStrip.h"

static const uint16_t FEEDBACK_LED_COUNT = 5;
static const uint8_t FEEDBACK_BLINKS = 3;
static const unsigned long FEEDBACK_PHASE_DURATION = 200; // ms, on and off phases

LedStrip::LedStrip(uint8_t pin, uint16_t maxLedCount)
    : LedStrip(pin, maxLedCount, 40) {}

LedStrip::LedStrip(uint8_t pin, uint16_t maxLedCount, unsigned long frameInterval)
    : strip(maxLedCount, pin, NEO_GRB + NEO_KHZ800),
      maxLedCount(maxLedCount),
      ledCount(maxLedCount),
      frameInterval(frameInterval),
      lastShowTime(0),
      previewCount(0),
      feedbackActive(false),
      feedbackPhase(0),
      feedbackPhaseStart(0) {}

void LedStrip::begin() {
    strip.begin();
    strip.show();
}

void LedStrip::setBrightness(uint8_t brightness) {
    strip.setBrightness(brightness);
}

void LedStrip::setLedCount(uint16_t newLedCount) {
    if (newLedCount < 1 || newLedCount > maxLedCount) {
        return;
    }
    ledCount = newLedCount;
}

uint16_t LedStrip::getLedCount() const {
    return ledCount;
}

uint16_t LedStrip::getMaxLedCount() const {
    return maxLedCount;
}

void LedStrip::startFeedback() {
    feedbackActive = true;
    feedbackPhase = 0;
    feedbackPhaseStart = millis();
}

void LedStrip::setPreviewCount(uint16_t count) {
    previewCount = count > maxLedCount ? maxLedCount : count;
}

void LedStrip::update(Pattern pattern) {
    // Clear everything first, so LEDs behind ledCount stay dark
    strip.clear();

    if (previewCount > 0) {
        strip.fill(strip.Color(255, 255, 255), 0, previewCount);
    } else {
        switch (pattern) {
            case PATTERN_RED:  patternRed();  break;
            case PATTERN_BLUE: patternBlue(); break;
            default: break;
        }
        renderFeedback();
    }

    // The only place where show() is called
    unsigned long now = millis();
    if (now - lastShowTime >= frameInterval) {
        lastShowTime = now;
        strip.show();
    }
}

void LedStrip::patternRed() {
    strip.fill(strip.Color(255, 0, 0), 0, ledCount);
}

void LedStrip::patternBlue() {
    strip.fill(strip.Color(0, 0, 255), 0, ledCount);
}

// Overlay on the first LEDs: even phases green, odd phases dark, then the pattern continues
void LedStrip::renderFeedback() {
    if (!feedbackActive) {
        return;
    }

    unsigned long now = millis();
    if (now - feedbackPhaseStart >= FEEDBACK_PHASE_DURATION) {
        feedbackPhaseStart += FEEDBACK_PHASE_DURATION;
        feedbackPhase++;
    }
    if (feedbackPhase >= FEEDBACK_BLINKS * 2) {
        feedbackActive = false;
        return;
    }

    uint16_t count = ledCount < FEEDBACK_LED_COUNT ? ledCount : FEEDBACK_LED_COUNT;
    uint32_t color = (feedbackPhase % 2 == 0) ? strip.Color(0, 255, 0) : 0;
    strip.fill(color, 0, count);
}

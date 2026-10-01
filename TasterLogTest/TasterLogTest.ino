#include <Taster.h>

const uint8_t BUTTON_PIN = 2;
const unsigned long LONG_PRESS_DURATION = 1000; // ms
const unsigned long STEP_TIMEOUT = 15000;       // ms

Taster button(BUTTON_PIN, true, LONG_PRESS_DURATION);

enum Step {
    STEP_SHORT,
    STEP_LONG,
    STEP_EVENT_ORDER,
    STEP_CONSUMED,
    STEP_DONE
};

Step step = STEP_SHORT;
bool stepAnnounced = false;
unsigned long stepStartTime = 0;
unsigned long pressStartTime = 0;
bool pressedSeen = false;
uint8_t passCount = 0;
uint8_t failCount = 0;

void logPrefix() {
    Serial.print('[');
    Serial.print(millis());
    Serial.print(F(" ms] "));
}

void logLine(const __FlashStringHelper *text) {
    logPrefix();
    Serial.println(text);
}

void logPressEvent(const __FlashStringHelper *name) {
    logPrefix();
    Serial.print(F("event: "));
    Serial.print(name);
    Serial.print(F(" after "));
    Serial.print(millis() - pressStartTime);
    Serial.println(F(" ms"));
}

void report(bool ok, const __FlashStringHelper *name) {
    logPrefix();
    Serial.print(ok ? F("PASS: ") : F("FAIL: "));
    Serial.println(name);
    if (ok) {
        passCount++;
    } else {
        failCount++;
    }
}

void nextStep(Step next) {
    step = next;
    stepAnnounced = false;
    pressedSeen = false;
}

void announceStep() {
    stepAnnounced = true;
    stepStartTime = millis();
    switch (step) {
        case STEP_SHORT:
            logLine(F("TEST 1: press the button SHORT (< 1 s) and release"));
            break;
        case STEP_LONG:
            logLine(F("TEST 2: press the button LONG (> 1 s) and release"));
            break;
        case STEP_EVENT_ORDER:
            logLine(F("TEST 3: press SHORT; wasPressed() must fire on press, shortPress() on release"));
            break;
        case STEP_CONSUMED:
            logLine(F("TEST 4: press SHORT once; every event must be reported only once"));
            break;
        case STEP_DONE:
            Serial.println(F("=== SUMMARY ==="));
            Serial.print(F("PASS: "));
            Serial.println(passCount);
            Serial.print(F("FAIL: "));
            Serial.println(failCount);
            Serial.println(failCount == 0 ? F("ALL TESTS PASSED") : F("SOME TESTS FAILED"));
            break;
    }
}

void setup() {
    Serial.begin(9600);
    logLine(F("=== TasterLogTest started ==="));
    Serial.print(F("Button on D2, long press threshold: "));
    Serial.print(LONG_PRESS_DURATION);
    Serial.println(F(" ms"));
}

void loop() {
    button.update(); // must be the first statement in loop()

    if (!stepAnnounced) {
        announceStep();
    }
    if (step == STEP_DONE) {
        return;
    }

    bool wasPressed = button.wasPressed();
    bool shortPress = button.shortPress();
    bool longPress = button.longPress();

    if (wasPressed) {
        pressStartTime = millis();
        pressedSeen = true;
        logLine(F("event: wasPressed()"));
    }
    if (shortPress) {
        logPressEvent(F("shortPress()"));
    }
    if (longPress) {
        logPressEvent(F("longPress()"));
    }

    if (shortPress || longPress) {
        switch (step) {
            case STEP_SHORT:
                report(shortPress && !longPress, F("short press reported as shortPress() only"));
                nextStep(STEP_LONG);
                break;
            case STEP_LONG:
                report(longPress && !shortPress, F("long press reported as longPress() only"));
                nextStep(STEP_EVENT_ORDER);
                break;
            case STEP_EVENT_ORDER:
                report(pressedSeen && shortPress, F("wasPressed() fired before shortPress()"));
                nextStep(STEP_CONSUMED);
                break;
            case STEP_CONSUMED:
                // the events were consumed above, so a second read must return false
                report(!button.wasPressed() && !button.shortPress() && !button.longPress(),
                       F("events are reported only once"));
                nextStep(STEP_DONE);
                break;
            default:
                break;
        }
    } else if (millis() - stepStartTime >= STEP_TIMEOUT) {
        report(false, F("timeout, no press detected"));
        nextStep(step == STEP_CONSUMED ? STEP_DONE : static_cast<Step>(step + 1));
    }
}

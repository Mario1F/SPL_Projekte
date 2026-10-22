#include "Settings.h"
#include <EEPROM.h>

static const uint8_t MAGIC = 0xA5;
static const int ADDRESS_MAGIC = 0;
static const int ADDRESS_PATTERN = 1;
static const int ADDRESS_LED_COUNT = 2;

Settings::Settings(uint8_t patternCount, uint8_t maxLedCount, uint8_t defaultPattern, uint8_t defaultLedCount)
    : patternCount(patternCount),
      maxLedCount(maxLedCount),
      pattern(defaultPattern),
      ledCount(defaultLedCount) {}

void Settings::begin() {
    if (EEPROM.read(ADDRESS_MAGIC) != MAGIC) {
        return;
    }

    // Each value is validated on its own, an invalid one keeps its default
    uint8_t storedPattern = EEPROM.read(ADDRESS_PATTERN);
    if (storedPattern < patternCount) {
        pattern = storedPattern;
    }
    uint8_t storedLedCount = EEPROM.read(ADDRESS_LED_COUNT);
    if (storedLedCount >= 1 && storedLedCount <= maxLedCount) {
        ledCount = storedLedCount;
    }
}

uint8_t Settings::getPattern() const {
    return pattern;
}

uint8_t Settings::getLedCount() const {
    return ledCount;
}

void Settings::savePattern(uint8_t newPattern) {
    if (newPattern >= patternCount) {
        return;
    }
    writeMagic();
    pattern = newPattern;
    EEPROM.update(ADDRESS_PATTERN, pattern);
}

void Settings::saveLedCount(uint8_t newLedCount) {
    if (newLedCount < 1 || newLedCount > maxLedCount) {
        return;
    }
    writeMagic();
    ledCount = newLedCount;
    EEPROM.update(ADDRESS_LED_COUNT, ledCount);
}

void Settings::writeMagic() {
    // On the first write the other value is still unwritten (0xFF): store the current one so both are valid
    if (EEPROM.read(ADDRESS_MAGIC) != MAGIC) {
        EEPROM.update(ADDRESS_PATTERN, pattern);
        EEPROM.update(ADDRESS_LED_COUNT, ledCount);
        EEPROM.update(ADDRESS_MAGIC, MAGIC);
    }
}

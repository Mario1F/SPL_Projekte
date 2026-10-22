#ifndef SETTINGS_H
#define SETTINGS_H

#include <Arduino.h>

class Settings {
public:
    // patternCount: number of valid patterns (stored index must be < patternCount)
    // maxLedCount: maximum valid LED count (stored count must be 1..maxLedCount)
    // defaultPattern, defaultLedCount: used when nothing valid is stored
    Settings(uint8_t patternCount, uint8_t maxLedCount, uint8_t defaultPattern, uint8_t defaultLedCount);

    // Loads the stored values; falls back to the defaults if the EEPROM content is invalid (does not write)
    void begin();

    uint8_t getPattern() const;
    uint8_t getLedCount() const;

    // Store the value (writes only if it changed; also writes the magic byte)
    void savePattern(uint8_t pattern);
    void saveLedCount(uint8_t ledCount);

private:
    void writeMagic();

    uint8_t patternCount;
    uint8_t maxLedCount;
    uint8_t pattern;
    uint8_t ledCount;
};

#endif

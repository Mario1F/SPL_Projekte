# Settings

Speichert Einstellungen des LED-Streifen-Projekts dauerhaft im EEPROM des Arduino Nano. Die Klasse ist nur für das EEPROM zuständig (kein Zugriff auf Taster oder Streifen).

## Aktueller Stand

Gespeichert werden das gewählte Muster (als Index) und die Anzahl der LEDs.

## EEPROM-Layout

| Adresse | Inhalt |
|---|---|
| 0 | Magic-Byte `0xA5` (zeigt an, dass gültige Werte vorliegen) |
| 1 | Muster-Index |
| 2 | LED-Anzahl |

Beim ersten Speichern werden beide Werte (aktuelle bzw. Standardwerte) zusammen mit dem Magic-Byte geschrieben, sodass der nicht geänderte Wert nicht als `0xFF` zurückkommt.

## Konstruktor

`Settings(uint8_t patternCount, uint8_t maxLedCount, uint8_t defaultPattern, uint8_t defaultLedCount)`

| Parameter | Bedeutung |
|---|---|
| `patternCount` | Anzahl gültiger Muster; ein gespeicherter Index muss kleiner sein |
| `maxLedCount` | größte gültige LED-Anzahl (gültig ist 1 bis `maxLedCount`) |
| `defaultPattern` | Muster, wenn nichts Gültiges gespeichert ist |
| `defaultLedCount` | LED-Anzahl, wenn nichts Gültiges gespeichert ist |

Es gibt keine Überladungen und keine Standardwerte für die Parameter.

## Methoden

- `void begin()` – in `setup()` aufrufen. Lädt die gespeicherten Werte. Ist das Magic-Byte nicht gesetzt oder ein Wert ungültig, bleibt der Standardwert (es wird nichts geschrieben).
- `uint8_t getPattern() const` – aktueller Muster-Index.
- `uint8_t getLedCount() const` – aktuelle LED-Anzahl.
- `void savePattern(uint8_t pattern)` – speichert den Index; ungültige Werte (≥ `patternCount`) werden ignoriert.
- `void saveLedCount(uint8_t ledCount)` – speichert die Anzahl; ungültige Werte (0 oder > `maxLedCount`) werden ignoriert.

Geschrieben wird mit `EEPROM.update()`, also nur bei geändertem Inhalt (schont die ca. 100.000 Schreibzyklen pro Zelle).

## Hinweise

- Neue Muster immer am Ende des `enum Pattern` ergänzen, sonst ändert sich die Bedeutung gespeicherter Indizes.
- Wird `patternCount` oder `maxLedCount` später verkleinert, werden zu große gespeicherte Werte beim Laden verworfen.

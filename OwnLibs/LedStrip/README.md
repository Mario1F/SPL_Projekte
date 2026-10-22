# LedStrip

Steuert einen WS2812-LED-Streifen (über die Library *Adafruit NeoPixel*) und stellt Muster dar, ohne die `loop()` zu blockieren. Die Klasse ist nur für den LED-Streifen zuständig (kein Zugriff auf Taster, EEPROM o. Ä.).

## Aktueller Stand

- Muster `PATTERN_RED` (ganzer Streifen rot) und `PATTERN_BLUE` (ganzer Streifen blau). Weitere Muster (Lauflicht, Regenbogen, Flackern) folgen.
- Einstellbare aktive LED-Anzahl; LEDs dahinter bleiben dunkel.
- Nicht blockierende Rückmeldung (grünes Blinken) und Vorschau für die LED-Anzahl-Eingabe.
- Bluetooth/RemoteXY ist noch nicht eingebunden.

## Enum `Pattern`

| Wert | Bedeutung |
|---|---|
| `PATTERN_RED` | ganzer Streifen rot |
| `PATTERN_BLUE` | ganzer Streifen blau |
| `PATTERN_COUNT` | Anzahl der Muster, steht immer zuletzt (für den Modulo-Überlauf: `(Pattern)((pattern + 1) % PATTERN_COUNT)`) |

Neue Muster immer **am Ende vor `PATTERN_COUNT`** ergänzen, da der Index im EEPROM gespeichert wird.

## Konstruktoren

| Konstruktor | Standardwerte |
|---|---|
| `LedStrip(uint8_t pin, uint16_t maxLedCount)` | `frameInterval = 40` ms (25 fps) |
| `LedStrip(uint8_t pin, uint16_t maxLedCount, unsigned long frameInterval)` | – |

| Parameter | Bedeutung |
|---|---|
| `pin` | Datenpin des Streifens |
| `maxLedCount` | Anzahl der physisch angeschlossenen LEDs (Obergrenze für `setLedCount`); die aktive Anzahl ist zunächst gleich `maxLedCount` |
| `frameInterval` | Mindestabstand in ms zwischen zwei `show()`-Aufrufen |

## Methoden

- `void begin()` – einmal in `setup()` aufrufen; initialisiert den Streifen und schaltet ihn dunkel.
- `void setBrightness(uint8_t brightness)` – Helligkeit 0–255 (begrenzt den Stromverbrauch).
- `void setLedCount(uint16_t ledCount)` – aktive LED-Anzahl, gültig 1 bis `maxLedCount` (andere Werte werden ignoriert). Die Muster nutzen nur diese LEDs, alle dahinter bleiben dunkel.
- `uint16_t getLedCount() const` – aktive LED-Anzahl.
- `uint16_t getMaxLedCount() const` – physische LED-Anzahl.
- `void startFeedback()` – startet die Rückmeldung: die ersten 5 LEDs (bei weniger aktiven LEDs entsprechend weniger) blinken 3-mal grün (200 ms an, 200 ms aus). Läuft nicht blockierend über `update()`, danach läuft das Muster normal weiter.
- `void setPreviewCount(uint16_t count)` – solange `count > 0`, leuchten die ersten `count` LEDs weiß (bis `maxLedCount`) statt des Musters; `0` schaltet die Vorschau aus. Wird für die LED-Anzahl-Eingabe verwendet.
- `void update(Pattern pattern)` – in jeder `loop()` aufrufen. Löscht den Puffer, zeichnet per `switch` das Muster (bzw. die Vorschau), legt die Rückmeldung darüber und ruft `show()` höchstens alle `frameInterval` ms auf. Das ist die **einzige** Stelle, an der `show()` aufgerufen wird.

Interne Funktionen (privat): `patternRed()`, `patternBlue()`, `renderFeedback()`.

## Beispiel

Siehe `LedStrip/LedStrip.ino` im Projektordner.

```cpp
LedStrip strip(6, 30);
Pattern pattern = PATTERN_RED;

void setup() { strip.begin(); strip.setLedCount(20); }
void loop() { strip.update(pattern); }
```

## Hinweise

- Benötigt die Library *Adafruit NeoPixel*.
- `show()` blockiert die Interrupts kurz; deshalb nicht häufiger als nötig aufrufen (wichtig für das spätere Bluetoothmodul).

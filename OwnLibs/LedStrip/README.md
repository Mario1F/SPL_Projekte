# LedStrip

Steuert einen WS2812-LED-Streifen (über die Library *Adafruit NeoPixel*) und stellt Muster dar, ohne die `loop()` zu blockieren. Die Klasse ist nur für den LED-Streifen zuständig (kein Zugriff auf Taster o. Ä.).

## Aktueller Stand

Implementiert sind die Muster `PATTERN_RED` (ganzer Streifen rot) und `PATTERN_BLUE` (ganzer Streifen blau). Weitere Muster (Lauflicht, Regenbogen, Flackern) folgen. Bluetooth/RemoteXY ist noch nicht eingebunden.

## Enum `Pattern`

| Wert | Bedeutung |
|---|---|
| `PATTERN_RED` | ganzer Streifen rot |
| `PATTERN_BLUE` | ganzer Streifen blau |
| `PATTERN_COUNT` | Anzahl der Muster, steht immer zuletzt (für den Modulo-Überlauf: `(Pattern)((pattern + 1) % PATTERN_COUNT)`) |

## Konstruktoren

| Konstruktor | Standardwerte |
|---|---|
| `LedStrip(uint8_t pin, uint16_t ledCount)` | `frameInterval = 40` ms (25 fps) |
| `LedStrip(uint8_t pin, uint16_t ledCount, unsigned long frameInterval)` | – |

| Parameter | Bedeutung |
|---|---|
| `pin` | Datenpin des Streifens |
| `ledCount` | Anzahl der LEDs |
| `frameInterval` | Mindestabstand in ms zwischen zwei `show()`-Aufrufen |

## Methoden

- `void begin()` – einmal in `setup()` aufrufen; initialisiert den Streifen und schaltet ihn dunkel.
- `void setBrightness(uint8_t brightness)` – Helligkeit 0–255 (begrenzt den Stromverbrauch).
- `void update(Pattern pattern)` – in jeder `loop()` aufrufen. Wählt per `switch` die Musterfunktion, zeichnet das Muster und ruft `show()` höchstens alle `frameInterval` ms auf. Das ist die **einzige** Stelle, an der `show()` aufgerufen wird.

Interne Musterfunktionen (privat): `patternRed()`, `patternBlue()`.

## Beispiel

Siehe `LedStrip/LedStrip.ino` im Projektordner.

```cpp
LedStrip strip(6, 30);
Pattern pattern = PATTERN_RED;

void setup() { strip.begin(); }
void loop() { strip.update(pattern); }
```

## Hinweise

- Benötigt die Library *Adafruit NeoPixel*.
- `show()` blockiert die Interrupts kurz; deshalb nicht häufiger als nötig aufrufen (wichtig für das spätere Bluetoothmodul).

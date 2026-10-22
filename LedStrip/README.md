# LedStrip (Projekt)

Aufgabe 2, Schritt 1: Mit einem Taster zwischen Mustern des LED-Streifens umschalten (siehe `Aufgaben/Aufgabe2_LedStreifen.md`).

## Aufbau

- Taster an **D2** gegen GND (`INPUT_PULLUP`).
- WS2812-Streifen, Datenleitung an **D6**, **30 LEDs**.
- Helligkeit auf 64 von 255 begrenzt (`BRIGHTNESS`), um den Strom zu begrenzen.

## Funktionsweise

- Globale Variable `pattern` (Typ `Pattern`) verbindet die beiden Teile: der Tasterteil schreibt sie, der Streifenteil liest sie.
- Bei jedem Tastendruck: `pattern = (Pattern)((pattern + 1) % PATTERN_COUNT)` – nach dem letzten Muster geht es wieder zum ersten.
- Muster: rot, blau.
- Kein `delay()`; `loop()` ruft nur `button.update()`, `button.wasPressed()` und `strip.update(pattern)` auf.

## Verwendete Klassen

- `Taster` (`OwnLibs/Taster/`)
- `LedStrip` (`OwnLibs/LedStrip/`)
- Library *Adafruit NeoPixel*

## Kompilieren

```bash
arduino-cli compile --fqbn arduino:avr:nano --library OwnLibs/Taster --library OwnLibs/LedStrip LedStrip
```

Status: kompiliert (ca. 10 % Flash, 3 % RAM); noch nicht auf der Hardware getestet.

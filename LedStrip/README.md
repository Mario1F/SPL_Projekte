# LedStrip (Projekt)

Aufgabe 2, Schritt 1 und Aufgabe 3: Mit einem Taster zwischen Mustern des LED-Streifens umschalten und Muster sowie LED-Anzahl dauerhaft speichern (siehe `Aufgaben/Aufgabe2_LedStreifen.md` und `Aufgaben/Aufgabe3_Speichern_EEPROM.md`).

## Aufbau

- Taster an **D2** gegen GND (`INPUT_PULLUP`), Schwelle für "lang": **1000 ms**.
- WS2812-Streifen, Datenleitung an **D6**, **30 LEDs** (`MAX_LED_COUNT`).
- Helligkeit auf 64 von 255 begrenzt (`BRIGHTNESS`), um den Strom zu begrenzen.

## Bedienung

| Aktion | Wirkung |
|---|---|
| Kurz drücken (< 1 s) | nächstes Muster (nach dem letzten wieder das erste) – wirkt beim Loslassen |
| 1 s bis 3 s halten, loslassen | aktuelles Muster wird im EEPROM gespeichert, Rückmeldung: die ersten 5 LEDs blinken 3-mal grün |
| Länger als 3 s halten | LED-Anzahl einstellen: ab 3 s leuchtet 1 LED (weiß), danach alle 200 ms eine weitere, bis maximal 30 |
| …dann loslassen | die leuchtende Anzahl wird gespeichert (gilt für alle Muster), Rückmeldung wie oben; das Muster wird dabei nicht gespeichert |

Beim Start werden Muster und LED-Anzahl aus dem EEPROM geladen; ist nichts (Gültiges) gespeichert, gelten Muster rot und 30 LEDs.

## UML

Klassen-, Zustands-, Sequenz- und Ablaufdiagramm siehe [UML.md](UML.md).

## Funktionsweise

- Globale Variable `pattern` (Typ `Pattern`) verbindet Taster- und Streifenteil: der Tasterteil schreibt sie, der Streifenteil liest sie.
- Kein `delay()`; Zählen und Blinken laufen über `millis()`.
- Der Sketch verbindet nur die Komponenten (Taster → Streifen/EEPROM); jede Klasse kennt nur ihre eigene Hardware.

## Verwendete Klassen

- `Taster` (`OwnLibs/Taster/`)
- `LedStrip` (`OwnLibs/LedStrip/`)
- `Settings` (`OwnLibs/Settings/`)
- Library *Adafruit NeoPixel*

## Kompilieren

```bash
arduino-cli compile --fqbn arduino:avr:nano --library OwnLibs/Taster --library OwnLibs/LedStrip --library OwnLibs/Settings LedStrip
```

Status: kompiliert (ca. 14 % Flash, 4 % RAM); noch nicht auf der Hardware getestet.

# TasterLogTest

Interaktiver Test für die Klasse `Taster` (`OwnLibs/Taster/`): Der Sketch führt dich per Serial-Ausgabe durch vier Tests, die du mit Tastendrücken beantwortest, und meldet je Test `PASS` oder `FAIL`. Alle Ereignisse werden mit Zeitstempel (`millis()`) ausgegeben und können in eine Log-Datei geschrieben werden.

## Aufbau

- Taster an **D2** gegen GND (`INPUT_PULLUP`, negative Logik), Schwelle für "lang": **1000 ms**.
- LED: On-Board-LED `LED_BUILTIN` (D13).
- Serielle Ausgabe mit **9600 Baud**.
- Ausführliche Anleitung mit Verdrahtung und allen Befehlen: `Anleitung.html`.

## Tests

| Nr. | Aktion | Erwartung |
|---|---|---|
| 1 | Taster kurz drücken (< 1 s) | `shortPress()` meldet, `longPress()` nicht |
| 2 | Taster lang drücken (> 1 s) | `longPress()` meldet, `shortPress()` nicht |
| 3 | Taster kurz drücken | `wasPressed()` kommt beim Drücken, vor `shortPress()` beim Loslassen |
| 4 | Taster kurz drücken | jedes Ereignis wird nur einmal gemeldet (zweites Auslesen liefert `false`) |

Pro Test wartet der Sketch 15 s; ohne Tastendruck wird der Test als `FAIL` (timeout) gewertet. Am Ende gibt es eine Zusammenfassung (`ALL TESTS PASSED` / `SOME TESTS FAILED`). Zum Wiederholen den Arduino resetten.

Zusätzlich werden alle Ereignisse einzeln protokolliert, z. B. `event: shortPress() after 120 ms`. Da noch nicht entprellt wird, siehst du hier auch, ob Prellen mehrere Ereignisse erzeugt.

### Demo (LED-Test, übernommen aus dem früheren `TasterTest`)

Nach den vier Tests wechselt der Sketch in den Demo-Modus: Bei einem Tastendruck leuchtet die LED **5 Sekunden**. Wird der Taster **innerhalb dieser 5 Sekunden** erneut gedrückt, startet die Zeit neu (kein Addieren zur Restzeit). `LED on` / `LED off` wird mitgeloggt.

## Ausführen und loggen

```
arduino-cli compile --fqbn arduino:avr:nano --libraries OwnLibs TasterLogTest
arduino-cli upload -p COM3 --fqbn arduino:avr:nano TasterLogTest
.\TasterLogTest\log_serial.ps1 -Port COM3
```

`COM3` durch den eigenen Port ersetzen (`arduino-cli board list`). `log_serial.ps1` zeigt die Ausgabe an und schreibt sie in `TasterLogTest/logs/test_log_<Datum_Uhrzeit>.txt`. Alternativ im Arduino-IDE-Serial-Monitor mitlesen. Bei einem Nano mit altem Bootloader ggf. `--fqbn arduino:avr:nano:cpu=atmega328old` verwenden.

Der Ordner `logs/` ist per `.gitignore` nicht versioniert.

## Dateien

- `TasterLogTest.ino` – der Testsketch. `logPrefix()` / `logLine()` / `logPressEvent()` geben Zeitstempel-Zeilen aus, `report()` gibt PASS/FAIL aus, `announceStep()` nennt die nächste Aufgabe, `nextStep()` wechselt den Test, `loop()` ruft zuerst `button.update()` auf und wertet danach die Ereignisse aus.
- `runLedDemo()` – LED-Demo mit 5-Sekunden-Regel (überlaufsicher per `millis()`-Differenz).
- `Anleitung.html` – Anleitung: Anschluss am Arduino Nano und alle Befehle.
- `log_serial.ps1` – PowerShell-Skript (Parameter `-Port`, `-Baud`, `-LogFile`), das die serielle Ausgabe in eine Log-Datei schreibt.

## Stand

Kompiliert; auf echter Hardware noch nicht getestet.

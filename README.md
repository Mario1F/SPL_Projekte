# SPL_Projekte

Sammlung von Arduino-Nano-Projekten (programmiert in C/C++) für das Fach SPL.

## Ordnerstruktur

- **`Aufgaben/`** – enthält ausschließlich die Aufgabenstellungen als `.md`-Dateien (eine Datei pro Aufgabe, z. B. `Aufgabe1_Taster.md`). Hier liegt **kein Code**.
  - **`Aufgaben/Abgeschlossene_Projekte/`** – Archiv für die `.md`-Dateien bereits abgeschlossener Aufgaben.
- **`OwnLibs/`** – eigene, wiederverwendbare Klassen, die in mehreren Projekten zum Einsatz kommen. Jede Klasse hat einen eigenen Unterordner mit `.h`/`.cpp`-Datei.
- **Projekt-Ordner auf oberster Ebene** (z. B. `TasterTest/`) – jeweils ein eigenständiger Arduino-Sketch (`.ino`-Datei mit demselben Namen wie der Ordner), der eine Aufgabe umsetzt/testet. Diese Ordner liegen bewusst **nicht** in `Aufgaben/`, sondern direkt im Projekt-Wurzelverzeichnis.

Diese Trennung sorgt dafür, dass Aufgabenstellung (Dokumentation) und Umsetzung (Code) unabhängig voneinander auffindbar sind.

## Klassen (`OwnLibs/`)

### `Taster` (`OwnLibs/Taster/`)

Kapselt einen Taster (Button) am Arduino.

**Aktueller Stand** (Aufgabe 1, reduzierter Umfang – siehe `Aufgaben/Abgeschlossene_Projekte/Aufgabe1_Taster.md`):
- Entprellen (Debouncing) ist **noch nicht** implementiert.
- Die Dauer für "lang gedrückt" wird entgegengenommen, aber noch nicht ausgewertet.

**Konstruktoren** (mit Standardwerten durch Überladung):

| Konstruktor | Standardwerte |
|---|---|
| `Taster(uint8_t pin)` | `negativeLogic = true`, `longPressDuration = 1000` ms |
| `Taster(uint8_t pin, bool negativeLogic)` | `longPressDuration = 1000` ms |
| `Taster(uint8_t pin, bool negativeLogic, unsigned long longPressDuration)` | – |

Parameter:

| Parameter | Bedeutung |
|---|---|
| `pin` | Pin-Nummer, an dem der Taster angeschlossen ist |
| `negativeLogic` | `true`: Taster zieht den Pin auf LOW (Pin wird als `INPUT_PULLUP` konfiguriert); `false`: Taster zieht auf HIGH (Pin wird als `INPUT` konfiguriert, externer Pulldown-Widerstand nötig) |
| `longPressDuration` | Dauer in ms, ab der ein Druck als "lang" gilt (aktuell noch ungenutzt) |

**Methoden:**

- `void update()` – muss in `loop()` als **erster Befehl** aufgerufen werden. Liest den Pin aus und aktualisiert den internen Zustand (Voraussetzung für zuverlässige Erkennung).
- `bool wasPressed()` – liefert einmalig `true`, wenn seit dem letzten Aufruf von `update()` ein neuer Tastendruck erkannt wurde (Flankenerkennung: Übergang von "nicht gedrückt" zu "gedrückt"). Das Ergebnis wird nach dem Auslesen zurückgesetzt, ein einzelner Tastendruck wird also nur einmal gemeldet.

**Geplante Erweiterungen:**
- Entprellen
- Abfrage, ob der Taster aktuell (nach Entprellen) gedrückt ist
- Erkennung "kurz gedrückt" / "lang gedrückt"
- Zeitraum-bezogene Abfragen (z. B. "wurde in den letzten X ms gedrückt")

## Projekte

### `TasterTest` (`TasterTest/`)

Testprogramm für die `Taster`-Klasse (Anforderungen siehe `Aufgaben/Abgeschlossene_Projekte/Aufgabe1_Taster.md`).

Soll-Verhalten: Eine LED leuchtet 5 Sekunden nach einem Tastendruck. Wird der Taster innerhalb dieser 5 Sekunden erneut gedrückt, verlängert sich die Leuchtdauer um weitere 5 Sekunden.

> Stand: Implementiert (LED an `LED_BUILTIN`, Taster an D2).

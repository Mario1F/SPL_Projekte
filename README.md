# SPL_Projekte

Sammlung von Arduino-Nano-Projekten (programmiert in C/C++) für das Fach SPL.

## Ordnerstruktur

- **`Aufgaben/`** – enthält ausschließlich die Aufgabenstellungen als `.md`-Dateien (eine Datei pro Aufgabe, z. B. `Aufgabe1_Taster.md`). Hier liegt **kein Code**.
  - **`Aufgaben/Abgeschlossene_Projekte/`** – Archiv für die `.md`-Dateien bereits abgeschlossener Aufgaben.
- **`OwnLibs/`** – eigene, wiederverwendbare Klassen, die in mehreren Projekten zum Einsatz kommen. Jede Klasse hat einen eigenen Unterordner mit `.h`/`.cpp`-Datei.
- **Projekt-Ordner auf oberster Ebene** (z. B. `TasterLogTest/`) – jeweils ein eigenständiger Arduino-Sketch (`.ino`-Datei mit demselben Namen wie der Ordner), der eine Aufgabe umsetzt/testet. Diese Ordner liegen bewusst **nicht** in `Aufgaben/`, sondern direkt im Projekt-Wurzelverzeichnis.

Diese Trennung sorgt dafür, dass Aufgabenstellung (Dokumentation) und Umsetzung (Code) unabhängig voneinander auffindbar sind.

## Klassen (`OwnLibs/`)

### `Taster` (`OwnLibs/Taster/`)

Kapselt einen Taster (Button) am Arduino.

**Aktueller Stand** (Aufgabe 1, reduzierter Umfang – siehe `Aufgaben/Abgeschlossene_Projekte/Aufgabe1_Taster.md`):
- Entprellen (Debouncing) ist **noch nicht** implementiert.
- `shortPress()` / `longPress()` sind implementiert (Auswertung beim Loslassen anhand `longPressDuration`).

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
| `longPressDuration` | Dauer in ms, ab der ein Druck als "lang" gilt |

**Methoden:**

- `void update()` – muss in `loop()` als **erster Befehl** aufgerufen werden. Liest den Pin aus und aktualisiert den internen Zustand (Voraussetzung für zuverlässige Erkennung).
- `bool wasPressed()` – liefert einmalig `true`, wenn seit dem letzten Aufruf von `update()` ein neuer Tastendruck erkannt wurde (Flankenerkennung: Übergang von "nicht gedrückt" zu "gedrückt"). Das Ergebnis wird nach dem Auslesen zurückgesetzt, ein einzelner Tastendruck wird also nur einmal gemeldet.
- `bool shortPress()` – liefert einmalig `true`, wenn der Taster losgelassen wurde und der Druck kürzer als `longPressDuration` war.
- `bool longPress()` – liefert einmalig `true`, wenn der Taster losgelassen wurde und der Druck mindestens `longPressDuration` lang war.

**Geplante Erweiterungen:**
- Entprellen
- Abfrage, ob der Taster aktuell (nach Entprellen) gedrückt ist
- Zeitraum-bezogene Abfragen (z. B. "wurde in den letzten X ms gedrückt")

## Projekte

### `TasterLogTest` (`TasterLogTest/`)

Interaktiver Hardware-Test für `Taster` (kurz/lang/einmalige Ereignisse, danach LED-Demo: 5 s leuchten, bei erneutem Druck Neustart; ersetzt das frühere `TasterTest`) mit Serial-Ausgabe und PowerShell-Skript `log_serial.ps1`, das die Ausgabe in eine Log-Datei schreibt. Details siehe `TasterLogTest/README.md`.

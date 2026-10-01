# Taster

Wiederverwendbare Klasse zur Ansteuerung eines einfachen Tasters am Arduino Nano.
Dateien: `Taster.h`, `Taster.cpp`, `library.properties` (Metadaten, damit der Ordner als Arduino-Bibliothek erkannt wird).

## Aktueller Stand

Umsetzung des reduzierten Umfangs aus `Aufgaben/Abgeschlossene_Projekte/Aufgabe1_Taster.md`:

- **Entprellen (Debouncing) ist noch nicht implementiert.** Ein "Prellen" des mechanischen Kontakts kann daher aktuell noch als mehrere Tastendrücke erkannt werden.
- `shortPress()` und `longPress()` sind implementiert (Auswertung beim Loslassen, ohne Entprellen). Zeitraum-Parameter gibt es noch nicht.
- Es gibt aktuell keine Methode, um den momentanen (entprellten) Zustand direkt abzufragen – nur die Flankenerkennung über `wasPressed()`.

## Klasse `Taster`

Kapselt einen digitalen Eingangspin, an dem ein Taster angeschlossen ist, liest ihn zyklisch aus und erkennt neue Tastendrücke (steigende Flanke des logischen "gedrückt"-Zustands).

### Konstruktoren

Drei überladene Konstruktoren, damit beim Anlegen eines `Taster`-Objekts sinnvolle Standardwerte verwendet werden können, wenn nicht alle Parameter angegeben werden. Alle Varianten laufen intern auf den vollständigen Konstruktor `Taster(pin, negativeLogic, longPressDuration)` hinaus.

| Konstruktor | Standardwerte für weggelassene Parameter |
|---|---|
| `Taster(uint8_t pin)` | `negativeLogic = true`, `longPressDuration = 1000` ms |
| `Taster(uint8_t pin, bool negativeLogic)` | `longPressDuration = 1000` ms |
| `Taster(uint8_t pin, bool negativeLogic, unsigned long longPressDuration)` | – (alle Werte explizit) |

Parameter:

| Parameter | Typ | Bedeutung |
|---|---|---|
| `pin` | `uint8_t` | Pin-Nummer, an dem der Taster angeschlossen ist. |
| `negativeLogic` | `bool` | `true`: Taster zieht den Pin im gedrückten Zustand auf `LOW` (Pin wird intern als `INPUT_PULLUP` konfiguriert, kein externer Widerstand nötig). `false`: Taster zieht im gedrückten Zustand auf `HIGH` (Pin wird als `INPUT` konfiguriert, dafür wird ein externer Pulldown-Widerstand benötigt). |
| `longPressDuration` | `unsigned long` | Dauer in Millisekunden, ab der ein Druck als "lang" gelten soll. Ein Druck mit mindestens dieser Dauer zählt als lang, ein kürzerer als kurz. |

Der Konstruktor konfiguriert den angegebenen Pin passend zur gewählten Logik direkt über `pinMode()`.

### Methoden

- **`void update()`**
  Muss in `loop()` als **allererster Befehl** aufgerufen werden. Liest den Pin per `digitalRead()` aus, berechnet daraus den logischen Zustand `pressed` (unter Berücksichtigung von `negativeLogic`) und vergleicht ihn mit dem zuletzt bekannten Zustand `lastPressed`. Wird dabei ein Übergang von "nicht gedrückt" zu "gedrückt" erkannt, wird intern `pressedEvent` gesetzt. Ohne regelmäßige Aufrufe von `update()` werden keine Tastendrücke erkannt.

- **`bool wasPressed()`**
  Liefert **einmalig** `true`, wenn seit dem letzten Aufruf dieser Methode ein neuer Tastendruck erkannt wurde (steigende Flanke, erkannt durch `update()`). Nach dem Auslesen wird das interne Ereignis-Flag zurückgesetzt (`pressedEvent = false`), sodass derselbe Tastendruck nicht mehrfach gemeldet wird. Wurde kein neuer Druck erkannt, liefert die Methode `false`.

- **`bool shortPress()`**
  Liefert **einmalig** `true`, wenn der Taster losgelassen wurde und die Druckdauer (Zeit zwischen steigender und fallender Flanke, gemessen mit `millis()`) **kleiner als `longPressDuration`** war. Das Ereignis wird erst beim Loslassen erkannt und beim Auslesen zurückgesetzt.

- **`bool longPress()`**
  Liefert **einmalig** `true`, wenn der Taster losgelassen wurde und die Druckdauer **mindestens `longPressDuration`** betrug. Das Ereignis wird erst beim Loslassen erkannt und beim Auslesen zurückgesetzt.

### Private Member

| Member | Bedeutung |
|---|---|
| `pin` | gespeicherte Pin-Nummer |
| `negativeLogic` | gespeicherte Logik-Einstellung |
| `longPressDuration` | gespeicherte Schwelle für "lang gedrückt" (aktuell ungenutzt) |
| `pressed` | aktueller (nicht entprellter) logischer Zustand nach dem letzten `update()` |
| `lastPressed` | logischer Zustand beim vorherigen `update()`-Aufruf, dient der Flankenerkennung |
| `pressedEvent` | wird bei einer erkannten steigenden Flanke gesetzt und von `wasPressed()` konsumiert |
| `shortPressEvent` | wird beim Loslassen nach einem kurzen Druck gesetzt und von `shortPress()` konsumiert |
| `longPressEvent` | wird beim Loslassen nach einem langen Druck gesetzt und von `longPress()` konsumiert |
| `pressStartTime` | `millis()`-Zeitpunkt der letzten steigenden Flanke |

### Beispiel

```cpp
#include "Taster.h"

Taster button(2); // Pin 2, negativeLogic = true, longPressDuration = 1000 ms

void setup() {
}

void loop() {
    button.update(); // immer als erstes in loop() aufrufen

    if (button.wasPressed()) {
        // auf neuen Tastendruck reagieren
    }
}
```

### Geplante Erweiterungen

- Entprellen (Debouncing)
- Abfrage des aktuellen (entprellten) Zustands
- Zeitraum-bezogene Abfragen (z. B. "wurde in den letzten X ms gedrückt")

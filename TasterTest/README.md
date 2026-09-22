# TasterTest

Arduino-Sketch (`TasterTest.ino`), der die Klasse `Taster` (`OwnLibs/Taster/`) testen soll.
Zugehörige Aufgabenstellung: `Aufgaben/Aufgabe1_Taster.md`.

## Aktueller Stand

**Noch nicht implementiert** – `TasterTest.ino` ist aktuell nur ein leeres Gerüst mit einer leeren `setup()`- und `loop()`-Funktion. Die eigentliche Testlogik ist laut Aufgabenstellung bewusst noch nicht umgesetzt ("Hinweis: In diesem Schritt geht es nur um das Festhalten der Anforderungen").

## Geplantes Soll-Verhalten

- Verwendet ein `Taster`-Objekt aus `OwnLibs/Taster/` zur Erkennung von Tastendrücken.
- Bei einem Tastendruck soll eine LED **5 Sekunden** leuchten.
- Wird der Taster **innerhalb dieser 5 Sekunden** erneut gedrückt, soll die Leuchtdauer der LED um weitere **5 Sekunden** verlängert werden (die Zeit wird ab dem neuen Tastendruck neu gestartet, nicht zur bestehenden Restzeit addiert).
- In `loop()` muss `taster.update()` als **erster Befehl** aufgerufen werden, damit der Tastendruck zuverlässig erkannt wird (siehe Dokumentation der `Taster`-Klasse).

## Funktionen

- **`void setup()`** – einmalige Initialisierung beim Programmstart. Aktuell leer; wird für Pin-Konfiguration der LED und Erzeugung des `Taster`-Objekts benötigt, sobald die Testlogik implementiert wird.
- **`void loop()`** – wird fortlaufend ausgeführt. Aktuell leer; wird künftig `taster.update()` als ersten Befehl sowie die Logik zum Ein-/Ausschalten der LED anhand der 5-Sekunden-Regel enthalten.

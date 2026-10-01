# TasterTest

Arduino-Sketch (`TasterTest.ino`), der die Klasse `Taster` (`OwnLibs/Taster/`) testet.
Zugehörige Aufgabenstellung: `Aufgaben/Abgeschlossene_Projekte/Aufgabe1_Taster.md`.

## Aktueller Stand

Implementiert. Der Sketch setzt das geforderte Testverhalten um:

- Bei einem Tastendruck leuchtet die LED **5 Sekunden**.
- Wird der Taster **innerhalb dieser 5 Sekunden** erneut gedrückt, startet die Zeit neu (die LED leuchtet ab dem neuen Druck wieder 5 Sekunden; es wird nicht zur Restzeit addiert).

Da `Taster` noch kein Entprellen besitzt, kann ein prellender Taster in seltenen Fällen mehrfach auslösen – für dieses Testverhalten ist das unkritisch, da jeder Auslöser nur die Zeit neu startet.

## Verdrahtung

| Bauteil | Pin |
|---|---|
| Taster | D2 (gegen GND, `INPUT_PULLUP`, negative Logik) |
| LED | `LED_BUILTIN` (D13, On-Board-LED) |

## Build-Hinweis

Die Klasse liegt in `OwnLibs/Taster/` (mit `library.properties`, also eine gültige Arduino-Bibliothek). Damit der Sketch kompiliert, muss `OwnLibs` als Bibliotheksordner bekannt sein:

```
arduino-cli compile --fqbn arduino:avr:nano --libraries OwnLibs TasterTest
```

Alternativ `OwnLibs/Taster` in den Arduino-`libraries`-Ordner kopieren. Hinweis: Der Kompiliervorgang wurde bisher nicht getestet (`arduino-cli` ist auf diesem Rechner nicht installiert).

## Funktionen / Konstanten

- **`BUTTON_PIN`** (`2`), **`LED_PIN`** (`LED_BUILTIN`), **`LED_ON_DURATION`** (`5000` ms) – Konfiguration.
- **`Taster button`** – globales Taster-Objekt (Standardwerte: negative Logik).
- **`ledOn`** / **`ledStartTime`** – Zustand der LED und Startzeitpunkt (`millis()`) der aktuellen Leuchtphase.
- **`void setup()`** – konfiguriert den LED-Pin als Ausgang und schaltet die LED aus.
- **`void loop()`** – ruft zuerst `button.update()` auf. Meldet `button.wasPressed()` einen Druck, wird die LED eingeschaltet und `ledStartTime` neu gesetzt. Ist die LED an und sind seit `ledStartTime` mindestens 5000 ms vergangen (überlaufsicher per Differenzbildung), wird sie ausgeschaltet.

# Aufgabe 2 – LED-Streifen-Steuerung

## Projekt

Hardware:

- Arduino Nano
- Taster
- WS2812-LED-Streifen
- HM-10 Bluetoothmodul

Funktionalität: Der LED-Streifen stellt verschiedene Muster dar. Umgeschaltet wird über den Taster; über eine Handyapp soll Feineinstellung möglich sein (z. B. RGB-Farbe, Geschwindigkeit des Lauflichts).

Software: Handyapp mit **RemoteXY**, Ansteuerung des Streifens mit der **Adafruit NeoPixel**-Library.

## Architektur (Grundprinzipien)

1. **Jeder Programmteil ist nur für eine Hardwarekomponente zuständig.** In den Methoden werden nicht mehrere Hardwarekomponenten vermischt (z. B. keine Tasterabfrage im Lauflicht). Begründung: Sonst müsste man die Tasterabfrage (und später Bluetooth) in jedes zeitabhängige Muster einbauen – unpraktisch und fehleranfällig.
2. **Kein Programmteil blockiert andere.** Kein `delay()` (stattdessen `millis()`), keine `while`-Schleifen, die auf etwas warten. Zeitabhängige Muster werden nicht in einer `for`-Schleife durchgespielt, sondern machen pro Aufruf nur einen Schritt, falls es dafür Zeit ist; sonst Rückkehr zur `loop()`.
3. Die Blöcke kommunizieren über globale Variablen, z. B. die Mustervariable: wird vom Taster geändert und bestimmt das Muster in der LED-Steuerung. Möglichst mit `enum` und Modulo lösen.
4. Für jedes Muster eine eigene Methode; ein `switch` wählt anhand der Mustervariable das Muster aus. Beim letzten Muster springt der nächste Tastendruck zurück zum ersten (Modulo `%`).
5. `show()` des Streifens nur an **einer einzigen Stelle** und nicht schneller als das Auge sieht (ca. 20–25 fps), da das Bluetoothmodul möglicherweise denselben Hardware-Timer wie der Streifen verwendet.

## Entwicklungsschritte

1. **Schritt 1:** Taster und LED-Streifen – mehrere Muster mit dem Taster durchschalten.
2. **Schritt 2:** Bluetoothmodul (HM-10) und RemoteXY-App einbinden.

## Aufgaben

1. Mit dem Taster zwischen zwei Mustern umschalten: Streifen ganz rot / ganz blau.
2. Weitere Muster, z. B. Lauflicht, Regenbogenmuster, wanderndes Regenbogenmuster, flackerndes Muster.

## Umfang für jetzt

- Nur **Schritt 1**, Aufgabe 1 (Muster rot / blau). Weitere Muster und Bluetooth folgen später.
- Verdrahtung: Taster an **D2** (gegen GND, `INPUT_PULLUP`), LED-Streifen-Daten an **D6**, **30 LEDs**.

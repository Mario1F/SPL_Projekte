# Aufgabe 1 – Klasse zur Verwaltung eines Tasters

## Ziel

Eine Klasse (z. B. `Button`), die einen Taster kapselt: entprellt ihn und meldet verschiedene Zustände/Ereignisse (aktuell gedrückt, kurz gedrückt, lang gedrückt).

## Anforderungen (Gesamtumfang)

1. **Entprellen**: Die Klasse soll den Taster entprellen (Debouncing), damit ein einzelner Tastendruck nicht als mehrere Ereignisse erkannt wird.
2. **Aktueller Zustand**: Melden, ob der Taster im Moment gedrückt ist (nach dem Entprellen).
3. **Kurzer Druck**: Melden, ob der Taster kurz gedrückt wurde.
4. **Langer Druck**: Melden, ob der Taster lang gedrückt wurde.
5. **Konstruktor**: `Button(pin, Dauer_lang)` legt fest:
   - die Pinnummer,
   - die Logik (positiv/negativ, z. B. Pullup vs. Pulldown),
   - die Dauer, ab der ein Druck als "lang" gilt.
6. **Standardwerte / Überladung**: Mehrere Konstruktoren mit unterschiedlichen Parametern, damit sinnvolle Standardwerte verwendet werden können, wenn nicht alle Parameter angegeben werden.
7. **Zeitraum-Abfragen**: Methoden wie `wasPressed()` und `longPress()` sollen prüfen können, ob der Taster innerhalb eines bestimmten Zeitraums gedrückt wurde (nicht nur im aktuellen Moment).
8. **update()-Aufruf**: In der `loop()` muss `taster.update()` als **erster Befehl** aufgerufen werden, damit `digitalRead()` ausreichend oft ausgeführt wird (für zuverlässiges Entprellen und Zeitmessung).

## Vorläufiger Umfang für Aufgabe 1

Für den ersten Schritt soll **nur ein reduzierter Teil** umgesetzt werden:

- **Kein Entprellen** (wird später ergänzt).
- Nur folgende Teile ausprogrammieren:
  - Konstruktor
  - `update()`
  - `wurdeGedrückt()`
- Die Dauer für "lang gedrückt" ist in dieser Version **noch nicht relevant** (kann ignoriert bzw. später ergänzt werden).

## Testprogramm (nur Anforderung, noch nicht programmieren)

Verhalten, das getestet werden soll:

- Bei einem Tastendruck soll eine LED **5 Sekunden** leuchten.
- Wird die Taste **innerhalb dieser 5 Sekunden** erneut gedrückt, soll die LED um weitere **5 Sekunden** verlängert leuchten (die Zeit wird also neu gestartet, nicht addiert über eine separate Zählung).

> Hinweis: In diesem Schritt geht es nur um das Festhalten der Anforderungen – die Implementierung (Klasse und Testprogramm) folgt in einem späteren Schritt.

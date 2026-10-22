# Aufgabe 3 – Muster und LED-Anzahl dauerhaft speichern (EEPROM)

Erweiterung von Aufgabe 2 (`Aufgabe2_LedStreifen.md`).

## Aufgabenstellung

1. Bei **langem Druck** auf den Taster soll das aktuelle Muster dauerhaft gespeichert werden (EEPROM). Nach Unterbrechung der Stromversorgung startet dieses Muster.
2. Als Rückmeldung blinken die ersten 5 LEDs 3-mal. Sind sie wieder aus, geht es normal weiter.
3. Bei **mehr als 3 s** Drücken kann der Nutzer die **Anzahl der LEDs** eingeben: Solange der Taster gedrückt ist, wird eine LED nach der anderen eingeschaltet. Beim Loslassen wird diese Anzahl gespeichert. Sie gilt für alle Muster und auch nach dem Ausschalten.

## Festlegungen (mit dem Nutzer besprochen)

- Muster wechseln: `shortPress()` (beim Loslassen, < 1 s), nicht mehr `wasPressed()`, sonst würde jeder lange Druck zuerst das Muster wechseln.
- 1 s bis 3 s halten, loslassen: Muster speichern.
- Ab 3 s halten: LED-Anzahl einstellen, **1 LED alle 200 ms**, Start mit 1 LED, stoppt beim Maximum (**30**). Beim Loslassen wird die Anzahl gespeichert, das Muster wird dabei nicht zusätzlich gespeichert.
- Rückmeldung: **grün**, 200 ms an / 200 ms aus, 3-mal, nach dem Speichern von Muster **und** Anzahl; bei weniger als 5 LEDs entsprechend weniger.
- Die LED-Anzahl gilt für alle Muster; LEDs hinter der Anzahl bleiben dunkel.
- Das EEPROM ist eine eigene Komponente (Klasse `Settings`), mit Magic-Byte und Prüfung der Werte beim Laden (erster Start: Standardwerte). Schreiben nur bei geänderten Werten (`EEPROM.update()`).
- Neue Muster werden immer hinten im `enum Pattern` ergänzt, damit gespeicherte Indizes ihre Bedeutung behalten.

## Plan

1. Aufgabe und Plan als `.md` anlegen (diese Datei).
2. `OwnLibs/Settings/`: EEPROM-Klasse (Magic-Byte, Muster, LED-Anzahl; Laden mit Prüfung und Standardwerten; Speichern).
3. `OwnLibs/LedStrip/` erweitern: aktive LED-Anzahl (`setLedCount`), nicht blockierende Rückmeldung (`startFeedback`), Vorschau beim Einstellen (`setPreviewCount`).
4. Sketch `LedStrip/LedStrip.ino`: Werte beim Start laden, Tasterstufen auswerten (kurz / 1–3 s / > 3 s), Speichern auslösen.
5. READMEs aktualisieren, kompilieren, committen.

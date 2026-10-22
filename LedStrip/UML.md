# UML-Darstellungen LedStrip-Projekt

Die Diagramme sind in Mermaid geschrieben und werden auf GitHub sowie in VS Code (mit Mermaid-Erweiterung) direkt dargestellt.

## 1. Klassendiagramm

Der Sketch verbindet die drei Klassen. Die Klassen kennen sich untereinander nicht; jede ist nur für ihre eigene Hardware zuständig (Taster-Pin, LED-Streifen, EEPROM).

```mermaid
classDiagram
    class Taster {
        -uint8_t pin
        -bool negativeLogic
        -unsigned long longPressDuration
        -unsigned long debounceTime
        -bool pressed
        -unsigned long pressStartTime
        +Taster(pin)
        +Taster(pin, negativeLogic)
        +Taster(pin, negativeLogic, longPressDuration)
        +Taster(pin, negativeLogic, longPressDuration, debounceTime)
        +update() void
        +wasPressed() bool
        +shortPress() bool
        +longPress() bool
        +isPressed() bool
        +isPressedFor(ms) bool
        +wasPressedWithin(ms) bool
    }

    class LedStrip {
        -Adafruit_NeoPixel strip
        -uint16_t maxLedCount
        -uint16_t ledCount
        -unsigned long frameInterval
        -uint16_t previewCount
        -bool feedbackActive
        +LedStrip(pin, maxLedCount)
        +LedStrip(pin, maxLedCount, frameInterval)
        +begin() void
        +setBrightness(brightness) void
        +setLedCount(ledCount) void
        +getLedCount() uint16_t
        +getMaxLedCount() uint16_t
        +startFeedback() void
        +setPreviewCount(count) void
        +update(pattern) void
        -patternRed() void
        -patternBlue() void
        -renderFeedback() void
    }

    class Pattern {
        <<enumeration>>
        PATTERN_RED
        PATTERN_BLUE
        PATTERN_COUNT
    }

    class Settings {
        -uint8_t patternCount
        -uint8_t maxLedCount
        -uint8_t pattern
        -uint8_t ledCount
        +Settings(patternCount, maxLedCount, defaultPattern, defaultLedCount)
        +begin() void
        +getPattern() uint8_t
        +getLedCount() uint8_t
        +savePattern(pattern) void
        +saveLedCount(ledCount) void
        -writeMagic() void
    }

    class Sketch {
        <<LedStrip.ino>>
        +Pattern pattern
        +bool counting
        +uint16_t countedLeds
        +setup() void
        +loop() void
    }

    class Adafruit_NeoPixel {
        <<external library>>
    }

    class EEPROM {
        <<Arduino library>>
    }

    Sketch --> Taster : button
    Sketch --> LedStrip : strip
    Sketch --> Settings : settings
    Sketch ..> Pattern : globale Variable
    LedStrip ..> Pattern : update(pattern)
    LedStrip *-- Adafruit_NeoPixel
    Settings ..> EEPROM
```

## 2. Zustandsdiagramm der Tasterbedienung

Beschreibt, was je nach Haltedauer beim Loslassen passiert.

```mermaid
stateDiagram-v2
    [*] --> Idle
    Idle --> Pressed : Taster gedrückt
    Pressed --> Idle : losgelassen unter 1 s - nächstes Muster
    Pressed --> LongHold : 1 s erreicht
    LongHold --> Idle : losgelassen - Muster speichern und Blinken
    LongHold --> Counting : 3 s erreicht
    Counting --> Counting : alle 200 ms eine LED mehr bis maximal 30
    Counting --> Idle : losgelassen - LED-Anzahl speichern und Blinken
```

## 3. Sequenzdiagramm einer `loop()`-Runde

```mermaid
sequenceDiagram
    participant L as loop()
    participant T as Taster
    participant S as LedStrip
    participant E as Settings

    L->>T: update()
    L->>T: isPressedFor(3000)
    alt gehalten über 3 s
        L->>S: setPreviewCount(countedLeds)
    end
    L->>T: shortPress()
    opt kurzer Druck
        L->>L: pattern = (pattern + 1) % PATTERN_COUNT
    end
    L->>T: longPress()
    opt langer Druck losgelassen
        alt counting
            L->>S: setPreviewCount(0)
            L->>S: setLedCount(countedLeds)
            L->>E: saveLedCount(countedLeds)
        else
            L->>E: savePattern(pattern)
        end
        L->>S: startFeedback()
    end
    L->>S: update(pattern)
    Note over S: show() nur alle 40 ms
```

## 4. Aktivitätsdiagramm von `LedStrip::update()`

```mermaid
flowchart TD
    A([update pattern]) --> B[Puffer löschen]
    B --> C{previewCount > 0?}
    C -- ja --> D[erste previewCount LEDs weiß]
    C -- nein --> E{Muster?}
    E -- PATTERN_RED --> F[ledCount LEDs rot]
    E -- PATTERN_BLUE --> G[ledCount LEDs blau]
    F --> H[renderFeedback]
    G --> H
    H --> I{40 ms seit letztem show?}
    D --> I
    I -- ja --> J[strip.show]
    I -- nein --> K([zurück zu loop])
    J --> K
```

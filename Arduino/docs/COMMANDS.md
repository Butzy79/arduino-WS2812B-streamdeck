# WS2812B Controller - Serial Commands

This document describes the serial communication protocol used by the Arduino WS2812B Controller.

The Arduino receives commands through USB Serial.

Default communication settings:

- Baud rate: 9600
- Line ending: Newline (`\n`)

---

# Command Overview

| Command | Description |
|---|---|
| OFF | Turn LED strip OFF |
| ON | Restore previous saved state |
| Bxxx | Set brightness |
| Crrggbb | Set HEX RGB color |
| P NAME | Load color preset |
| Rxxx | Start Rainbow mode |

---

# Power Commands

## OFF
Turns the LED strip OFF.

The controller keeps the last saved:

- Color
- Brightness
- Mode
- Rainbow speed

The state can be restored using the ON command.

Example:
OFF
Result:
LED strip OFF

---

## ON
ON
Turns the LED strip ON and restores the previous saved state.

Examples:

After:
CFF0000
B050
OFF
Sending:
ON
will restore:
Red color
50% brightness

---

# Brightness Control

## Format
Range:
000 - 100
Value represents percentage brightness.

Examples:
B000
Brightness: 0%
B050
Brightness: 50%

Brightness changes are saved to EEPROM.

---

# HEX Color Command

## Format

RGB color using HEX format.

The command automatically switches the controller to STATIC COLOR mode.

Format:
C + RED + GREEN + BLUE
Each channel uses two HEX characters.

---

## Examples

### Red
CFF0000
RGB:
Red:   255
Green: 0
Blue:  0

---

### Green
C00FF00
RGB:
Red:   0
Green: 255
Blue:  0

---

HEX colors are saved to EEPROM.

---

# Preset Colors

## Format
P NAME

Loads a predefined color.

Preset colors are configured inside the Arduino code.

Current presets:

P RED
P GREEN
P BLUE
P YELLOW
P ORANGE
P WHITE
P PURPLE

---

Preset colors automatically stop Rainbow mode.

---

# Rainbow Mode

## Format

Rxxx

Starts Rainbow animation.

The value controls the animation speed.

Range:
001 - 100

---

Examples:

Fast rainbow:
R001

Slow rainbow:
R020
---

Rainbow speed is saved to EEPROM.

---

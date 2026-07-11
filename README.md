# WS2812B Stream Deck Controller

Arduino based controller for WS2812B LED strips controlled by Elgato Stream Deck.

The project allows static colors, brightness control and optional rainbow effects.

The LED strip is controlled through USB serial commands.

---

# Features

- ON / OFF control
- Restore last state after power cycle
- Static RGB colors
- HEX color commands
- Preset colors
- Adjustable brightness
- Rainbow mode with speed control
- EEPROM state saving
- Stream Deck integration

---

# Hardware

## Required

- Arduino Micro
- WS2812B LED strip
- USB cable
- Elgato Stream Deck MK.2


## Wiring

Arduino Micro:

| Arduino | WS2812B |
|---|---|
| 5V | +5V |
| GND | GND |
| D6 | DATA |


---

# Arduino Setup

## Install Arduino IDE

Download:

https://www.arduino.cc/en/software


## Install Libraries

Arduino IDE:

Tools -> Manage Libraries

Install:

- FastLED


## Upload

Open:

Arduino/

WS2812B_Controller/

WS2812B_Controller.ino


Select:

Board:
Arduino Micro

Port:
Arduino USB Port


Upload.

## Hardware Wiring

Arduino Micro -> WS2812B

5V   -> Red wire
GND  -> White wire
D6   -> Green wire (DATA)

LED strip:
WS2812B 5V
30 LEDs

---

# Serial Commands

## Power

OFF

Turn LEDs off.

ON

Restore previous state.


## Brightness

Bxxx

Example:

B050

Set brightness to 50%.


## HEX Color

Crrggbb

Examples:

CFF0000

Red


C00FF00

Green


## Presets

P RED

P GREEN

P BLUE

P ORANGE

P WHITE


## Rainbow

R005

Start rainbow mode.

The number controls speed.


---

# Stream Deck

Stream Deck integration is located in:

/StreamDeck


Buttons:

- ON
- OFF
- RED
- GREEN
- BLUE
- CUSTOM COLORS


---

# Future Development

- Stream Deck plugin
- Multiple LED zones
- SimHub integration
- Profiles

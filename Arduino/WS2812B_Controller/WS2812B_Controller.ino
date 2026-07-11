#define DEBUG false

#include <FastLED.h>
#include <EEPROM.h>
#include <avr/wdt.h>
// =====================================================
// SERIAL COMMANDS REFERENCE
// =====================================================
// POWER CONTROL
// -----------------------------------------------------
// OFF
//     Turn LED strip OFF
//     Keeps the last saved state in memory
//
// ON
//     Turn LED strip ON
//     Restores the last saved mode, color,
//     brightness and rainbow settings
//
//
// BRIGHTNESS CONTROL
// -----------------------------------------------------
// Bxxx
//     Set brightness from 0 to 100 percent
//
// Examples:
// B000  -> 0% brightness
// B050  -> 50% brightness
// B100  -> 100% brightness
//
//
// HEX COLOR CONTROL
// -----------------------------------------------------
// Crrggbb
//     Set static color using RGB HEX value
//     Automatically stops Rainbow mode
//
// Examples:
// CFF0000  -> Red
// C00FF00  -> Green
// C0000FF  -> Blue
// CFFFFFF  -> White
// CFFFF00  -> Yellow
//
//
// PRESET COLORS
// -----------------------------------------------------
// P NAME
//     Load a predefined color preset
//
// Available presets:
// P RED
// P GREEN
// P BLUE
// P YELLOW
// P ORANGE
// P WHITE
// P PURPLE
//
//
// RAINBOW EFFECT
// -----------------------------------------------------
// Rxxx
//     Start Rainbow mode
//     Value controls animation speed
//
// Examples:
// R001  -> Fast Rainbow
// R005  -> Medium Rainbow
// R020  -> Slow Rainbow
//
//
// NOTES
// -----------------------------------------------------
// - OFF does not erase the saved state
// - ON restores the previous state
// - Cxxxxxx switches back to static color mode
// - P NAME switches back to static color mode
// - Rainbow settings are stored in EEPROM
// - All LEDs always show the same static color
//
// =====================================================

// =====================================================
// USER CONFIGURATION
// =====================================================

// LED configuration
#define LED_PIN 6
#define NUM_LEDS 30

// Brightness limits
#define DEFAULT_BRIGHTNESS 50


// =====================================================
// PRESET COLORS
// Modify these values if you want different colors
// Format: Red, Green, Blue (0-255)
// =====================================================

#define PRESET_RED       CRGB(255,0,0)
#define PRESET_GREEN     CRGB(0,255,0)
#define PRESET_BLUE      CRGB(0,0,255)
#define PRESET_YELLOW    CRGB(255,255,0)
#define PRESET_ORANGE    CRGB(255,80,0)
#define PRESET_WHITE     CRGB(255,255,255)
#define PRESET_PURPLE    CRGB(180,0,255)


// =====================================================
// EEPROM MEMORY ADDRESS
// =====================================================

#define EEPROM_COLOR_R     0
#define EEPROM_COLOR_G     1
#define EEPROM_COLOR_B     2
#define EEPROM_BRIGHTNESS  3
#define EEPROM_MODE        4
#define EEPROM_RAINBOW_SPEED 5
#define EEPROM_STARTUP_ON 6

// =====================================================
// MODES
// =====================================================

#define MODE_STATIC 0
#define MODE_RAINBOW 1


// =====================================================
// GLOBAL VARIABLES
// =====================================================

CRGB leds[NUM_LEDS];

CRGB currentColor = PRESET_RED;

uint8_t brightness = DEFAULT_BRIGHTNESS;

uint8_t currentMode = MODE_STATIC;

uint8_t rainbowSpeed = 5;

bool ledEnabled = false;

uint8_t rainbowHue = 0;

void debugMessage(String msg) {
  if(DEBUG) {
    Serial.println(msg);
  }
}

// =====================================================
// SAVE STATE TO EEPROM
// =====================================================

void saveState()
{
  debugMessage("Current Color R: " + String(currentColor.r));
  debugMessage("Current Color G: " + String(currentColor.g));
  debugMessage("Current Color B: " + String(currentColor.b));
  debugMessage("Current Brightness: " + String(brightness));
  debugMessage("Current Mode: " + String(currentMode));
  debugMessage("Current Rainbow Speed: " + String(rainbowSpeed));

  EEPROM.update(EEPROM_COLOR_R, currentColor.r);
  EEPROM.update(EEPROM_COLOR_G, currentColor.g);
  EEPROM.update(EEPROM_COLOR_B, currentColor.b);

  EEPROM.update(EEPROM_BRIGHTNESS, brightness);

  EEPROM.update(EEPROM_MODE, currentMode);

  EEPROM.update(EEPROM_RAINBOW_SPEED, rainbowSpeed);
}


// =====================================================
// LOAD STATE FROM EEPROM
// =====================================================

void loadState()
{
  currentColor.r = EEPROM.read(EEPROM_COLOR_R);
  currentColor.g = EEPROM.read(EEPROM_COLOR_G);
  currentColor.b = EEPROM.read(EEPROM_COLOR_B);

  brightness = EEPROM.read(EEPROM_BRIGHTNESS);

  currentMode = EEPROM.read(EEPROM_MODE);

  rainbowSpeed = EEPROM.read(EEPROM_RAINBOW_SPEED);


  // Safety checks
  if (brightness > 100)
    brightness = DEFAULT_BRIGHTNESS;

  if (currentMode > MODE_RAINBOW)
    currentMode = MODE_STATIC;

  if (rainbowSpeed == 0)
    rainbowSpeed = 5;
}

// =====================================================
// RESET CONTROLLER
// Restore factory defaults and reboot Arduino
// =====================================================

void resetController()
{
  // Default values
  currentColor = PRESET_BLUE;
  brightness = 40;
  currentMode = MODE_STATIC;
  rainbowSpeed = 5;

  // Save defaults
  saveState();

  // Request automatic startup ON after reboot
  EEPROM.update(EEPROM_STARTUP_ON, 1);
  
  // Turn LEDs OFF before reboot
  ledEnabled = false;
  showOff();

  delay(500);

  // Enable watchdog reset
  wdt_enable(WDTO_15MS);

  while(true)
  {
    // Wait for reboot
  }
}

// =====================================================
// APPLY STATIC COLOR
// =====================================================

void showStaticColor()
{
  debugMessage("Set color new: " + String(brightness) + " -> " + String(map(brightness,0,100,0,255)));
  FastLED.setBrightness(map(brightness,0,100,0,255));

  debugMessage("Color = " + String(currentColor.r) + "," + String(currentColor.g) + "," + String(currentColor.b));
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = currentColor;
  }
  FastLED.show(); 
}


// =====================================================
// APPLY OFF
// =====================================================

void showOff()
{
  fill_solid(
    leds,
    NUM_LEDS,
    CRGB::Black
  );

  FastLED.show();
}


// =====================================================
// RAINBOW EFFECT
// =====================================================

void showRainbow()
{
  FastLED.setBrightness(map(brightness,0,100,0,255));

  fill_rainbow(
    leds,
    NUM_LEDS,
    rainbowHue,
    7
  );

  FastLED.show();

  rainbowHue += rainbowSpeed;

  delay(20);
}


// =====================================================
// UPDATE LED OUTPUT
// =====================================================

void updateLED()
{

  debugMessage("Led Enabled: " + String(ledEnabled));
  if (!ledEnabled)
  {
    showOff();
    return;
  }

  debugMessage("Is Static? " + String(currentMode == MODE_STATIC));
  if (currentMode == MODE_STATIC)
  {
    showStaticColor();
  }
}


// =====================================================
// HEX COLOR PARSER
// =====================================================

void setHexColor(String hex)
{
  if(hex.length()!=6)
    return;


  long number = strtol(
    hex.c_str(),
    NULL,
    16
  );


  currentColor.r = (number >> 16) & 0xFF;
  currentColor.g = (number >> 8) & 0xFF;
  currentColor.b = number & 0xFF;


  currentMode = MODE_STATIC;

  saveState();

  updateLED();
}


// =====================================================
// PRESET COLOR SELECTOR
// =====================================================

void setPreset(String name)
{

  name.toUpperCase();


  if(name=="RED")
    currentColor = PRESET_RED;

  else if(name=="GREEN")
    currentColor = PRESET_GREEN;

  else if(name=="BLUE")
    currentColor = PRESET_BLUE;

  else if(name=="YELLOW")
    currentColor = PRESET_YELLOW;

  else if(name=="ORANGE")
    currentColor = PRESET_ORANGE;

  else if(name=="WHITE")
    currentColor = PRESET_WHITE;

  else if(name=="PURPLE")
    currentColor = PRESET_PURPLE;

  else
    return;


  currentMode = MODE_STATIC;

  saveState();

  updateLED();
}


// =====================================================
// SERIAL COMMAND PROCESSOR
// =====================================================

void processCommand(String cmd)
{

  cmd.trim();
  cmd.toUpperCase();
  debugMessage("CMD: " + cmd);
  // Turn OFF
  if(cmd=="OFF")
  {
    ledEnabled=false;
    saveState();
    showOff();
  }

  // Factory reset
  else if(cmd=="RESET")
  {
    resetController();
  }

  // Turn ON
  else if(cmd=="ON")
  {
    ledEnabled=true;
    updateLED();
  }
  else if(cmd=="INFO")
  {
    Serial.println("DEVICE:Led Stripe Simracing");
    Serial.println("VERSION:1.0");
    Serial.println("LEDS:30");
    Serial.println("READY");
  }
  // Brightness Bxxx
  else if(cmd.startsWith("B"))
  {
    int value = cmd.substring(1).toInt();

    if(value>=0 && value<=100)
    {
      brightness=value;
      saveState();
      updateLED();
    }
  }


  // HEX COLOR Cxxxxxx
  else if(cmd.startsWith("C"))
  {
    setHexColor(
      cmd.substring(1)
    );
  }


  // PRESET COLOR P NAME
  else if(cmd.startsWith("P "))
  {
    setPreset(
      cmd.substring(2)
    );
  }


  // RAINBOW Rxxx
  else if(cmd.startsWith("R"))
  {
    int speed = cmd.substring(1).toInt();

    if(speed>=1 && speed<=100)
    {
      rainbowSpeed=speed;
      currentMode=MODE_RAINBOW;

      saveState();

      ledEnabled=true;
    }
  }
}


// =====================================================
// SETUP
// =====================================================

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("DEVICE:Led Stripe Simracing");
  Serial.println("VERSION:1.0");
  Serial.println("READY");

  FastLED.addLeds<WS2812B,LED_PIN,GRB>
  (
    leds,
    NUM_LEDS
  );
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);

  loadState();

  // Check if RESET requested startup ON
  if (EEPROM.read(EEPROM_STARTUP_ON) == 1) {
    ledEnabled = true;
    EEPROM.update(EEPROM_STARTUP_ON, 0);
    updateLED();
  } else {
    // Normal boot always OFF
    ledEnabled = false;
    showOff();
  }
  debugMessage("==============================");
  debugMessage("WS2812B CONTROLLER STARTED");
  debugMessage("Started: " + String(millis()));
  debugMessage("==============================");
  debugMessage("Brightness: " + String(brightness));
  debugMessage("Mode: " + String(currentMode));
}


// =====================================================
// MAIN LOOP
// =====================================================

void loop()
{

  if(Serial.available()) {
    String command =
      Serial.readStringUntil('\n');

    processCommand(command);
  }

  if(
    ledEnabled &&
    currentMode==MODE_RAINBOW
  )
  {
    showRainbow();
  }

}

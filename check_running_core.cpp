#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>
#include <WROVER_KIT_LCD.h>

// Controller Class
WROVER_KIT_LCD screen;


void setup() {
  Serial.begin(115200);
  screen.begin();
  screen.fillScreen(WROVER_BLACK); //Clear screen
  screen.setCursor(0, 0); //Set upper left corner
  screen.setTextColor(WROVER_WHITE); //Set text colour
  screen.setTextSize(1); //Set font size
  screen.print("setup() running on core ");
  screen.println(xPortGetCoreID());
}

void loop() {
  screen.print("loop() running on core ");
  screen.println(xPortGetCoreID());
}
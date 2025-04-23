#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

bool lcdWorking = false;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Scanning I2C devices...");

  byte count = 0;
  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("I2C device found at address 0x");
      Serial.println(address, HEX);
      count++;

      if (address == 0x27 || address == 0x3F) {
        lcd = LiquidCrystal_I2C(address, 16, 2);
        lcd.init();
        lcd.backlight();
        lcdWorking = true;
      }
    }
    delay(5);
  }

  if (count == 0) {
    Serial.println("No I2C devices found.");
  } else {
    Serial.println("I2C scan finished.");
  }

  if (lcdWorking) {
    lcd.setCursor(0, 0);
    lcd.print("LCD working!");
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("Test completed.");
  } else {
    Serial.println("LCD not found or not initialized.");
  }
}

void loop() {
}
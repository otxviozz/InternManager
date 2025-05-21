#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pinos do RFID
#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

// LCD I2C no endereço 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Buzzer
const int buzzerPin = 2;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  lcd.init();
  lcd.backlight();

  pinMode(buzzerPin, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Aproxime o cartao");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Converte UID para string
  String uidString = "";
  for (byte i = 0; i < rfid.uid.size; i++) {
    uidString += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
    uidString += String(rfid.uid.uidByte[i], HEX);
  }
  uidString.toUpperCase();

  Serial.print("Cartao detectado! UID: ");
  Serial.println(uidString);

 String json = "{";
  json += "\"uid\":\"" + uidString + "\"";
  json += "}";

  Serial.println(json);

  // Toca o buzzer
  tone(buzzerPin, 1000);
  delay(300);
  noTone(buzzerPin);

  delay(2500); // Tempo para ler
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aproxime o cartao");

  // Finaliza comunicação
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

const int buzzerPin = 2;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Testing buzzer...");
}

void loop() {
  tone(buzzerPin, 1000); // 1000 Hz
  delay(300);
  noTone(buzzerPin);
  delay(300);

  tone(buzzerPin, 1500); // 1500 Hz
  delay(300);
  noTone(buzzerPin);
  delay(1000);
}
// Auteur: AlexChulo
// Bron: https://brightspace.avans.nl/
// Definieer een array van pinnen voor de LEDs
int ledPins[] = {13, 10, 9, 8, 7, 6, 5, 4};

void setup() {
  // Stel elke pin in de array in op OUTPUT
  for (int i = 0; i < sizeof(ledPins)/sizeof(ledPins[0]); i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void knipper(int pin) {
  // Zet de LED aan
  digitalWrite(pin, HIGH);
  // Wacht 1 seconde
  delay(1000);
  // Zet de LED uit
  digitalWrite(pin, LOW);
  // Wacht 1 seconde
  delay(1000);
}

void loop() {
  // Loop door elke pin van links naar rechts
  for (int i = 0; i < sizeof(ledPins)/sizeof(ledPins[0]); i++) {
    knipper(ledPins[i]);
  }
  
  // Loop door elke pin van rechts naar links
  for (int i = sizeof(ledPins)/sizeof(ledPins[0]) - 2; i >= 1; i--) {
    knipper(ledPins[i]);
  }
}

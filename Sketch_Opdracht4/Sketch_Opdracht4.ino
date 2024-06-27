// Auteur: AlexChulo
// Bronnen: 
// - https://brightspace.avans.nl/
// - 4# How to Code Potentiometers (Complete Guide) - MIDI Programming for the Arduino (youtube.com)

const int ledPins[] = {11, 10, 9, 6, 5, 3}; // Array voor pinnnen LED's
const int potPin = A0; // Gebruikte pin voor potentiometer
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]); // Berekent het aantal LED's in de array

int potState = 0; // Variabele voor de staat van de potentiometer
int activeLeds = 0; // Variabele voor het aantal actieve LED's

void setup() {
  setupLeds();
}

void loop() {
  leesPotentiometer();
  updateLeds();
}

// Zet de LED-pinnen als output
void setupLeds() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT); // Zet de huidige pin als output
  }
}

// Lees de waarde van de potentiometer en update het aantal actieve LED's
void leesPotentiometer() {
  potState = analogRead(potPin); // Lees de waarde van de potentiometer
  activeLeds = map(potState, 0, 1023, numLeds, 0); // Mapping van potentiometerwaarde naar aantal actieve LED's
}

// Update de status van de LEDs op basis van de potentiometerwaarde
void updateLeds() {
  for (int i = 0; i < numLeds; i++) {
    if (i < activeLeds) {
      digitalWrite(ledPins[i], HIGH); // Zet de LED aan
    } else {
      digitalWrite(ledPins[i], LOW); // Zet de LED uit
    }
  }
}

int ledPins[] = {11, 10, 9, 6, 5, 3}; // Array voor pinnnen LED's
int potState = 0; // Variabele voor de staat van de potentiometer
int potPin = A0; // Gebruikte pin voor potentiometer
int numLeds = sizeof(ledPins) / sizeof(ledPins[0]); // Berekent het aantal LED's in de array
int activeLeds = 0; // Variabele voor het aantal actieve LED's

void setup() {
  // Voor elke pin in de array, zet als output
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT); // Zet de huidige pin als output
  }
}

void loop() {
  potState = analogRead(potPin); // Lees de waarde van de potentiometer
  // Mapping van potentiometerwaarde naar aantal actieve LED's
  // Wanneer potState 0 is, zijn alle LEDs aan
  // Wanneer potState 1023 is, zijn alle LEDs uit
  activeLeds = map(potState, 0, 1023, numLeds, 0); 

  // Voor elke LED in de array
  for (int i = 0; i < numLeds; i++) {
    // Als de huidige index kleiner is dan het aantal actieve LED's
    if (i < activeLeds) {
      digitalWrite(ledPins[i], HIGH); // Zet de LED aan
    } else {
      digitalWrite(ledPins[i], LOW); // Zet de LED uit
    }
  }
}

// Definitie van pinnen voor de button en de LEDs
const int buttonPin = 8;  // Pin toewijzing voor de drukknop
const int ledPin1 = 11;   // Pin toewijzing voor LED 1
const int ledPin2 = 5;    // Pin toewijzing voor LED 2

// Variabelen om de status van de drukknop en een teller bij te houden
int buttonStatus = 0;     // Status van de drukknop, standaard 0 (niet ingedrukt)
int counter = 0;          // Teller om het aantal drukknop indrukken bij te houden

void setup() {
  pinMode(buttonPin, INPUT);  // Stel de button pin in als input
  pinMode(ledPin1, OUTPUT);   // Stel de pin voor LED 1 in als output
  pinMode(ledPin2, OUTPUT);   // Stel de pin voor LED 2 in als output
}

void loop() {
  // Lees de status van de drukknop
  buttonStatus = digitalRead(buttonPin); 

  // Controleer of de drukknop is ingedrukt
  if (buttonStatus == HIGH) { // HIGH betekent dat de knop is ingedrukt
    counter++;  // Verhoog de teller
    delay(50);  // Korte pauze om debounce van de drukknop te voorkomen

    // Wacht totdat de drukknop wordt losgelaten
    while (digitalRead(buttonPin) == HIGH) {
      delay(10);  // Korte pauze om de lus te vertragen
    }
  }

  // Wissel de LEDs afhankelijk van de tellerstand
  if (counter % 2 == 0) {
    digitalWrite(ledPin1, LOW);  // Zet LED 1 uit
    digitalWrite(ledPin2, HIGH); // Zet LED 2 aan
  } else {
    digitalWrite(ledPin1, HIGH); // Zet LED 1 aan
    digitalWrite(ledPin2, LOW);  // Zet LED 2 uit
  }
}

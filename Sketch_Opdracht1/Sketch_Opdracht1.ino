// Auteur: AlexChulo
// Bron: https://brightspace.avans.nl/
// Dit programma laat twee LED's knipperen die zijn aangesloten op pin 13 en pin 10 afwisselend met een vertraging van 2 seconden.

// De setup functie wordt één keer uitgevoerd wanneer de microcontroller wordt opgestart of gereset.
void setup() {
  pinMode(13, OUTPUT);  // Stel pin 13 in als een output pin
  pinMode(10, OUTPUT);  // Stel pin 10 in als een output pin
}

// De loop functie wordt herhaaldelijk uitgevoerd nadat setup is voltooid.
void loop() {
  digitalWrite(13, HIGH);  // Zet de LED aangesloten op pin 13 aan
  delay(2000);             // Wacht 2 seconden
  digitalWrite(13, LOW);   // Zet de LED aangesloten op pin 13 uit
  delay(2000);             // Wacht 2 seconden
  
  digitalWrite(10, HIGH);  // Zet de LED aangesloten op pin 10 aan
  delay(2000);             // Wacht 2 seconden
  digitalWrite(10, LOW);   // Zet de LED aangesloten op pin 10 uit
  delay(2000);             // Wacht 2 seconden
}

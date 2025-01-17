// Auteur: AlexChulo
// Bronnen: 
// - https://brightspace.avans.nl/
// - Arduino Ultrasonic Motion Sensor: Motion Sensor and LED project - YouTube
// - ChatGPT

#include <Servo.h> // Servo bibliotheek voor aansturing van de servomotor

// Initialisatie van de servo en pinnen
Servo myServo;
const int trigPin = 12; // Pin voor trig van de ultrasone sensor
const int echoPin = 13; // Pin voor echo van de ultrasone sensor
const int servoPin = 6; // Pin voor servomotor

// Functieprototypen
long measureDistance();

/**
 * @brief Setup functie om de pinnen en servo te configureren
 */
void setup() {
  Serial.begin(9600); // Initialiseer seriële communicatie
  pinMode(trigPin, OUTPUT); // Zet trig pin als output
  pinMode(echoPin, INPUT); // Zet echo pin als input
  myServo.attach(servoPin); // Verbind de servo met pin 6
  myServo.write(0); // Zet servo op startpositie 0 graden
}

/**
 * @brief Loop functie die continu wordt uitgevoerd
 *        Meet de afstand en beweegt de servo
 */
void loop() {
  long distance = measureDistance();

  // Debugging informatie naar de serial monitor sturen
  Serial.print("Afstand: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Bereken servo positie op basis van de gemeten afstand
  if (distance <= 10) {
    int servoPos = map(distance, 4, 10, 180, 0);
    servoPos = constrain(servoPos, 0, 180);
    myServo.write(servoPos);
  } else {
    myServo.write(0); // Zet de servo terug naar 0 graden als de afstand > 10 cm is
  }

  delay(100); // Kleine vertraging om te voorkomen dat de sensor te vaak leest
}

/**
 * @brief Functie om de afstand te meten met de ultrasone sensor
 * @return De gemeten afstand in centimeters
 */
long measureDistance() {
  long duration;
  int distance;

  // Ultrasoon puls sturen
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Pulsduur lezen
  duration = pulseIn(echoPin, HIGH);

  // Berekening van afstand (in cm)
  distance = duration * 0.034 / 2;
  
  return distance;
}

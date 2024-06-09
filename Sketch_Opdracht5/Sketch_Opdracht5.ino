#include <Servo.h> // Servo bibliotheek voor aansturing van de servomotor

// Initialisatie van de servo en pinnen
Servo myServo;
const int button1Pin = 2; // Pin voor knop 1
const int button2Pin = 3; // Pin voor knop 2
const int servoPin = 9;   // Pin voor servomotor

/**
 * @brief Setup functie om de pinnen en servo te configureren
 */
void setup() {
  pinMode(button1Pin, INPUT); // Zet pin 2 als input voor drukknop 1
  pinMode(button2Pin, INPUT); // Zet pin 3 als input voor drukknop 2
  myServo.attach(servoPin);   // Verbind de servo met pin 9
  myServo.write(0);           // Zet servo op startpositie 0 graden
}

/**
 * @brief Loop functie die continu wordt uitgevoerd
 *        Controleert de status van de drukknoppen en roept servoMotion aan
 */
void loop() {
  bool button1State = digitalRead(button1Pin); // Lees de status van drukknop 1
  bool button2State = digitalRead(button2Pin); // Lees de status van drukknop 2

  if (button1State && button2State) {
    servoMotion(3000, 5000, 500); // Beide knoppen ingedrukt: 3s omhoog, 5s wachten, 0.5s omlaag
  } else if (button1State) {
    servoMotion(3000, 0, 3000);   // Alleen knop 1 ingedrukt: 3s omhoog en omlaag
  } else if (button2State) {
    servoMotion(500, 0, 500);     // Alleen knop 2 ingedrukt: 0.5s omhoog en omlaag
  }
}

/**
 * @brief Functie om de servomotor te bewegen
 * @param upTime Tijd in milliseconden om de servo van 0 naar 120 graden te draaien
 * @param waitTime Tijd in milliseconden om te wachten op positie 120 graden
 * @param downTime Tijd in milliseconden om de servo van 120 terug naar 0 graden te draaien
 */
void servoMotion(int upTime, int waitTime, int downTime) {
  myServo.write(0); // Zet servo op 0 graden
  delay(10); // Korte pauze om de servo opdracht te geven

  // Servo omhoog in upTime ms
  for (int pos = 0; pos <= 120; pos++) {
    myServo.write(pos);
    delay(upTime / 120);
  }

  delay(waitTime); // Wacht voor de opgegeven tijd

  // Servo terug naar 0 in downTime ms
  for (int pos = 120; pos >= 0; pos--) {
    myServo.write(pos);
    delay(downTime / 120);
  }
}

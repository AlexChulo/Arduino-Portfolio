// Auteur: AlexChulo
// Bronnen: 
// - https://brightspace.avans.nl/
// - Control a Positional Servo Motor with an Arduino (Lesson #10) (youtube.com)
// - ChatGPT

#include <Servo.h> // Servo bibliotheek voor aansturing van de servomotor

// Initialisatie van de servo en pinnen
Servo myServo;
const int button1Pin = 2; // Pin voor drukknop 1
const int button2Pin = 3; // Pin voor drukknop 2
const int servoPin = 9;   // Pin voor servomotor

unsigned long lastDebounceTime1 = 0;  // De laatste tijd dat de output pin veranderde voor drukknop 1
unsigned long lastDebounceTime2 = 0;  // De laatste tijd dat de output pin veranderde voor drukknop 2
const unsigned long debounceDelay = 50; // De debounce tijd; vergroot als de schakelaar minder gevoelig is

bool lastButton1State = LOW;
bool lastButton2State = LOW;
bool button1State = LOW;
bool button2State = LOW;
bool actionTaken = false; // Vlag om ervoor te zorgen dat actie slechts eenmaal per druk wordt uitgevoerd

// Functieprototypen
void servoMotion(int upTime, int waitTime, int downTime, int button1, int button2 = -1);
void debounceButtons();

/**
 * @brief Setup functie om de pinnen en servo te configureren
 */
void setup() {
  Serial.begin(9600); // Start seriële communicatie met 9600 baud
  pinMode(button1Pin, INPUT); // Zet pin 2 als input voor drukknop 1
  pinMode(button2Pin, INPUT); // Zet pin 3 als input voor drukknop 2
  myServo.attach(servoPin);   // Verbind de servo met pin 9
  myServo.write(0);           // Zet servo op startpositie 0 graden
  Serial.println("Setup voltooid, servo op startpositie.");
}

/**
 * @brief Loop functie die continu wordt uitgevoerd
 *        Controleert de status van de drukknoppen en roept servoMotion aan
 */
void loop() {
  debounceButtons();

  // Controleer de status van de knoppen en roep servoMotion aan
  if (button1State && button2State && !actionTaken) {
    Serial.println("Beide knoppen ingedrukt: 3s omhoog, 5s wachten, 0.5s omlaag.");
    servoMotion(3000, 5000, 500, button1Pin, button2Pin); // Beide knoppen ingedrukt: 3s omhoog, 5s wachten, 0.5s omlaag
    actionTaken = true; // Markeer de actie als uitgevoerd
  } else if (button1State && !button2State && !actionTaken) {
    Serial.println("Knop 1 ingedrukt: 3s omhoog en omlaag.");
    servoMotion(3000, 0, 3000, button1Pin);   // Alleen knop 1 ingedrukt: 3s omhoog en omlaag
    actionTaken = true; // Markeer de actie als uitgevoerd
  } else if (button2State && !button1State && !actionTaken) {
    Serial.println("Knop 2 ingedrukt: 0.5s omhoog en omlaag.");
    servoMotion(500, 0, 500, button2Pin);     // Alleen knop 2 ingedrukt: 0.5s omhoog en omlaag
    actionTaken = true; // Markeer de actie als uitgevoerd
  }

  // Reset de actionTaken vlag wanneer beide knoppen worden losgelaten
  if (!button1State && !button2State) {
    actionTaken = false;
  }
}

/**
 * @brief Functie om de drukknoppen te debouncen
 */
void debounceButtons() {
  // Lees de status van de drukknoppen
  bool reading1 = digitalRead(button1Pin);
  bool reading2 = digitalRead(button2Pin);

  // Debounce logica
  if ((reading1 != lastButton1State) || (reading2 != lastButton2State)) {
    lastDebounceTime1 = millis();
    lastDebounceTime2 = millis();
  }

  if ((millis() - lastDebounceTime1) > debounceDelay) {
    if (reading1 != button1State) {
      button1State = reading1;
      actionTaken = false; // Reset de actie vlag wanneer de knop status verandert
    }
  }
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    if (reading2 != button2State) {
      button2State = reading2;
      actionTaken = false; // Reset de actie vlag wanneer de knop status verandert
    }
  }

  // Update vorige knopstatussen
  lastButton1State = reading1;
  lastButton2State = reading2;
}

/**
 * @brief Functie om de servomotor te bewegen en controleren of knoppen zijn losgelaten
 * @param upTime Tijd in milliseconden om de servo van 0 naar 120 graden te draaien
 * @param waitTime Tijd in milliseconden om te wachten op positie 120 graden
 * @param downTime Tijd in milliseconden om de servo van 120 terug naar 0 graden te draaien
 * @param buttons Variabele aantal pinnen die de beweging kunnen onderbreken
 */
void servoMotion(int upTime, int waitTime, int downTime, int button1, int button2) {
  myServo.write(0); // Zet servo op 0 graden
  delay(10); // Korte pauze om de servo opdracht te geven

  // Servo omhoog in upTime ms
  Serial.print("Servo omhoog naar 120 graden in ");
  Serial.print(upTime);
  Serial.println(" ms.");
  for (int pos = 0; pos <= 120; pos++) {
    myServo.write(pos);
    delay(upTime / 120);
    // Controleer knopstatus tijdens beweging
    if (!digitalRead(button1) || (button2 != -1 && !digitalRead(button2))) {
      Serial.println("Beweging onderbroken.");
      return;
    }
  }

  Serial.print("Servo wacht voor ");
  Serial.print(waitTime);
  Serial.println(" ms.");
  for (unsigned long start = millis(); millis() - start < waitTime;) {
    // Controleer knopstatus tijdens wachten
    if (!digitalRead(button1) || (button2 != -1 && !digitalRead(button2))) {
      Serial.println("Beweging onderbroken.");
      return;
    }
  }

  // Servo terug naar 0 in downTime ms
  Serial.print("Servo terug naar 0 graden in ");
  Serial.print(downTime);
  Serial.println(" ms.");
  for (int pos = 120; pos >= 0; pos--) {
    myServo.write(pos);
    delay(downTime / 120);
    // Controleer knopstatus tijdens beweging
    if (!digitalRead(button1) || (button2 != -1 && !digitalRead(button2))) {
      Serial.println("Beweging onderbroken.");
      return;
    }
  }
  Serial.println("Servo beweging voltooid.");
}

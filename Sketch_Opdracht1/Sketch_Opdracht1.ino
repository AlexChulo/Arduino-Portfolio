void setup() {
  pinMode(13,OUTPUT);
  pinMode(10,OUTPUT);
  }


void loop() {
 digitalWrite(13,1);
 delay(2000);
 digitalWrite(13,0);
  delay(2000);
 digitalWrite(10,1);
  delay(2000);
 digitalWrite(10,0);
  delay(2000);
  }


#include <TimerOne.h>

#define PIN_PING 3
#define PIN_IN 2
#define VALID_LOW 10
#define VALID_HIGH 250

int pingActive;
unsigned long pingDuration;
int echoState;
unsigned long echoDuration;

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_PING, OUTPUT);
  digitalWrite(PIN_PING, LOW);
  pingActive = 0;
  
  attachInterrupt(0, echoSonar, CHANGE);
  
  Timer1.initialize(500000);
  Timer1.attachInterrupt(pingSonar);
  
  echoState = 0;
}

void loop() {
    if(micros() - pingDuration > 15 && pingActive) {
      pingActive = 0;
      digitalWrite(PIN_PING, LOW);
    }
}

void pingSonar() {
    digitalWrite(PIN_PING, HIGH);
    pingDuration = micros();
    pingActive = 1;
}

void echoSonar() {
    if(!echoState) {
      echoDuration = micros();
      echoState = !echoState;
    } else {
      echoDuration = micros() - echoDuration;
      Serial.println(microsecondsToCentimeters(echoDuration));
      echoState = !echoState;
    }
}

int microsecondsToCentimeters(long microseconds) {
  int cm = microseconds / 29 / 2;
  if(cm > VALID_HIGH || cm < VALID_LOW) {
    return -1;
  } else {
    return cm;
  }
}

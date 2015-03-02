const byte RED = 0;
const byte GREEN = 1;

byte buttonRed = 8;
byte buttonGreen = 9;
byte ledRed = 2;
byte ledGreen = 3;
byte computerTurn = 1;
byte lastPly;

void setup() {
  pinMode(buttonRed, INPUT);
  pinMode(buttonGreen, INPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);

  randomSeed(analogRead(0));
}

void loop() {
  if(computerTurn) {
    lastPly = random(2);
    allLedsOff();
    if(lastPly == RED) {
      digitalWrite(ledRed, HIGH);
    } else {
      digitalWrite(ledGreen, HIGH);
    }
    delay(300);
    allLedsOff();
    computerTurn = 0;
  } else {
    int stateRed = digitalRead(buttonRed);
    int stateGreen = digitalRead(buttonGreen);
    if(stateRed || stateGreen) {
      if(stateRed) {
        lightTheLed(ledRed);
      } else {
        lightTheLed(ledGreen);
      }
      if(stateRed && lastPly == RED) {
        // OK
        delay(2000);
      } else if(stateGreen && lastPly == GREEN) {
        // OK
        delay(2000);
      } else if((stateRed && lastPly == GREEN) || (stateGreen && lastPly == RED)) {
        blinkLeds();
        delay(2000);
      }
      computerTurn = 1;
    }
    delay(1);
  }
}

void allLedsOff() {
  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);
}

void lightTheLed(byte led) {
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
}

void blinkLeds() {
  for(int i = 0; i < 10; i++) {
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, HIGH);
    delay(100);
    allLedsOff();
    delay(100);
  }
}

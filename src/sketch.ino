const byte RED = 0;
const byte GREEN = 1;
const byte BLUE = 2;
const byte YELLOW = 3;

const byte buttonRed = 8;
const byte buttonGreen = 9;
const byte buttonBlue = 10;
const byte buttonYellow = 11;
const byte ledRed = 2;
const byte ledGreen = 3;
const byte ledBlue = 4;
const byte ledYellow = 5;

byte computerTurn = 1;
byte lastPly;

void setup() {
  pinMode(buttonRed, INPUT);
  pinMode(buttonGreen, INPUT);
  pinMode(buttonBlue, INPUT);
  pinMode(buttonYellow, INPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledYellow, OUTPUT);

  randomSeed(analogRead(0));
}

void loop() {
  if(computerTurn) {
    lastPly = random(4);
    allLedsOff();
    if(lastPly == RED) {
      digitalWrite(ledRed, HIGH);
    } else if(lastPly == GREEN) {
      digitalWrite(ledGreen, HIGH);
    } else if(lastPly == BLUE) {
      digitalWrite(ledBlue, HIGH);
    } else {
      digitalWrite(ledYellow, HIGH);
    }
    delay(300);
    allLedsOff();
    computerTurn = 0;
  } else {
    byte stateRed = digitalRead(buttonRed);
    byte stateGreen = digitalRead(buttonGreen);
    byte stateBlue = digitalRead(buttonBlue);
    byte stateYellow = digitalRead(buttonYellow);
    if(stateRed || stateGreen || stateBlue || stateYellow) {
      if(stateRed) {
        lightTheLed(ledRed);
      } else if(stateGreen) {
        lightTheLed(ledGreen);
      } else if(stateBlue) {
        lightTheLed(ledBlue);
      } else {
        lightTheLed(ledYellow);
      }
      if(isRightAnswer(stateRed, stateGreen, stateBlue, stateYellow)) {
        delay(1500);
      } else {
        blinkLeds();
        delay(2000);
      }
      computerTurn = 1;
    }
    delay(1);
  }
}

boolean isRightAnswer(byte red, byte green, byte blue, byte yellow) {
  if( (red && lastPly == RED) || (green && lastPly == GREEN) ||
      (blue && lastPly == BLUE) || (yellow && lastPly == YELLOW) ) {
    return true;
  } else {
    return false;
  }

}

void allLedsOff() {
  digitalWrite(ledRed, LOW);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledBlue, LOW);
  digitalWrite(ledYellow, LOW);
}

void lightTheLed(byte led) {
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
}

void blinkLeds() {
  for(byte i = 0; i < 10; i++) {
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledYellow, HIGH);
    delay(100);
    allLedsOff();
    delay(100);
  }
}


const byte RED = 0;
const byte GREEN = 1;
const byte BLUE = 2;
const byte YELLOW = 3;

// Red button is pin 8, green button is pin 9, blue button is pin 10,
// yellow button is pin 11.
const byte BUTTON_BASE = 8;

// Red led is pin 2, green led is pin 3, blue led is pin 4 and yellow
// led is pin 5.
const byte LED_BASE = 2;

const byte BUZZER = 13;

int notes[] = {262, 311, 349, 392};

boolean isComputerTurn = true;
byte lastPly;
byte plies[20];
byte plyIndex = 0;

byte answers[20];
byte answerIndex = 0;

boolean isButtonUp = true;

void setup() {
  for(byte i = 0; i < 4; i++) {
    pinMode(BUTTON_BASE + i, INPUT);
  }
  for(byte i = 0; i < 4; i++) {
    pinMode(LED_BASE + i, OUTPUT);
  }
  randomSeed(analogRead(0));
}

void loop() {
  isComputerTurn ? computerTurn() : playerTurn();
}

void computerTurn() {
  computeNewPly();
  playAllPlies();
  isComputerTurn = false;
}

void computeNewPly() {
  lastPly = random(4);
  plies[plyIndex] = lastPly;
  plyIndex++;
}

void playAllPlies() {
  for(byte i = 0; i < plyIndex; i++) {
    allLedsOff();
    lightTheLed(plies[i]);
    delay(400);
  }
  allLedsOff();
}

void playerTurn() {
  // Records the state of the buttons.
  byte states[4];
  for(byte i = 0; i < 4; i++) {
    states[i] = digitalRead(BUTTON_BASE + i);
  }

  if(!isButtonPressed(states) && !isButtonUp) {
    isButtonUp = true;
  } else if(isButtonPressed(states) && isButtonUp) {
    isButtonUp = false;
    lightTheLedAndRecordAnswer(states);
    isRightAnswer() ? rightAnswer() : gameOver();
  }
  delay(1);
}

boolean isButtonPressed(byte buttons[]) {
  return buttons[RED] || buttons[GREEN] || buttons[BLUE] || buttons[YELLOW];
}

void lightTheLedAndRecordAnswer(byte states[]) {
  for(byte i = RED; i <= YELLOW; i++) {
    if(states[i]) {
      lightTheLed(i);
      answers[answerIndex] = i;
      answerIndex++;
      break;
    }
  }
}

boolean isRightAnswer() {
  if(answers[answerIndex - 1] == plies[answerIndex - 1]) {
    return true;
  } else {
    return false;
  }
}

void allLedsOff() {
  allLeds(LOW);
}

void allLedsOn() {
  allLeds(HIGH);
}

void allLeds(int state) {
  for(byte i = 0; i < 4; i++) {
    digitalWrite(LED_BASE + i, state);
  }
}

void lightTheLed(byte led) {
  digitalWrite(LED_BASE + led, HIGH);
  tone(BUZZER, notes[led], 200);
  delay(200);
  digitalWrite(LED_BASE + led, LOW);
}

void blinkLeds() {
  for(byte i = 0; i < 10; i++) {
    allLedsOn();
    delay(100);
    allLedsOff();
    delay(100);
  }
}

void gameOver() {
  blinkLeds();
  plyIndex = 0;
  answerIndex = 0;
  isComputerTurn = true;
  delay(2000);
}

void rightAnswer() {
  if(answerIndex == plyIndex) {
    answerIndex = 0;
    isComputerTurn = true;
    delay(1000);
  } else {
    delay(1);
  }
}

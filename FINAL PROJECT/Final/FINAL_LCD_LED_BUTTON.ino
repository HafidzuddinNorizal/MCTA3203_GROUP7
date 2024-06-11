#include <Wire.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // input LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int speedPlus = 7; // to add speeds
const int Start = 6;     // to execute wash cycle 
const int Pause = 9;     // to pause/resume the wash cycle
const int tempPin = 8;   // pin for temperature setting

int speeds = 0;          // wash speed and time per minute
int secs = 59;           // seconds counter
int temp = 1;            // temperature setting
const int mins = 5;      // Fixed wash time

bool LastBtnState = HIGH; // to know the last condition 
bool pauseState = HIGH;   // to know the pause condition

void setup() {
  pinMode(speedPlus, INPUT_PULLUP); // speed add button
  pinMode(Start, INPUT_PULLUP);     // execute button 
  pinMode(Pause, INPUT_PULLUP);     // pause/resume button
  pinMode(tempPin, INPUT_PULLUP);   // detect temperature input 
  Serial1.begin(9600);
  lcd.begin(16, 2);                 // initialize LCD with 16 columns and 2 rows
  lcd.setCursor(0, 0);
  lcd.print("WASHING MACHINE");
  lcd.setCursor(5, 1);
  lcd.print("TIMER");
  delay(1000);
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("GROUP H");
  lcd.setCursor(0, 1);
  lcd.print("ASSALAMUALAIKUM");
  delay(1000);
  lcd.clear();
  
}

void loop() {
  // ----------- LCD for wash speed and temperature-------------
  lcd.setCursor(0, 0);
  lcd.print("SPEED ");
  lcd.print(speeds);
  lcd.setCursor(0, 1);
  lcd.print("TEMP: ");
  printTemp(temp);
  setspeeds();
  setTemp();
  

  //-------------- Starting or resetting wash cycle --------------------
  bool NewBtnState = digitalRead(Start);
  if (NewBtnState == LOW && LastBtnState == HIGH) {
    Serial1.write('1');
    delay(50);
    unsigned long pressTime = millis();
    while (digitalRead(Start) == LOW) {
      if (millis() - pressTime > 2000) { // long press detected
        setup(); // reset the system
        return;
      }
    }

    // short press detected
    LastBtnState = LOW;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("REM TIME ");
    lcd.print(mins - 1);
    delay(1000);
    speeds = mins - 1;

    while (speeds > 0 && LastBtnState == LOW) {
      bool NewBtnState1 = digitalRead(Start);
      bool NewPauseState = digitalRead(Pause);
      delay(100);

      // Pause/Resume logic
      if (NewPauseState == LOW) {
        pauseState = !pauseState;
        delay(200); // debounce delay
      }

      if (NewBtnState1 == LOW) {
        LastBtnState = HIGH;
        setup();
      }

      if (pauseState == HIGH) {
        delay(1000);
        secs--;
        if (secs < 0) {
          secs = 59;
          speeds--;
        }

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("REM TIME ");
        lcd.print(speeds);
        lcd.print(":");
        if (secs < 10) lcd.print("0");
        lcd.print(secs);
      }
    }
    LastBtnState = HIGH; // Reset button state
  }
}

//----------------------------- speed setting ----------------------------
void setspeeds() {
  if (digitalRead(speedPlus) == LOW) {
    delay(200); // debounce delay
    speeds++;
    if (speeds > 3) {
      speeds = 1;
    }
  }
}

//----------------------------- temperature setting ----------------------------
void setTemp() {
  if (digitalRead(tempPin) == LOW) {
    delay(500); // debounce delay
    temp++;
    if (temp > 3) {
      temp = 1;
    }
  }
}

//----------------------------- print temperature ----------------------------
void printTemp(int temp) {
  switch (temp) {
    case 1:
      lcd.print("Low    ");
      break;
    case 2:
      lcd.print("Medium ");
      break;
    case 3:
      lcd.print("High   ");
      break;
  }
}

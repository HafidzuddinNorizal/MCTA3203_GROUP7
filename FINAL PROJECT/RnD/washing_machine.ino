#include <Wire.h>
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int minPlus = 7; // to add wash time
int Start = 6;   // to execute wash cycle 
int mins;
int startState;   // to identify execute button state 
int LastBtnState; // to know the last condition 
int motOn = 30;   // motor on time 
int motOff = 10;  // motor reset time 
int secs;
int motTimer;     // time counter for motor control
int delaypd = 200; // time in milliseconds 
int spinDirpin = 8; // 1 for uni-dir,  2 for bi-dire
int spinDir;        // variable 

void setup() {
  // put your setup code here, to run once:
  pinMode(minPlus, INPUT);    // mins add
  pinMode(Start, INPUT);      // execute button 
  pinMode(10, OUTPUT);        // motor cw rotation
  digitalWrite(10, LOW);      // initial setting 
  pinMode(11, OUTPUT);        // motor ccw rotation 
  digitalWrite(11, LOW);      // initial setting 
  pinMode(spinDirpin, INPUT); // detect directional input 
  mins = 0;
  lcd.begin(16, 2);           // initialize LCD with 16 columns and 2 rows
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
  startState = HIGH;
  LastBtnState = HIGH;
  motTimer = 0;
  secs = 59;
  spinDir = 2;
  delay(1000);
  lcd.clear();
}

void loop() {
  // ----------- adding wash time--------------
  lcd.setCursor(0, 0);
  lcd.print("WASH TIME ");
  lcd.print(mins);
  lcd.print(" Min");
  lcd.setCursor(0, 1);
  lcd.print("Spin Dir ");
  lcd.print(spinDir);
  setMins();
  setDir();

  //----------------  starting wash cycle--------------------
  byte NewBtnState = digitalRead(Start);
  if (NewBtnState == LOW && LastBtnState == HIGH) {
    LastBtnState = LOW;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("REM TIME ");
    lcd.print(mins);
    delay(1000);
    mins = mins - 1;

    //------------------------------------- timer section----------------------
    while (mins != 0 && LastBtnState == LOW) {
      byte NewBtnState1 = digitalRead(Start);
      delay(100);
      if (NewBtnState1 == LOW && LastBtnState == LOW) {
        LastBtnState = HIGH;
        setup();
      }
      delay(delaypd);
      spinDir = spinDir;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("REM TIME ");
      lcd.print(mins);
      lcd.print(":");
      lcd.print(secs);
      motTimer = motTimer + 1;
      if (spinDir == 1 && (motTimer == motOn + motOff)) {
        motTimer = 0;
      }

      if (spinDir == 2 && (motTimer == 2 * (motOn + motOff))) {
        motTimer = 0;
      }

      secs = secs - 1;
      if (secs == 0) {
        secs = 59;
        mins = mins - 1;
        if (mins == 0) {
          mins = 0;

          setup();
          LastBtnState = HIGH;
        }
      }
      //---------------- mot start---------------------
      if (spinDir == 1) {
        if (motTimer == 1) {
          digitalWrite(10, HIGH);
          digitalWrite(11, LOW);
        } else if (LastBtnState == HIGH) {
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
        }
        if (motTimer == motOn + 1) {
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
        } else if (LastBtnState == HIGH) {
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
        }
      }

      //-------------------------- bidirectional -----------------------
      if (spinDir == 2) {
        if (motTimer == 1) {
          digitalWrite(10, HIGH);
          digitalWrite(11, LOW);
        }
        if (motTimer == motOn + 1) {
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
        }
        if (motTimer == (motOn + motOff + 1)) {
          digitalWrite(11, HIGH);
          digitalWrite(10, LOW);
        }
        if (motTimer == (motOn + motOff + motOn + 1)) {
          digitalWrite(11, LOW);
          digitalWrite(10, LOW);
        } else if (LastBtnState == HIGH) {
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
        }
      }
    }
  } else if (LastBtnState == LOW && NewBtnState == HIGH) {
    LastBtnState = LastBtnState;
  }
}

//----------------------------- minutes setting----------------------------
void setMins() {
  byte minTimer = digitalRead(minPlus);
  if (minTimer == LOW) {
    delay(200);
    mins = mins + 1;
    if (mins == 30) {
      mins = 0;
    }
  }
}

//----------------------------------direction -------------------
void setDir() {
  byte dir = digitalRead(spinDirpin);
  if (dir == LOW) {
    delay(500);
    spinDir = spinDir + 1;
    lcd.setCursor(0, 1);
    lcd.print("Spin Dir ");
    lcd.print(spinDir);
    if (spinDir == 3) {
      spinDir = 1;
    }
  }
}

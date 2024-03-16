//MCTA 3203 Assignment 1
//GROUP 7
const int segmentA = 2;
const int segmentB = 3;
const int segmentC = 4;
const int segmentD = 5;
const int segmentE = 6;
const int segmentF = 7;
const int segmentG = 8; 
const int switchbuttondown = 9;
const int switchbuttonup = 10;
const int DP = 11;

int count = 0;
int buttonUpState = 0;
int iniButtonUpState = 0;
int buttonDownState = 0;
int iniButtonDownState = 0; 
  
void setup() { 
  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);
  pinMode(DP, OUTPUT); 
  digitalWrite(DP ,HIGH);
} 
  
void loop() {
  buttonUpState = digitalRead(switchbuttonup); 
  buttonDownState = digitalRead(switchbuttondown);
  if (buttonUpState != iniButtonUpState) {
    if (buttonUpState == HIGH) {
      count++;
      Serial.println(count);       
      changeNumber(count); 
      if(count == 9) {
        count = 9;
      }        
      delay(200); 
    }
    delay(10); 
  }
  if (buttonDownState != iniButtonDownState) {
    if (buttonDownState == HIGH) {
      count--;
      Serial.println(count);
      changeNumber(count);
      if(count == 0) {
        count = 0; 
      }
      delay(200); 
    } else { 
      Serial.println("OFF");
    } 
    delay(10);
  } 
  changeNumber(count);
} 
 
void changeNumber(int buttonPress) {
  switch (buttonPress) {
    case 0: 
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, HIGH);
    digitalWrite(segmentE, HIGH);
    digitalWrite(segmentF, HIGH);
    digitalWrite(segmentG, LOW);
    break;
    case 1: 
    digitalWrite(segmentA, LOW);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, LOW);
    digitalWrite(segmentE, LOW);
    digitalWrite(segmentF, LOW);
    digitalWrite(segmentG, LOW);
    break; 
    case 2:
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, LOW);
    digitalWrite(segmentD, HIGH);
    digitalWrite(segmentE, HIGH);
    digitalWrite(segmentF, LOW);
    digitalWrite(segmentG, HIGH);
    break; 
    case 3:
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, HIGH);
    digitalWrite(segmentE, LOW);
    digitalWrite(segmentF, LOW);
    digitalWrite(segmentG, HIGH);
    break; 
    case 4:
    digitalWrite(segmentA, LOW);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, LOW);
    digitalWrite(segmentE, LOW);
    digitalWrite(segmentF, HIGH);
    digitalWrite(segmentG, HIGH);
    break; 
    case 5: 
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, LOW);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, HIGH);
    digitalWrite(segmentE, LOW);
    digitalWrite(segmentF, HIGH);
    digitalWrite(segmentG, HIGH);
    break; 
    case 6: 
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, LOW);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, HIGH);
    digitalWrite(segmentE, HIGH);
    digitalWrite(segmentF, HIGH);
    digitalWrite(segmentG, HIGH);
    break; 
    case 7:
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, LOW);
    digitalWrite(segmentE, LOW);
    digitalWrite(segmentF, LOW);
    digitalWrite(segmentG, LOW);
    break; 
    case 8: 
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, HIGH);
    digitalWrite(segmentE, HIGH);
    digitalWrite(segmentF, HIGH);
    digitalWrite(segmentG, HIGH);
    break; 
    case 9: 
    digitalWrite(segmentA, HIGH);
    digitalWrite(segmentB, HIGH);
    digitalWrite(segmentC, HIGH);
    digitalWrite(segmentD, HIGH);
    digitalWrite(segmentE, LOW);
    digitalWrite(segmentF, HIGH);
    digitalWrite(segmentG, HIGH);
    break;
  } 
} 
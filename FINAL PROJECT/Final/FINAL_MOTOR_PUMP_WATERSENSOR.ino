//change it when finalizing
int motor1 = 2;
int motor1rev = 3;

//water sensor
int resval = 0; // holds the value
int respin = A5; // sensor pin used

int speed1 = 200; // Speed for motor 1
int time = 0;
char *inByte = '0';
const int pumpin = 11;
const int pumpout = 12; 
void setup() {
  pinMode(motor1, OUTPUT);
  pinMode(pumpin, OUTPUT);
  pinMode(pumpout, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  Serial1.begin(9600);
  Serial.begin(19200);
}

void loop() {

  MotorOFF();
  PumpOff();
 if(Serial1.available())
  {
    inByte = Serial1.read();
    if(inByte=='1'){
        digitalWrite(10, HIGH);
      Serial.println("JadiOi");
      delay(1000);
      PumpIn();
      MotorSpin();
      PumpOut();
      PumpIn();
      MotorSpin();
      PumpOut();
      MotorRinse();
      inByte = '0';
    }
  }
}

void PumpOut(){
  digitalWrite(pumpout, HIGH);
  delay(10000);// add water sensor function
  digitalWrite(pumpout, LOW);
}

void PumpIn(){
  digitalWrite(pumpin, HIGH); // turn on pump 5 seconds
  if (resval > 330) {
  Serial.println("Water Level: High");
 delay(3000);
  digitalWrite(pumpin, LOW);
  }
}
void PumpOff(){
  digitalWrite(pumpin, LOW); // turn on pump 5 seconds
  digitalWrite(pumpout, LOW);
}


void MotorRinse(){
  Motor1CCW();
  delay(100000);
  if(Serial.available()){
  inByte = Serial.read();
  }
}

void MotorSpin(){

  for(int i=0; i<=60 && inByte == '1'; i++){
    if(Serial.available())
    inByte = Serial.read();
    Motor1CW();
    delay(1000);
  } 
  

}

//motor movement
void Motor1CW(){
//Progression: Masuk air, Spin w detergent, Keluar air, Masuk air, Spin kosong, keluar air, spin/ rinse, siap
  digitalWrite(motor1, HIGH);
  digitalWrite(motor1rev, LOW);
  analogWrite(9, 100);
}
void Motor1CCW(){
  digitalWrite(motor1, LOW);
  digitalWrite(motor1rev, HIGH);
  analogWrite(9, 100);
}
void MotorOFF(){
  digitalWrite(motor1, LOW);
  digitalWrite(motor1rev, LOW);
}


int motor1 = 2;
int motor2 = 3;
const int button = 4;

void setup() {
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(button, INPUT_PULLUP);

}

void loop() {
  digitalWrite(button, 1);
 // if (digitalRead(button)==1){
    digitalWrite(motor1, HIGH);
    digitalWrite(motor2, LOW);


 . 
  Serial.println(digitalRead(button));
  delay(500);

}

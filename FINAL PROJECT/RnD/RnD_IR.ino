#include <IRremote.h>

// Define the IR receiver pin
const int IR_PIN = 6;

// Define the IR receiver object
IRrecv irrecv(IR_PIN);
const int ledgreen = 2;
const int ledyellow = 3;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(ledgreen, OUTPUT);
  pinMode(ledyellow, OUTPUT);
}

void loop() {
  // Check if the IR receiver has received a signal
  if (irrecv.decode()) {
    
    // Print the HEX value of the button press
    Serial.println(irrecv.decodedIRData.decodedRawData, HEX);
    if (irrecv.decodedIRData.decodedRawData==0XFD024FB0){
      digitalWrite(ledgreen,HIGH);
      delay(500);
      digitalWrite(ledgreen, LOW);
      Serial.println("Green turn on");
    }
    if (irrecv.decodedIRData.decodedRawData==0XF6094FB0){
      digitalWrite(ledyellow, HIGH);
      delay(500);
      digitalWrite(ledyellow, LOW);
      Serial.println("Yellow turn on");
    }
    // Reset the IR receiver for the next signal
    irrecv.resume();
  }
}
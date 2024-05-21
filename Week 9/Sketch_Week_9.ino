#include <SPI.h>
#include <Pixy.h>

Pixy pixy;

const int blueLedPin = 2;    // Pin for red LED
const int redLedPin = 3;  // Pin for green LED
const int greenLedPin = 4;   // Pin for blue LED

void setup() {
  Serial.begin(9600);
  pixy.init();

  pinMode(blueLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
}

void loop() {
  static int i = 0;
  int blocks = pixy.getBlocks();  // Use getBlocks method from ccc (Color Connected Components) object

  if (blocks) {
    // Turn off all LEDs initially
    digitalWrite(blueLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(greenLedPin, LOW);

    for (i = 0; i < blocks; i++) {
      Serial.print("Block ");
      Serial.print(i);
      Serial.print(": ");
      Serial.print("Signature: ");
      Serial.print(pixy.blocks[i].signature);  // Access signature using m_signature
      Serial.print(" X: ");
      Serial.print(pixy.blocks[i].x);  // Access x using m_x
      Serial.print(" Y: ");
      Serial.println(pixy.blocks[i].y);  // Access y using m_y
delay(100);
      // Add logic to identify and react based on the color signature
      if (pixy.blocks[i].signature == 1) {
        // Object with signature 1 detected (Color 1: Red)
        Serial.println("Color 1 (Blue) detected");
        digitalWrite(blueLedPin, HIGH);  // Turn on red LED
        // Add more actions for color 1 if needed
      } else if (pixy.blocks[i].signature == 2) {
        // Object with signature 2 detected (Color 2: Green)
        Serial.println("Color 2 (Red) detected");
        digitalWrite(redLedPin, HIGH);  // Turn on green LED
        // Add more actions for color 2 if needed
      } else if (pixy.blocks[i].signature == 3) {
        // Object with signature 3 detected (Color 3: Blue)
        Serial.println("Color 3 (Green) detected");
        digitalWrite(greenLedPin, HIGH);  // Turn on blue LED
        // Add more actions for color 3 if needed
        
      }
    }
  }
}

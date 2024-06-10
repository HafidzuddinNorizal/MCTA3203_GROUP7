#include <LiquidCrystal.h>

int resval = 0; // holds the value
int respin = A5; // sensor pin used
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
lcd.begin(16, 2);
  // Print a message to the LCD.
// start the serial console
Serial.begin(9600);
}

void loop() {

resval = analogRead(respin); //Read data from analog pin and store it to resval variable
// set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
if (resval <= 100) {
Serial.println("Water Level: Empty");
lcd.setCursor(0, 0);
lcd.print("Empty");
}
else if (resval > 100 && resval <= 300) {
Serial.println("Water Level: Low");
lcd.setCursor(0, 0);
lcd.print("Low");
}
else if (resval > 300 && resval <= 330) {
Serial.println("Water Level: Medium");
lcd.setCursor(0, 0);
lcd.print("Medium");
}
else if (resval > 330) {
Serial.println("Water Level: High");
lcd.setCursor(0, 0);
lcd.print("High");
}
delay(1000);
}
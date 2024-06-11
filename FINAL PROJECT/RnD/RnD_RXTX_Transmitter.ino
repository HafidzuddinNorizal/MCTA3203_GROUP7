// C++ code
//
char inByte = '0';
void setup()
{
  pinMode(2, INPUT_PULLUP);
    pinMode(3, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop()
{
  if(digitalRead(3)==0)
  {
    Serial.write('1');
    delay(10);    
  }
  else if(digitalRead(2)==0)
  {
    Serial.write('0');
    delay(10);    
  }
}
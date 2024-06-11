// C++ code
//
char *inByte = '0';
void setup()
{
  pinMode(5, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  if(Serial.available())
  {
    inByte = Serial.read();
    Serial.print(inByte);
    if(inByte == '1')
    {
      digitalWrite(5, 1);
    }
    else if(inByte == '0')
    {
      digitalWrite(5, 0);
    }
  }
}
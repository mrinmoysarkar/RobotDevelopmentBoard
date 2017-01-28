#include<Servo.h>
Servo a,b;
void setup()
{
  a.attach(7);
  b.attach(8);
  //a.write(20);
  Serial.begin(9600);
 // delay(10000);
}
void loop()
{
  //Serial.println(a.read());
  //delay(500);
  //Serial.println("bbb");
  //Serial.println(b.read());
  //delay(5000);
  
  for(int i=0;i<110;i++)
  {
   // a.write(135+i);//35//90
   // b.write(80-i);
    a.write(20+i);//130//20
    b.write(130-i);
    delay(20);
  }
  delay(1000);
  for(int i=0;i<110;i++)
  {
    //a.write(180-i);
    //b.write(35+i);
    b.write(20+i);
    a.write(130-i);
    delay(20);
  }
  delay(10000);
}

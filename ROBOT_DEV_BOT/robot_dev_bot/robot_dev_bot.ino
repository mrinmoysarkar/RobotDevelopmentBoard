#include <LiquidCrystal.h>
#include <Servo.h>

int m1=13,m2=12,m3=11,m4=10;
int hom=22,up=23,down=24,ok=25,back=26;
int enable=27,rw=28,rs=29,d7=30,d6=31,d5=32,d4=33,d3=34,d2=35,d1=36,d0=37;
int buzzer=9;
int L1=38,L2=39,L3=40,L4=41,L5=42;

int left1=0,left2=1,left3=2,middle=3,right3=7,right2=6,right1=5;
int exl_xx=12,exl_yy=13,exl_zz=14;
int power_check=15;

int sd_card_cs = 53;
int sonor_trig = 44;
int sonor_echo = 2;
int eeprom_scl = 21;
int eeprom_sda = 20;
int servo_1 = 8,servo_2=7,servo_3=6,servo_4=5,servo_5=4,servo_6=3;
int motor_base_speed=0;

int value=0;
int SERVO_INITIAL_VALUE[6] = {
  0,0,0,0,0,0};
int SERVO_FINAL_VALUE[6] = {
  0,0,0,0,0,0};

LiquidCrystal lcd(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7);

//Servo Left_grab;
//Servo Right_grab;
//Servo Left_pick;
//Servo Right_pick;
//Servo Sonor_move;
//Servo box_remover;
Servo SERVO_1;
Servo SERVO_2;
Servo SERVO_3;
Servo SERVO_4;
Servo SERVO_5;
Servo SERVO_6;

void setup()
{
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  pinMode(m3,OUTPUT);
  pinMode(m4,OUTPUT);

  pinMode(hom,INPUT);
  pinMode(up,INPUT);
  pinMode(down,INPUT);
  pinMode(ok,INPUT);
  pinMode(back,INPUT);

  pinMode(buzzer,OUTPUT);

  //  Left_grab.attach(8);
  //  Right_grab.attach(7);
  //  Left_pick.attach(6);
  //  Right_pick.attach(5);
  //  Sonor_move.attach(4);
  //  box_remover.attach(3); 
  SERVO_1.attach(servo_1);
  SERVO_2.attach(servo_2);
  SERVO_3.attach(servo_3);
  SERVO_4.attach(servo_4);
  SERVO_5.attach(servo_5);
  SERVO_6.attach(servo_6);

  pinMode(L1,OUTPUT);
  pinMode(L2,OUTPUT);
  pinMode(L3,OUTPUT);
  pinMode(L4,OUTPUT);
  pinMode(L5,OUTPUT); 

  lcd.begin(20,4);

  Serial.begin(9600);
}
void loop()
{
  button_check();
  //set_motor_speed();
  //check_IR();
  //check_buzzer();
  // begin_bot();
  start_bot();
  lcd.print("mrinmoy is a good boy he works hard");
  while(1);

}
void start_bot()
{
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("ARDU BOT");
  lcd.setCursor(3,1);
  lcd.print("DESIGNED BY:");
  lcd.setCursor(0,2);
  lcd.print("***MRINMOY SARKAR***");
  lcd.setCursor(0,3);
  lcd.print("PRESS HOME FOR MANUE");
  while(1)
  {
    delay(100);
    if( digitalRead(hom))
    {
      digitalWrite(L1,HIGH);
      digitalWrite(L2,LOW);
      digitalWrite(L3,LOW);
      digitalWrite(L4,LOW);
      digitalWrite(L5,LOW);
      begin_bot();
      break;
    }
  }
}

void begin_bot()
{
label:
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("1.DO MAIN JOB");
  lcd.setCursor(0,1);
  lcd.print("2.SET MOTOR SPEED");
  lcd.setCursor(0,2);
  lcd.print("3.CHECK IR SENSOR");
  lcd.setCursor(0,3);
  lcd.print("4.CALIBRATE IRSENSOR");
  lcd.setCursor(0,0);
  lcd.blink();
  int option = 0;
  int display_check = 0;
  while(1)
  {
    delay(200);
    if(digitalRead(up))
    {
      digitalWrite(L1,LOW);
      digitalWrite(L2,HIGH);
      digitalWrite(L3,LOW);
      digitalWrite(L4,LOW);
      digitalWrite(L5,LOW); 
      option = option-1;
      if(option<0)
      {
        option =0;
      }
    }
    else if( digitalRead(down))
    {
      digitalWrite(L1,LOW);
      digitalWrite(L2,LOW);
      digitalWrite(L3,HIGH);
      digitalWrite(L4,LOW);
      digitalWrite(L5,LOW);
      option = option+1;
      if(option > 7)
      {
        option = 7;
      }
    }
    else if( digitalRead(ok))
    {
      digitalWrite(L1,LOW);
      digitalWrite(L2,LOW);
      digitalWrite(L3,LOW);
      digitalWrite(L4,LOW);
      digitalWrite(L5,HIGH);
      switch(option)
      {
      case 0:
        Do_the_job();
        goto label;
        break;
      case 1:
        set_motor_speed();
        goto label;
        break;
      case 2:
        check_IR();
        goto label;
        break;
      case 3:
        calibrate_ir_sensor();
        goto label;
        break;
      case 4:
        Initialize_valiable();
        goto label;
        break;
      case 5:
        check_servo();
        goto label;
        break;
      case 6:
        check_buzzer();
        goto label;
        break;
      case 7:
        SD_CONTROL();
        goto label;
        break;
      }
    }
    if(display_check == 0 && option == 3)
    {
      display_check = 1; 
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("1.DO MAIN JOB");
      lcd.setCursor(0,1);
      lcd.print("2.SET MOTOR SPEED");
      lcd.setCursor(0,2);
      lcd.print("3.CHECK IR SENSOR");
      lcd.setCursor(0,3);
      lcd.print("4.CALIBRATE IRSENSOR");
      lcd.setCursor(0,0);
      lcd.blink();
    }
    if(display_check == 1 && option == 4)
    {
      display_check = 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("5.INITIALIZE VARIABL");
      lcd.setCursor(0,1);
      lcd.print("6.SERVO CHECK");
      lcd.setCursor(0,2);
      lcd.print("7.BUZZER CHECK");
      lcd.setCursor(0,3);
      lcd.print("8.SD CARD CONTROL");
      lcd.setCursor(0,0);
      lcd.blink();
    }
    if(option < 4 && option >= 0)
    {
      lcd.setCursor(0,option);
    }
    else if(option < 8)
    {
      lcd.setCursor(0,option-4);
    }
  }
}
void calibrate_ir_sensor()
{
  lcd.clear();
  lcd.noBlink();
  lcd.print("NOT IMPLEMENTED YET");
  lcd.setCursor(0,1);
  lcd.print("PRESS HOME TO RETURN");
  while(1)
  {
    delay(100);
    //write code here
    if( digitalRead(hom))
    {
      digitalWrite(L1,HIGH);
      digitalWrite(L2,LOW);
      digitalWrite(L3,LOW);
      digitalWrite(L4,LOW);
      digitalWrite(L5,LOW);
      break;
    }
  }
}









void check_servo()
{
label:
  lcd.clear();
  lcd.noBlink();
  lcd.print("1.CALIBRATE SERVO");
  lcd.setCursor(0,1);
  lcd.print("2.SET INITIAL AND");
  lcd.setCursor(6,2);
  lcd.print("  FINAL DEGREE");
  lcd.setCursor(0,3);
  lcd.print("PRESS HOME TO RETURN");
  lcd.setCursor(0,0);
  lcd.blink();
  int option = 0;
  while(1)
  {
    delay(100);
    //write code here
    lcd.setCursor(0,option);
    if( digitalRead(up))
    {
      digitalWrite(L1,LOW);
      digitalWrite(L2,HIGH);
      digitalWrite(L3,LOW);
      digitalWrite(L4,LOW);
      digitalWrite(L5,LOW);
      option=0;
    }
    else if( digitalRead(down))
    {
      digitalWrite(L1,LOW);
      digitalWrite(L2,LOW);
      digitalWrite(L3,HIGH);
      digitalWrite(L4,LOW);
      digitalWrite(L5,LOW);
      option=1;
    }
    else if( digitalRead(ok))
    {
      digitalWrite(L1,LOW);
      digitalWrite(L2,LOW);
      digitalWrite(L3,LOW);
      digitalWrite(L4,LOW);
      digitalWrite(L5,HIGH);
      switch(option)
      {
      case 0:
lavel1:
        lcd.clear();
        lcd.noBlink();
        lcd.setCursor(0,0);
        lcd.print("1.SERVO-1 4.SERVO-4");
        lcd.setCursor(0,1);
        lcd.print("2.SERVO-2 5.SERVO-5");
        lcd.setCursor(0,2);
        lcd.print("3.SERVO-3 6.SERVO-6");
        lcd.setCursor(0,3);
        lcd.print("PRESS BACK TO RETURN");
        lcd.setCursor(0,0);
        lcd.blink();
        option = 0;
        while(1)
        {
          delay(100);
          switch(option)
          {
          case 0:
            lcd.setCursor(0,0);
            break;
          case 1:
            lcd.setCursor(0,1);
            break;
          case 2:
            lcd.setCursor(0,2);
            break;
          case 3:
            lcd.setCursor(10,0);
            break;
          case 4:
            lcd.setCursor(10,1);
            break;
          case 5:
            lcd.setCursor(10,2);
            break;
          }
          if( digitalRead(up))
          {
            digitalWrite(L1,LOW);
            digitalWrite(L2,HIGH);
            digitalWrite(L3,LOW);
            digitalWrite(L4,LOW);
            digitalWrite(L5,LOW);
            option-=1;
            option = option<0?0:option;
          }
          else if( digitalRead(down))
          {
            digitalWrite(L1,LOW);
            digitalWrite(L2,LOW);
            digitalWrite(L3,HIGH);
            digitalWrite(L4,LOW);
            digitalWrite(L5,LOW);
            option+=1;
            option = option>5?5:option;
          }
          else if( digitalRead(back))
          {
            digitalWrite(L1,LOW);
            digitalWrite(L2,LOW);
            digitalWrite(L3,LOW);
            digitalWrite(L4,HIGH);
            digitalWrite(L5,LOW);
            goto label;
          }
          else if( digitalRead(ok))
          {
            digitalWrite(L1,LOW);
            digitalWrite(L2,LOW);
            digitalWrite(L3,LOW);
            digitalWrite(L4,LOW);
            digitalWrite(L5,HIGH);
            int angle = 0;
            switch(option)
            {
            case 0:
              angle = SERVO_1.read();
              lcd.clear();
              lcd.noBlink();
              lcd.setCursor(0,0);
              lcd.print("SERVO-1 CURRENT");
              lcd.setCursor(0,1);
              lcd.print("POSITION IS    DEG");
              lcd.setCursor(12,1);
              lcd.print(angle);
              lcd.setCursor(0,2);
              lcd.print("PRESS UP TO INCREASE");
              lcd.setCursor(0,3);
              lcd.print("PRESS DOWN TO DECRE");
              while(1)
              {
                delay(100);
                SERVO_1.write(angle);
                lcd.setCursor(12,1);
                lcd.print(angle);
                if( digitalRead(up))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,HIGH);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  angle+=1;
                  angle = angle>180?180:angle;
                }
                else if( digitalRead(down))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,HIGH);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  angle-=1;
                  angle = angle<0?0:angle;
                }
                else if( digitalRead(back))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,HIGH);
                  digitalWrite(L5,LOW);
                  goto lavel1;
                }
                if( digitalRead(hom))
                {
                  digitalWrite(L1,HIGH);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  return;
                }
              }
              break;
            case 1:
              angle = SERVO_2.read();
              lcd.clear();
              lcd.noBlink();
              lcd.setCursor(0,0);
              lcd.print("SERVO-2 CURRENT");
              lcd.setCursor(0,1);
              lcd.print("POSITION IS    DEG");
              lcd.setCursor(12,1);
              lcd.print(angle);
              lcd.setCursor(0,2);
              lcd.print("PRESS UP TO INCREASE");
              lcd.setCursor(0,3);
              lcd.print("PRESS DOWN TO DECRE");
              while(1)
              {
                delay(100);
                SERVO_2.write(angle);
                lcd.setCursor(12,1);
                lcd.print(angle);
                if( digitalRead(up))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,HIGH);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  angle+=1;
                  angle = angle>180?180:angle;
                }
                else if( digitalRead(down))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,HIGH);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  angle-=1;
                  angle = angle<0?0:angle;
                }
                else if( digitalRead(back))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,HIGH);
                  digitalWrite(L5,LOW);
                  goto lavel1;
                }
                if( digitalRead(hom))
                {
                  digitalWrite(L1,HIGH);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  return;
                }
              }
              break;
            case 2:
              angle = SERVO_3.read();
              lcd.clear();
              lcd.noBlink();
              lcd.setCursor(0,0);
              lcd.print("SERVO-3 CURRENT");
              lcd.setCursor(0,1);
              lcd.print("POSITION IS    DEG");
              lcd.setCursor(12,1);
              lcd.print(angle);
              lcd.setCursor(0,2);
              lcd.print("PRESS UP TO INCREASE");
              lcd.setCursor(0,3);
              lcd.print("PRESS DOWN TO DECRE");
              while(1)
              {
                delay(100);
                SERVO_3.write(angle);
                lcd.setCursor(12,1);
                lcd.print(angle);
                if( digitalRead(up))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,HIGH);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  angle+=1;
                  angle = angle>180?180:angle;
                }
                else if( digitalRead(down))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,HIGH);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  angle-=1;
                  angle = angle<0?0:angle;
                }
                else if( digitalRead(back))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,HIGH);
                  digitalWrite(L5,LOW);
                  goto lavel1;
                }
                if( digitalRead(hom))
                {
                  digitalWrite(L1,HIGH);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  return;
                }
              }
              break;
            case 3:
              angle = SERVO_4.read();
              lcd.clear();
              lcd.noBlink();
              lcd.setCursor(0,0);
              lcd.print("SERVO-4 CURRENT");
              lcd.setCursor(0,1);
              lcd.print("POSITION IS    DEG");
              lcd.setCursor(12,1);
              lcd.print(angle);
              lcd.setCursor(0,2);
              lcd.print("PRESS UP TO INCREASE");
              lcd.setCursor(0,3);
              lcd.print("PRESS DOWN TO DECRE");
              while(1)
              {
                delay(100);
                SERVO_4.write(angle);
                lcd.setCursor(12,1);
                lcd.print(angle);
                if( digitalRead(up))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,HIGH);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  angle+=1;
                  angle = angle>180?180:angle;
                }
                else if( digitalRead(down))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,HIGH);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  angle-=1;
                  angle = angle<0?0:angle;
                }
                else if( digitalRead(back))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,HIGH);
                  digitalWrite(L5,LOW);
                  goto lavel1;
                }
                if( digitalRead(hom))
                {
                  digitalWrite(L1,HIGH);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  return;
                }
              }
              break;
            case 4:
              angle = SERVO_5.read();
              lcd.clear();
              lcd.noBlink();
              lcd.setCursor(0,0);
              lcd.print("SERVO-5 CURRENT");
              lcd.setCursor(0,1);
              lcd.print("POSITION IS    DEG");
              lcd.setCursor(12,1);
              lcd.print(angle);
              lcd.setCursor(0,2);
              lcd.print("PRESS UP TO INCREASE");
              lcd.setCursor(0,3);
              lcd.print("PRESS DOWN TO DECRE");
              while(1)
              {
                delay(100);
                SERVO_5.write(angle);
                lcd.setCursor(12,1);
                lcd.print(angle);
                if( digitalRead(up))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,HIGH);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  angle+=1;
                  angle = angle>180?180:angle;
                }
                else if( digitalRead(down))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,HIGH);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  angle-=1;
                  angle = angle<0?0:angle;
                }
                else if( digitalRead(back))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,HIGH);
                  digitalWrite(L5,LOW);
                  goto lavel1;
                }
                if( digitalRead(hom))
                {
                  digitalWrite(L1,HIGH);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  return;
                }
              }
              break;
            case 5:
              angle = SERVO_6.read();
              lcd.clear();
              lcd.noBlink();
              lcd.setCursor(0,0);
              lcd.print("SERVO-6 CURRENT");
              lcd.setCursor(0,1);
              lcd.print("POSITION IS    DEG");
              lcd.setCursor(12,1);
              lcd.print(angle);
              lcd.setCursor(0,2);
              lcd.print("PRESS UP TO INCREASE");
              lcd.setCursor(0,3);
              lcd.print("PRESS DOWN TO DECRE");
              while(1)
              {
                delay(100);
                SERVO_6.write(angle);
                lcd.setCursor(12,1);
                lcd.print(angle);
                if( digitalRead(up))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,HIGH);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  angle+=1;
                  angle = angle>180?180:angle;
                }
                else if( digitalRead(down))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,HIGH);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  angle-=1;
                  angle = angle<0?0:angle;
                }
                else if( digitalRead(back))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,HIGH);
                  digitalWrite(L5,LOW);
                  goto lavel1;
                }
                if( digitalRead(hom))
                {
                  digitalWrite(L1,HIGH);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  return;
                }
              }
              break;
            }
          }
          if( digitalRead(hom))
          {
            digitalWrite(L1,HIGH);
            digitalWrite(L2,LOW);
            digitalWrite(L3,LOW);
            digitalWrite(L4,LOW);
            digitalWrite(L5,LOW);
            return;
          }
        }
        break;
      case 1:
lavel2:
        lcd.clear();
        lcd.noBlink();
        lcd.setCursor(0,0);
        lcd.print("1.SERVO-1 4.SERVO-4");
        lcd.setCursor(0,1);
        lcd.print("2.SERVO-2 5.SERVO-5");
        lcd.setCursor(0,2);
        lcd.print("3.SERVO-3 6.SERVO-6");
        lcd.setCursor(0,3);
        lcd.print("PRESS BACK TO RETURN");
        lcd.setCursor(0,0);
        lcd.blink();
        option = 0;
        while(1)
        {
          delay(100);
          switch(option)
          {
          case 0:
            lcd.setCursor(0,0);
            break;
          case 1:
            lcd.setCursor(0,1);
            break;
          case 2:
            lcd.setCursor(0,2);
            break;
          case 3:
            lcd.setCursor(10,0);
            break;
          case 4:
            lcd.setCursor(10,1);
            break;
          case 5:
            lcd.setCursor(10,2);
            break;
          }
          if( digitalRead(up))
          {
            digitalWrite(L1,LOW);
            digitalWrite(L2,HIGH);
            digitalWrite(L3,LOW);
            digitalWrite(L4,LOW);
            digitalWrite(L5,LOW);
            option-=1;
            option = option<0?0:option;
          }
          else if( digitalRead(down))
          {
            digitalWrite(L1,LOW);
            digitalWrite(L2,LOW);
            digitalWrite(L3,HIGH);
            digitalWrite(L4,LOW);
            digitalWrite(L5,LOW);
            option+=1;
            option = option>5?5:option;
          }
          else if( digitalRead(back))
          {
            digitalWrite(L1,LOW);
            digitalWrite(L2,LOW);
            digitalWrite(L3,LOW);
            digitalWrite(L4,HIGH);
            digitalWrite(L5,LOW);
            goto label;
          }
          else if( digitalRead(ok))
          {
            digitalWrite(L1,LOW);
            digitalWrite(L2,LOW);
            digitalWrite(L3,LOW);
            digitalWrite(L4,LOW);
            digitalWrite(L5,HIGH);
            int angle1 = 0;
            int angle2 = 0;
            switch(option)
            {
            case 0:
              angle1 = SERVO_INITIAL_VALUE[0];
              angle2 = SERVO_FINAL_VALUE[0];
              lcd.clear();
              lcd.noBlink();
              lcd.setCursor(0,0);
              lcd.print("SERVO-1 INI POS: ");
              lcd.setCursor(17,0);
              lcd.print(SERVO_INITIAL_VALUE[0]);
              lcd.setCursor(0,1);
              lcd.print("SERVO-1 FIN POS:");
              lcd.setCursor(17,1);
              lcd.print(SERVO_FINAL_VALUE[0]);
              lcd.setCursor(0,2);
              lcd.print("PRESS UP TO INCREASE");
              lcd.setCursor(0,3);
              lcd.print("PRESS DOWN TO DECRE");
              lcd.setCursor(17,0);
              lcd.blink();
              option = 0;
              while(1)
              {
                delay(100);
                switch(option)
                {
                case 0:
                  lcd.setCursor(17,0);
                  lcd.print(angle1);
                  if( digitalRead(up))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,HIGH);
                    digitalWrite(L3,LOW);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle1+=1;
                    angle1 = angle1>180?180:angle1;
                  }
                  else if( digitalRead(down))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,LOW);
                    digitalWrite(L3,HIGH);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle1-=1;
                    angle1 = angle1<0?0:angle1;
                  }
                  break;
                case 1:
                  lcd.setCursor(17,1);
                  lcd.print(angle2);
                  if( digitalRead(up))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,HIGH);
                    digitalWrite(L3,LOW);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle2+=1;
                    angle2 = angle2>180?180:angle2;
                  }
                  else if( digitalRead(down))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,LOW);
                    digitalWrite(L3,HIGH);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle2-=1;
                    angle2 = angle2<0?0:angle2;
                  }
                  break;
                }
                if( digitalRead(back))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,HIGH);
                  digitalWrite(L5,LOW);
                  SERVO_INITIAL_VALUE[0] = angle1;
                  SERVO_FINAL_VALUE[0] = angle2;
                  goto lavel2;
                }
                else if( digitalRead(ok))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,HIGH);
                  option = option==0?1:0;
                }
                if( digitalRead(hom))
                {
                  digitalWrite(L1,HIGH);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  return;
                }
              }
              break;
            case 1:
              angle1 = SERVO_INITIAL_VALUE[1];
              angle2 = SERVO_FINAL_VALUE[1];
              lcd.clear();
              lcd.noBlink();
              lcd.setCursor(0,0);
              lcd.print("SERVO-2 INI POS: ");
              lcd.setCursor(17,0);
              lcd.print(SERVO_INITIAL_VALUE[1]);
              lcd.setCursor(0,1);
              lcd.print("SERVO-2 FIN POS:");
              lcd.setCursor(17,1);
              lcd.print(SERVO_FINAL_VALUE[1]);
              lcd.setCursor(0,2);
              lcd.print("PRESS UP TO INCREASE");
              lcd.setCursor(0,3);
              lcd.print("PRESS DOWN TO DECRE");
              lcd.setCursor(17,0);
              lcd.blink();
              option = 0;
              while(1)
              {
                delay(100);
                switch(option)
                {
                case 0:
                  lcd.setCursor(17,0);
                  lcd.print(angle1);
                  if( digitalRead(up))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,HIGH);
                    digitalWrite(L3,LOW);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle1+=1;
                    angle1 = angle1>180?180:angle1;
                  }
                  else if( digitalRead(down))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,LOW);
                    digitalWrite(L3,HIGH);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle1-=1;
                    angle1 = angle1<0?0:angle1;
                  }
                  break;
                case 1:
                  lcd.setCursor(17,1);
                  lcd.print(angle2);
                  if( digitalRead(up))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,HIGH);
                    digitalWrite(L3,LOW);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle2+=1;
                    angle2 = angle2>180?180:angle2;
                  }
                  else if( digitalRead(down))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,LOW);
                    digitalWrite(L3,HIGH);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle2-=1;
                    angle2 = angle2<0?0:angle2;
                  }
                  break;
                }
                if( digitalRead(back))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,HIGH);
                  digitalWrite(L5,LOW);
                  SERVO_INITIAL_VALUE[1] = angle1;
                  SERVO_FINAL_VALUE[1] = angle2;
                  goto lavel2;
                }
                else if( digitalRead(ok))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,HIGH);
                  option = option==0?1:0;
                }
                if( digitalRead(hom))
                {
                  digitalWrite(L1,HIGH);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  return;
                }
              }
              break;
            case 2:
              angle1 = SERVO_INITIAL_VALUE[2];
              angle2 = SERVO_FINAL_VALUE[2];
              lcd.clear();
              lcd.noBlink();
              lcd.setCursor(0,0);
              lcd.print("SERVO-3 INI POS: ");
              lcd.setCursor(17,0);
              lcd.print(SERVO_INITIAL_VALUE[2]);
              lcd.setCursor(0,1);
              lcd.print("SERVO-3 FIN POS:");
              lcd.setCursor(17,1);
              lcd.print(SERVO_FINAL_VALUE[2]);
              lcd.setCursor(0,2);
              lcd.print("PRESS UP TO INCREASE");
              lcd.setCursor(0,3);
              lcd.print("PRESS DOWN TO DECRE");
              lcd.setCursor(17,0);
              lcd.blink();
              option = 0;
              while(1)
              {
                delay(100);
                switch(option)
                {
                case 0:
                  lcd.setCursor(17,0);
                  lcd.print(angle1);
                  if( digitalRead(up))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,HIGH);
                    digitalWrite(L3,LOW);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle1+=1;
                    angle1 = angle1>180?180:angle1;
                  }
                  else if( digitalRead(down))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,LOW);
                    digitalWrite(L3,HIGH);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle1-=1;
                    angle1 = angle1<0?0:angle1;
                  }
                  break;
                case 1:
                  lcd.setCursor(17,1);
                  lcd.print(angle2);
                  if( digitalRead(up))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,HIGH);
                    digitalWrite(L3,LOW);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle2+=1;
                    angle2 = angle2>180?180:angle2;
                  }
                  else if( digitalRead(down))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,LOW);
                    digitalWrite(L3,HIGH);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle2-=1;
                    angle2 = angle2<0?0:angle2;
                  }
                  break;
                }
                if( digitalRead(back))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,HIGH);
                  digitalWrite(L5,LOW);
                  SERVO_INITIAL_VALUE[2] = angle1;
                  SERVO_FINAL_VALUE[2] = angle2;
                  goto lavel2;
                }
                else if( digitalRead(ok))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,HIGH);
                  option = option==0?1:0;
                }
                if( digitalRead(hom))
                {
                  digitalWrite(L1,HIGH);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  return;
                }
              }
              break;
            case 3:
              angle1 = SERVO_INITIAL_VALUE[3];
              angle2 = SERVO_FINAL_VALUE[3];
              lcd.clear();
              lcd.noBlink();
              lcd.setCursor(0,0);
              lcd.print("SERVO-4 INI POS: ");
              lcd.setCursor(17,0);
              lcd.print(SERVO_INITIAL_VALUE[3]);
              lcd.setCursor(0,1);
              lcd.print("SERVO-4 FIN POS:");
              lcd.setCursor(17,1);
              lcd.print(SERVO_FINAL_VALUE[3]);
              lcd.setCursor(0,2);
              lcd.print("PRESS UP TO INCREASE");
              lcd.setCursor(0,3);
              lcd.print("PRESS DOWN TO DECRE");
              lcd.setCursor(17,0);
              lcd.blink();
              option = 0;
              while(1)
              {
                delay(100);
                switch(option)
                {
                case 0:
                  lcd.setCursor(17,0);
                  lcd.print(angle1);
                  if( digitalRead(up))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,HIGH);
                    digitalWrite(L3,LOW);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle1+=1;
                    angle1 = angle1>180?180:angle1;
                  }
                  else if( digitalRead(down))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,LOW);
                    digitalWrite(L3,HIGH);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle1-=1;
                    angle1 = angle1<0?0:angle1;
                  }
                  break;
                case 1:
                  lcd.setCursor(17,1);
                  lcd.print(angle2);
                  if( digitalRead(up))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,HIGH);
                    digitalWrite(L3,LOW);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle2+=1;
                    angle2 = angle2>180?180:angle2;
                  }
                  else if( digitalRead(down))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,LOW);
                    digitalWrite(L3,HIGH);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle2-=1;
                    angle2 = angle2<0?0:angle2;
                  }
                  break;
                }
                if( digitalRead(back))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,HIGH);
                  digitalWrite(L5,LOW);
                  SERVO_INITIAL_VALUE[3] = angle1;
                  SERVO_FINAL_VALUE[3] = angle2;
                  goto lavel2;
                }
                else if( digitalRead(ok))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,HIGH);
                  option = option==0?1:0;
                }
                if( digitalRead(hom))
                {
                  digitalWrite(L1,HIGH);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  return;
                }
              }
              break;
            case 4:
              angle1 = SERVO_INITIAL_VALUE[4];
              angle2 = SERVO_FINAL_VALUE[4];
              lcd.clear();
              lcd.noBlink();
              lcd.setCursor(0,0);
              lcd.print("SERVO-5 INI POS:");
              lcd.setCursor(17,0);
              lcd.print(SERVO_INITIAL_VALUE[4]);
              lcd.setCursor(0,1);
              lcd.print("SERVO-5 FIN POS:");
              lcd.setCursor(17,1);
              lcd.print(SERVO_FINAL_VALUE[4]);
              lcd.setCursor(0,2);
              lcd.print("PRESS UP TO INCREASE");
              lcd.setCursor(0,3);
              lcd.print("PRESS DOWN TO DECRE");
              lcd.setCursor(17,0);
              lcd.blink();
              option = 0;
              while(1)
              {
                delay(100);
                switch(option)
                {
                case 0:
                  lcd.setCursor(17,0);
                  lcd.print(angle1);
                  if( digitalRead(up))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,HIGH);
                    digitalWrite(L3,LOW);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle1+=1;
                    angle1 = angle1>180?180:angle1;
                  }
                  else if( digitalRead(down))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,LOW);
                    digitalWrite(L3,HIGH);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle1-=1;
                    angle1 = angle1<0?0:angle1;
                  }
                  break;
                case 1:
                  lcd.setCursor(17,1);
                  lcd.print(angle2);
                  if( digitalRead(up))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,HIGH);
                    digitalWrite(L3,LOW);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle2+=1;
                    angle2 = angle2>180?180:angle2;
                  }
                  else if( digitalRead(down))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,LOW);
                    digitalWrite(L3,HIGH);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle2-=1;
                    angle2 = angle2<0?0:angle2;
                  }
                  break;
                }
                if( digitalRead(back))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,HIGH);
                  digitalWrite(L5,LOW);
                  SERVO_INITIAL_VALUE[4] = angle1;
                  SERVO_FINAL_VALUE[4] = angle2;
                  goto lavel2;
                }
                else if( digitalRead(ok))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,HIGH);
                  option = option==0?1:0;
                }
                if( digitalRead(hom))
                {
                  digitalWrite(L1,HIGH);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  return;
                }
              }
              break;
            case 5:
              angle1 = SERVO_INITIAL_VALUE[5];
              angle2 = SERVO_FINAL_VALUE[5];
              lcd.clear();
              lcd.noBlink();
              lcd.setCursor(0,0);
              lcd.print("SERVO-5 INI POS:");
              lcd.setCursor(17,0);
              lcd.print(SERVO_INITIAL_VALUE[5]);
              lcd.setCursor(0,1);
              lcd.print("SERVO-5 FIN POS:");
              lcd.setCursor(17,1);
              lcd.print(SERVO_FINAL_VALUE[5]);
              lcd.setCursor(0,2);
              lcd.print("PRESS UP TO INCREASE");
              lcd.setCursor(0,3);
              lcd.print("PRESS DOWN TO DECRE");
              lcd.setCursor(17,0);
              lcd.blink();
              option = 0;
              while(1)
              {
                delay(100);
                switch(option)
                {
                case 0:
                  lcd.setCursor(17,0);
                  lcd.print(angle1);
                  if( digitalRead(up))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,HIGH);
                    digitalWrite(L3,LOW);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle1+=1;
                    angle1 = angle1>180?180:angle1;
                  }
                  else if( digitalRead(down))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,LOW);
                    digitalWrite(L3,HIGH);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle1-=1;
                    angle1 = angle1<0?0:angle1;
                  }
                  break;
                case 1:
                  lcd.setCursor(17,1);
                  lcd.print(angle2);
                  if( digitalRead(up))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,HIGH);
                    digitalWrite(L3,LOW);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle2+=1;
                    angle2 = angle2>180?180:angle2;
                  }
                  else if( digitalRead(down))
                  {
                    digitalWrite(L1,LOW);
                    digitalWrite(L2,LOW);
                    digitalWrite(L3,HIGH);
                    digitalWrite(L4,LOW);
                    digitalWrite(L5,LOW);
                    angle2-=1;
                    angle2 = angle2<0?0:angle2;
                  }
                  break;
                }
                if( digitalRead(back))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,HIGH);
                  digitalWrite(L5,LOW);
                  SERVO_INITIAL_VALUE[5] = angle1;
                  SERVO_FINAL_VALUE[5] = angle2;
                  goto lavel2;
                }
                else if( digitalRead(ok))
                {
                  digitalWrite(L1,LOW);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,HIGH);
                  option = option==0?1:0;
                }
                if( digitalRead(hom))
                {
                  digitalWrite(L1,HIGH);
                  digitalWrite(L2,LOW);
                  digitalWrite(L3,LOW);
                  digitalWrite(L4,LOW);
                  digitalWrite(L5,LOW);
                  return;
                }
              }
              break;
            }
          }
          if( digitalRead(hom))
          {
            digitalWrite(L1,HIGH);
            digitalWrite(L2,LOW);
            digitalWrite(L3,LOW);
            digitalWrite(L4,LOW);
            digitalWrite(L5,LOW);
            return;
          }
        }
        break;
      }
    }
    if( digitalRead(hom))
    {
      digitalWrite(L1,HIGH);
      digitalWrite(L2,LOW);
      digitalWrite(L3,LOW);
      digitalWrite(L4,LOW);
      digitalWrite(L5,LOW);
      break;
    }
  }
}













void SD_CONTROL()
{
  lcd.clear();
  lcd.noBlink();
  lcd.print("NOT IMPLEMENTED YET");
  lcd.setCursor(0,1);
  lcd.print("PRESS HOME TO RETURN");
  while(1)
  {
    delay(100);
    //write code here


    if( digitalRead(hom))
    {
      digitalWrite(L1,HIGH);
      digitalWrite(L2,LOW);
      digitalWrite(L3,LOW);
      digitalWrite(L4,LOW);
      digitalWrite(L5,LOW);
      break;
    }
  }
}

void Initialize_valiable()
{
  lcd.clear();
  lcd.noBlink();
  lcd.print("NOT IMPLEMENTED YET");
  lcd.setCursor(0,1);
  lcd.print("PRESS HOME TO RETURN");
  while(1)
  {
    delay(100);
    //write code here
    if( digitalRead(hom))
    {
      digitalWrite(L1,HIGH);
      digitalWrite(L2,LOW);
      digitalWrite(L3,LOW);
      digitalWrite(L4,LOW);
      digitalWrite(L5,LOW);
      break;
    }
  }
}

void Do_the_job()
{
  lcd.clear();
  lcd.noBlink();
  lcd.print("NOT IMPLEMENTED YET");
  lcd.setCursor(0,1);
  lcd.print("PRESS HOME TO RETURN");
  while(1)
  {
    delay(100);
    //write code here
    if( digitalRead(hom))
    {
      digitalWrite(L1,HIGH);
      digitalWrite(L2,LOW);
      digitalWrite(L3,LOW);
      digitalWrite(L4,LOW);
      digitalWrite(L5,LOW);
      break;
    }
  }
}

void check_buzzer()
{
  lcd.clear();
  lcd.noBlink();
  lcd.setCursor(0,0);
  lcd.print("BLOWING BUZZER FOR");
  lcd.setCursor(9,1);
  lcd.print("10s");
  blow_buzzer(10000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PRESS HOME TO RETURN");
  while(1)
  {
    delay(100);
    if( digitalRead(hom))
    {
      digitalWrite(L1,HIGH);
      digitalWrite(L2,LOW);
      digitalWrite(L3,LOW);
      digitalWrite(L4,LOW);
      digitalWrite(L5,LOW);
      break;
    }
  }
}

void blow_buzzer(int duration)
{
  digitalWrite(buzzer,HIGH);
  delay(duration);
  digitalWrite(buzzer,LOW);
}


void set_motor_speed()
{
  lcd.clear();
  lcd.noBlink();
  while(1)
  {
    if( digitalRead(hom))
    {
      digitalWrite(L1,HIGH);
      digitalWrite(L2,LOW);
      digitalWrite(L3,LOW);
      digitalWrite(L4,LOW);
      digitalWrite(L5,LOW);
      analogWrite(m1,0);
      analogWrite(m4,0);
      break;
    }
    else if( digitalRead(up))
    {
      digitalWrite(L1,LOW);
      digitalWrite(L2,HIGH);
      digitalWrite(L3,LOW);
      digitalWrite(L4,LOW);
      digitalWrite(L5,LOW);
      motor_base_speed=motor_base_speed+1;
    }
    else if( digitalRead(down))
    {
      digitalWrite(L1,LOW);
      digitalWrite(L2,LOW);
      digitalWrite(L3,HIGH);
      digitalWrite(L4,LOW);
      digitalWrite(L5,LOW);
      motor_base_speed=motor_base_speed-1;
    }
    lcd.print("Current Motor base");
    lcd.setCursor(0,1);
    lcd.print("Speed is: ");
    lcd.print(motor_base_speed);
    lcd.setCursor(0,2);
    lcd.print("MAX SPEED CAN BE 256");
    lcd.setCursor(0,3);
    lcd.print("PRESS HOME TO RETURN");
    analogWrite(m1,motor_base_speed);
    analogWrite(m4,motor_base_speed);
    delay(200);
  }
}

void button_check()
{
  if( digitalRead(hom))
  {
    digitalWrite(L1,HIGH);
    digitalWrite(L2,LOW);
    digitalWrite(L3,LOW);
    digitalWrite(L4,LOW);
    digitalWrite(L5,LOW);
  }
  else if( digitalRead(up))
  {
    digitalWrite(L1,LOW);
    digitalWrite(L2,HIGH);
    digitalWrite(L3,LOW);
    digitalWrite(L4,LOW);
    digitalWrite(L5,LOW);
  }
  else if( digitalRead(down))
  {
    digitalWrite(L1,LOW);
    digitalWrite(L2,LOW);
    digitalWrite(L3,HIGH);
    digitalWrite(L4,LOW);
    digitalWrite(L5,LOW);
  }
  else if( digitalRead(back))
  {
    digitalWrite(L1,LOW);
    digitalWrite(L2,LOW);
    digitalWrite(L3,LOW);
    digitalWrite(L4,HIGH);
    digitalWrite(L5,LOW);
  }
  else if( digitalRead(ok))
  {
    digitalWrite(L1,LOW);
    digitalWrite(L2,LOW);
    digitalWrite(L3,LOW);
    digitalWrite(L4,LOW);
    digitalWrite(L5,HIGH);
  }
}

void check_IR()
{
  while(!digitalRead(hom))
  {
    lcd.clear();
    lcd.noBlink();
    lcd.setCursor(0,0);
    int value = analogRead(left1);
    String s="L1="+String(value);
    value = analogRead(left2);
    s=s+"L2="+String(value);
    value = analogRead(left3);
    s=s+"L3="+String(value);
    lcd.print(s);
    Serial.println(s);

    lcd.setCursor(0,1);
    value = analogRead(middle);
    s="m="+String(value)+"  ";
    lcd.print(s);
    Serial.println(s);

    lcd.setCursor(0,2);
    value = analogRead(right3);
    s="R3="+String(value);
    value = analogRead(right2);
    s=s+"R2="+String(value);
    value = analogRead(right1);
    s=s+"R1="+String(value);
    lcd.print(s);
    Serial.println(s);

    lcd.setCursor(0,3);
    s="PRESS HOME TO RETURN";
    lcd.print(s);
    Serial.println(s);
    delay(1000);
    if( digitalRead(hom))
    {
      digitalWrite(L1,HIGH);
      digitalWrite(L2,LOW);
      digitalWrite(L3,LOW);
      digitalWrite(L4,LOW);
      digitalWrite(L5,LOW);
      break;
    }
  }  
}


































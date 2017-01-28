
int previous_error = 0;
float integral = 0;
float derivatve = 0;
int line_flow_using_pid(int left1,int left2,int middle,int right2,int right1,int dt,int kp,int ki,int kd,int sensor_basevalue[],int tp int offset)
{
  int error = 0;
  int output = 0;
  error = error - 2 * map(analogRead(left1),sensor_basevalue[0],sensor_basevalue[1],0,128);
  error = error - map(analogRead(left2),sensor_basevalue[2],sensor_basevalue[3],0,128);
  //error = error + map(analogRead(middle),sensor_basevalue[4],sensor_basevalue[5],0,128);
  error = error + map(analogRead(right2),sensor_basevalue[6],sensor_basevalue[7],0,128);
  error = error + 2 * map(analogRead(right1),sensor_basevalue[8],sensor_basevalue[9],0,128);
  error = error - offset;
  integral = integral+error*dt;
  derivative = (error - previous_error)/dt;
  output = kp*error + ki*integral + kd*derivative;
  int powerA = tp + output;
  int powerB = tp - output;
  if(powerA>=0)
  {
    analogWrite(m1,powerA);
    analogWrite(m2,0);
  }
  else
  {
    analogWrite(m1,0);
    analogWrite(m2,(-1)*powerA); 
  }
  if(powerB>=0)
  {
    analogWrite(m3,powerB);
    analogWrite(m4,0);
  }
  else
  {
    analogWrite(m3,0);
    analogWrite(m4,(-1)*powerB); 
  }
  previous_error = error;
}


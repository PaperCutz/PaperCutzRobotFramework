#include <Wire.h>
#include <AFMotor.h>

//Code that goes with Papercutz.py to control a robot using a sainsmart motorshield.
//defines motorsheild as an object, always the same


AF_DCMotor right(1);
AF_DCMotor left(2);
AF_DCMotor weapon(4);

//right motor in port m1
//left motor in port m2


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}
String in;
int w_pow=128;
int y_pow=150;
int x_pow=128;
int r_pow=128;
int l_pow=128;
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    delay(5);
   char cmd = Serial.read();
 
  if(cmd == 121){
   in=Serial.readStringUntil(':');
    Serial.println(cmd+in);
   y_pow = 100*(in[0]-'0')+10*(in[1]-'0')+in[2]-'0';
 
  }else if(cmd == 120){
   in=Serial.readStringUntil(':');
     Serial.println(cmd+in);
   x_pow = 100*(in[0]-'0')+10*(in[1]-'0')+in[2]-'0';
  } else if(cmd == 115){
    in=Serial.readStringUntil(':');
      Serial.println(in);
    100*(in[0]-'0')+10*(in[1]-'0')+in[2]-'0';
  } else if(cmd==119) {
    in=Serial.readStringUntil(':');
   w_pow = 100*(in[0]-'0')+10*(in[1]-'0')+in[2]-'0';
    
  }
}
r_pow = map((y_pow-128)-(x_pow-128),-255,255,255,0);
l_pow = map((y_pow-128)+(x_pow-128),-255,255,255,0);
 motor_drive(weapon,w_pow);
 motor_drive(right,r_pow);
 motor_drive(left,l_pow);
delay(5);
}

unsigned char motor_mag(unsigned char x){
 //will take value that is zero at 128 and convert to 0 to 255
   unsigned char r; 
   if(x==128){
    r=0;
   } else if (x>128){
    r = map(x,128,255,0,255);
   } else if (x<128){
    r = map(x,0,128,255,0);
   } else {}

  return r;
}
unsigned char motor_dir(unsigned char x){
 //will take value that is zero at 128 and convert to 0 to 255
   unsigned char r;
   if(x==128){
    r=RELEASE;
   } else if (x>128){
    r = FORWARD;
   } else if (x<128){
    r = BACKWARD;
   } else {}
  return r;
}

void motor_drive(AF_DCMotor motor, unsigned char input){
  motor.run(motor_dir(input));
  motor.setSpeed(motor_mag(input));
}

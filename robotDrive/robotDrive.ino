#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Servo.h>
#include "utility/Adafruit_PWMServoDriver.h"

//defines motorsheild as an object, always the same
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *right = AFMS.getMotor(4);
Adafruit_DCMotor *left = AFMS.getMotor(3);
Servo tilt;
Servo pan;
//right motor in port m1
//left motor in port m2


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  AFMS.begin();
  
  tilt.attach(10);
  pan.attach(9);
}
int tilt_val = 128;
int pan_val = 128;
int i;
String in;
int y_pow=128;
int x_pow=128;
int r_pow=128;
int l_pow=128;
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
   delay(5);
   pan_val = Serial.read();
   tilt_val = Serial.read();
   x_pow = Serial.read();
   y_pow = Serial.read();
   
//   Serial.print(Serial.read());
//   Serial.print(Serial.read());
//   Serial.print(Serial.read());
//   Serial.println(Serial.read());
 //  if(tilt_val <=70){
//tilt_val = 70;
//   }
   }
  
r_pow = map((y_pow-128)-(x_pow-128),-255,255,255,0);
l_pow = map((y_pow-128)+(x_pow-128),-255,255,255,0);
 motor_drive(right,255-r_pow);
 motor_drive(left,l_pow);
 tilt.write(tilt_val);
 pan.write(pan_val);
delay(15);

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

void motor_drive(Adafruit_DCMotor *motor, unsigned char input){
  motor->run(motor_dir(input));
  motor->setSpeed(motor_mag(input));
}

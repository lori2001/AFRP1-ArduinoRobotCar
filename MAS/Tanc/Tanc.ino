#include "Ultrasonic.h"   //SZENZOR
#include "Arduino.h"      //SZENZOR

#define MOTORLATCH 12
#define MOTORCLK 4
#define MOTORENABLE 7
#define MOTORDATA 8
#define MOTOR1_A 2
#define MOTOR1_B 3
#define MOTOR2_A 1
#define MOTOR2_B 4
#define MOTOR3_A 7
#define MOTOR3_B 5
#define MOTOR4_A 0
#define MOTOR4_B 6
#define MOTOR1_PWM 11
#define MOTOR2_PWM 3
#define MOTOR3_PWM 6
#define MOTOR4_PWM 5
#define SERVO1_PWM 10
#define SERVO2_PWM 9
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4

Ultrasonic ultrasonic( 52, 53 );    //SZENZOR
int cm;                             //SZENZOR
                               
int SPEAKER = 22; //SPEAKER
int sec=1310;     //SPEAKER
int c = 261;      //SPEAKER
int d = 294;      //SPEAKER
int e = 329;      //SPEAKER
int f = 349;      //SPEAKER
int g = 391;      //SPEAKER
int gS = 415;     //SPEAKER
int a = 440;      //SPEAKER
int aS = 455;     //SPEAKER
int b = 466;      //SPEAKER
int cH = 523;     //SPEAKER
int cSH = 554;    //SPEAKER
int dH = 587;     //SPEAKER
int dSH = 622;    //SPEAKER
int eH = 659;     //SPEAKER
int fH = 698;     //SPEAKER
int fSH = 740;    //SPEAKER
int gH = 784;     //SPEAKER
int gSH = 830;    //SPEAKER
int aH = 880;     //SPEAKER
int DO = 261;     //SPEAKER
int RE = 294;     //SPEAKER
int MI = 329;     //SPEAKER
int FA = 349;     //SPEAKER
int SO = 391;     //SPEAKER
int La = 440;     //SPEAKER
int SI = 466;     //SPEAKER

void setup()
{
pinMode(SPEAKER,OUTPUT);
Serial.begin(9600);   //SZENZOR
}
void loop()
{
  
  int timing;                      //SZENZOR
  cm=ultrasonic.Ranging(CM);       //SZENZOR
                                   //SZENZOR
 if (cm<=8)                        //SZENZOR
   {    
  motor(2, BRAKE,30);
  motor(3, BRAKE,30);
  
  beep(500,sec/2);      //SPEAKER
  delay(sec/2);         //SPEAKER
  beep(300,sec/3);      //SPEAKER
  delay(sec/2);         //SPEAKER
     
  motor(3, BACKWARD, 200);
  motor(2, FORWARD, 200);
  
  delay(500);
  motor(2, BRAKE,30);
  motor(3, BRAKE,30);  
  delay(500);
  motor(2, BACKWARD, 200); // MOTOR 2 BACKWARD
  motor(3, BACKWARD, 200); // MOTOR 3 BACKWARD    
  }
   else
  {
    motor(3, BACKWARD, 200);
    beep(40,sec/2);
    delay(90);
    motor(3, BRAKE,30);
    delay(10);
    motor(2, FORWARD, 40);
    delay(9);
    motor(2, BRAKE,30);
    delay(1);
    motor(2, FORWARD, 45);
    delay(9);
    motor(2, BRAKE,30);
    delay(1);
    motor(3, BACKWARD, 200);
    beep(40,sec/2);
    delay(18);
    motor(3, BRAKE,30);
    delay(2);
    motor(3, BACKWARD, 200);
    beep(40,sec/2);
    delay(90);
    motor(3, BRAKE,30);
    delay(10);
    motor(2, FORWARD, 40);
    delay(9);
    motor(2, BRAKE,30);
    delay(1);
    motor(2, FORWARD, 45);
    delay(9);
    motor(2, BRAKE,30);
    delay(1);
    beep(20,sec);     
  }
}
void beep(int note, int duration) //SPEAKER
{                                 //SPEAKER
tone(SPEAKER, note, duration);    //SPEAKER
}                                 //SPEAKER
void motor(int nMotor, int command, int speed)
{
  int motorA, motorB;

  if (nMotor >= 1 && nMotor <= 4)
  {  
    switch (nMotor)
    {
    case 1:
      motorA   = MOTOR1_A;
      motorB   = MOTOR1_B;
      break;
    case 2:
      motorA   = MOTOR2_A;
      motorB   = MOTOR2_B;
      break;
  case 3:
      motorA   = MOTOR3_A;
      motorB   = MOTOR3_B;
      break;
    case 4:
      motorA   = MOTOR4_A;
      motorB   = MOTOR4_B;
      break; 
    default:
      break;
    }

    switch (command)
    {
    case FORWARD:
      motor_output (motorA, HIGH, speed);
      motor_output (motorB, LOW, -1);     // -1: no PWM set
      break;
    case BACKWARD:
      motor_output (motorA, LOW, speed);
      motor_output (motorB, HIGH, -1);    // -1: no PWM set
      break;
    case BRAKE:
      motor_output (motorA, LOW, 255); // 255: fully on.
      motor_output (motorB, LOW, -1);  // -1: no PWM set
      break;
    case RELEASE:
      motor_output (motorA, LOW, 0);  // 0: output floating.
      motor_output (motorB, LOW, -1); // -1: no PWM set
      break;
    default:
      break;
    }
  }
}
void motor_output (int output, int high_low, int speed)
{
  int motorPWM;

  switch (output)
  {
  case MOTOR1_A:
  case MOTOR1_B:
    motorPWM = MOTOR1_PWM;
    break;
  case MOTOR2_A:
  case MOTOR2_B:
    motorPWM = MOTOR2_PWM;
    break;
case MOTOR3_A:
  case MOTOR3_B:
    motorPWM = MOTOR3_PWM;
    break;
  case MOTOR4_A:
  case MOTOR4_B:
    motorPWM = MOTOR4_PWM;
    break;
  default:
    speed = -3333;
    break;
  }

  if (speed != -3333)
  {
    shiftWrite(output, high_low);
    if (speed >= 0 && speed <= 255)    
    {
      analogWrite(motorPWM, speed);
    }
  }
}
void shiftWrite(int output, int high_low)
{
  static int latch_copy;
  static int shift_register_initialized = false;

  if (!shift_register_initialized)
  {
    pinMode(MOTORLATCH, OUTPUT);
    pinMode(MOTORENABLE, OUTPUT);
    pinMode(MOTORDATA, OUTPUT);
    pinMode(MOTORCLK, OUTPUT);

    digitalWrite(MOTORDATA, LOW);
    digitalWrite(MOTORLATCH, LOW);
    digitalWrite(MOTORCLK, LOW);
    digitalWrite(MOTORENABLE, LOW);

    latch_copy = 0;
    shift_register_initialized = true;
  }
  bitWrite(latch_copy, output, high_low);
  
  shiftOut(MOTORDATA, MOTORCLK, MSBFIRST, latch_copy);
  delayMicroseconds(5);    // For safety, not really needed.
  digitalWrite(MOTORLATCH, HIGH);
  delayMicroseconds(5);    // For safety, not really needed.
  digitalWrite(MOTORLATCH, LOW);
}

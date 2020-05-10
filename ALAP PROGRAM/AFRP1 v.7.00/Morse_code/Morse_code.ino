
#include "Ultrasonic.h"
#include "Arduino.h"
#include "Servo.h"

//Motors and Flashlight 
 #define MOTORLATCH 12
 #define MOTORCLK 4
 #define MOTORENABLE 7
 #define MOTORDATA 8

 #define FLASH_A 1
 #define FLASH_B 4
 #define FLAG_A 2  
 #define FLAG_B 3  
 #define MOTOR3_A 7
 #define MOTOR3_B 5  
 #define MOTOR4_A 0 
 #define MOTOR4_B 6 

 #define FLAG_PWM 11
 #define MOTOR3_PWM 6 
 #define MOTOR4_PWM 5
 #define FLASH_PWM   3

 #define FORWARD 1
 #define BACKWARD 2
 #define BRAKE 3
 #define RELEASE 4

int time_unit = 100; //stores in miliseconds the time unit
int noprinting = false;

#include "Commands.h" 

void setup() 
{
 Serial.begin(9600);

  
 morse("Hello, I'm AFRP1");

}

void loop() {
  // put your main code here, to run repeatedly:

}

void morse(String text )//char text[255])
{
 char text_array[text.length()];

 text.toCharArray(text_array,text.length());
 
 Serial.print(text_array);
}



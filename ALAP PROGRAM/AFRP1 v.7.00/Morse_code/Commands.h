
void shiftWrite(  int output,  int high_low) 
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

void motor_output (  int output,  int high_low,  int speed) 
{
  int motorPWM;

  switch (output)
  {
  case FLAG_A:
  case FLAG_B:
    motorPWM = FLAG_PWM;
    break;
  case FLASH_A:
  case FLASH_B:
    motorPWM = FLASH_PWM ;
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

void motor(int nMotor, int command, int speed)
{
  int motorA, motorB;
  char printcommand[10];

  if (nMotor == 1 || 2 || 3 || 4)
  {
    switch (nMotor)
    {
    case 1:
      motorA   = FLAG_A;
      motorB   = FLAG_B;
      break;
    case 2:
      motorA   = FLASH_A;
      motorB   = FLASH_B;
      break;                     //MOTOR                THE DEFINITION OF MOTOR COMMAND... 
    case 3:                      //MOTOR      
      motorA   = MOTOR3_A;       //MOTOR       Formula:
      motorB   = MOTOR3_B;       //MOTOR   
      break;                     //MOTOR          motor(motor pin, action, speed)
    case 4:                      //MOTOR   motor:1(not_in_use) 2(not_in_use) 3(right) 4(left)
      motorA   = MOTOR4_A;       //MOTOR   action: FORWARD BACKWARD BRAKE RELEASE
      motorB   = MOTOR4_B;       //MOTOR
      break;                     //MOTOR             1        2      3      4
    default:                     //MOTOR   speed:0-255 -- if speed = 255: 1400ms are needed for the tyre for 1 turn...if 1 tyre is in use
      break;                     //MOTOR         the robot goes ~90degree in 1400 ms
    }
    switch (command)
    {
    case FORWARD:
      motor_output (motorA, HIGH, speed);
      motor_output (motorB, LOW, -1);
      strncpy(printcommand, "Forward", 8);
      break;
    case BACKWARD:
      motor_output (motorA, LOW, speed);
      motor_output (motorB, HIGH, -1);
      strncpy(printcommand, "Backward", 9);
      break; 
    case BRAKE:
      motor_output (motorA, LOW, 255);     // 255: max speed
      motor_output (motorB, LOW, -1);
      strncpy(printcommand, "Brake", 6);
      break;
    case RELEASE:
      motor_output (motorA, LOW, 0);       // 0: output floating.
      motor_output (motorB, LOW, -1);
      strncpy(printcommand, "Release", 8);
      break;
    default:
      break;
    }
  }
  if(!noprinting)
  {
   Serial.println(""); 
   Serial.print("Motor=");
   Serial.print(nMotor);
   Serial.print(" || Command=");
   Serial.print(printcommand);
   Serial.print(" || Speed=");
   Serial.print(speed);
  }
}

void forward (int sp)                              
{
  motor(3, FORWARD , sp); 
  motor(4, FORWARD , sp); 
}                                                    
void backward (int sp)                        
{  
  motor(3, BACKWARD, sp);
  motor(4, BACKWARD, sp);                                                   
}                                                   
void right (int sp)                               
{                     
  motor(3, BACKWARD, sp);
  motor(4, FORWARD, sp); 
}                                            
void left (int sp)                           
{ 
  motor(3, FORWARD, sp);
  motor(4, BACKWARD , sp); 
}                                                   
void brake (int sp)                            
{ 
  if(!noprinting)
  {Serial.println("");}
  motor(3,  BRAKE  , sp); 
  motor(4,  BRAKE  , sp);
}                                                    
                         



void beep(int note, int duration) 
{
 pinMode(VOICE,OUTPUT);
 //Actual beeping command
 tone(VOICE, note, duration);  
 
 //Printing out
 if(!noprinting)
 {
  Serial.println("");
  Serial.print("Beep=");
  Serial.print(note);
  Serial.print("hz ");
  Serial.print(duration);
  Serial.print("ms");
 }

  //LED 
  if (note <= 450)
  {
     digitalWrite(LED[0], HIGH);
     digitalWrite(LED[1], HIGH);
     delay(duration);
     digitalWrite(LED[0], LOW);
     digitalWrite(LED[1], LOW);
  }
  else if (note > 450 && note <= 650)
  {
     digitalWrite(LED[2], HIGH); //1 es 2
     digitalWrite(LED[3], HIGH); //1-high 2-low
     delay(duration);
     digitalWrite(LED[2], LOW);
     digitalWrite(LED[3], LOW);
  }
  else
  {
     digitalWrite(LED[4], HIGH);
     digitalWrite(LED[5], HIGH);
     delay(duration);
     digitalWrite(LED[4], LOW);
     digitalWrite(LED[5], LOW);
  }
}

void serpos (float angle, int miliseconds) 
{
 Head_rotate.write(angle);
 delay(miliseconds);

 if(!noprinting)
 {
  Serial.println("");
  Serial.print("Servo at ");
  Serial.print(angle);
  Serial.print(" degrees");
 }
}

void shiftWrite(int output,  int high_low) 
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
  motor(3,  BRAKE  , sp); 
  motor(4,  BRAKE  , sp);
}                                                    
                         
void StarWars ()                                                
{                                                                                                                                                                                                                                                                         
 Serial.println("StarWars Indul.."); 
 noprinting = true;   

              int  c = 261 , d = 294 , e = 329 , f = 349 , g = 391 , gS = 415 , a = 440 , aS = 455 , b = 466 ,  //Music notes in Hz
     cH = 523 , cSH = 554 , dH = 587 , dSH = 622 , eH = 659 , fH = 698 , fSH = 740 , gH = 784  , 
     gSH = 830 , aH = 880;  

                                                
  forward(100);               
  delay(100);     
  beep(a, 500);                                                
  beep(a, 500);                                                      
  beep(a, 500);                                                                                    
  backward(250);               
  delay(25);   
  beep(f, 350);                                                                                
  forward(100);           
  delay(100);
  beep(cH, 150);                                                     
  beep(a, 500);                                                                                      
  backward(250);          
  delay(25);
  beep(f, 350);                                                                          
  forward(100);            
  delay(100);
  beep(cH, 150);                                                  
  beep(a, 650);                                                                                                                                                                                       
  brake(255);                                                    
  delay(500);                                                                                            
  forward(100);          
  delay(100);
  beep(eH, 500);                                                 
  beep(eH, 500);                                                
  beep(eH, 500);                                                                                  
  backward(250);           
  delay(25);
  beep(fH, 350);                                                                                    
  forward(100);              
  delay(100);
  beep(cH, 150);                                                 
  beep(gS, 500);                                                                                    
  backward(250);            
  delay(25);
  beep(f, 350);                                                                                    
  forward(100);           
  delay(100);
  beep(cH, 150);                                                  
  beep(a, 650);                                                           
  brake(255);                                                                     
  delay(500);                                                                                                      
  motor(4, FORWARD , 250);            
  delay(25);                                                              
  beep(aH, 500);                                                            
  motor(4, BACKWARD , 100);        
  delay(100);
  beep(a, 300);                                                   
  beep(a, 150);                                                                
  brake(255);                    
  motor(3, FORWARD , 250);            
  delay(25);   
  beep(aH, 500);                                                                             
  motor(3, BACKWARD , 100);         
  delay(100);
  beep(gSH, 325);                                                     
  beep(gH, 175);                                       
  brake(255);                                                  
  backward(250);                
  delay(70);
  beep(fSH, 125);                                                 
  beep(fH, 125);                                                 
  beep(fSH, 250);                                                                            
  brake(255);       
  delay(325);                                                                                                   
  forward(100);                
  delay(100);                                                                         
  beep(aS, 250);                                                  
  beep(dSH, 500);                                                 
  beep(dH, 325);                                                                
  backward(250);               
  delay(70);
  beep(cSH, 175);                                            
  beep(cH, 125);
  beep(b, 125);                                                   
  beep(cH, 250);                                                      
  brake(255);      
  delay(350);    
  forward(100);              
  delay(100);                                                       
  beep(f, 250);                                                   
  beep(gS, 500);                                      
  brake(255);                                                         
  motor(4, FORWARD , 250);             
  delay(25); 
  beep(f, 350);                                                                              
  motor(4, BACKWARD , 100);          
  delay(100);
  beep(a, 125);                                                  
  beep(cH, 500);                                       
  brake(255);                   
  motor(3, FORWARD , 250);        
  delay(25); 
  beep(a, 375);                                                            
  motor(3, BACKWARD , 100);           
  delay(100);
  beep(cH, 125);                                                 
  beep(eH, 650);                                                                  
  brake(255);
  delay(500);                                                                                                       
  motor(3, FORWARD , 250);         
  delay(25);                                                                                            
  beep(aH, 500);                                                      
  motor(3, BACKWARD , 100);           
  delay(100);
  beep(a, 300);                                                   
  beep(a, 150);                                                  
  brake(255);    
  motor(4, FORWARD , 250);           
  delay(25);   
  beep(aH, 500);                                                                             
  motor(4, BACKWARD , 100);          
  delay(100);
  beep(gSH, 325);                                                
  beep(gH, 175);                                                                        
  backward(250);                
  delay(70);
  beep(fSH, 125);                                                
  beep(fH, 125);                                               
  beep(fSH, 250);                                         
  brake(255);                                                          
  delay(325);                                               
  forward(100);                 
  delay(100);                                                                         
  beep(aS, 250);                                                 
  beep(dSH, 500);                                              
  beep(dH, 325);                                                                     
  backward(250);                 
  delay(70);
  beep(cSH, 175);                                                 
  beep(cH, 125);
  beep(b, 125);                                              
  beep(cH, 250);                                                                
  brake(255);                                                      
  delay(350);                                                   
  forward(100);                  
  delay(100);                                                            
  beep(f, 250);                                                  
  beep(gS, 500);                                       
  brake(255);                                                       
  motor(4, FORWARD , 250);            
  delay(25);
  beep(f, 375);                                                        
  motor(4, BACKWARD , 100);         
  delay(100);
  beep(cH, 125);                                          
  beep(a, 500);                                        
  brake(255);                                                  
  motor(3, FORWARD , 250);           
  delay(25);  
  beep(f, 375);                                                        
  motor(3, BACKWARD  , 100);        
  delay(100);
  beep(cH, 125);                                                  
  beep(a, 500);                                                      
  brake(255);                                                                                   
  delay(650);
  
  noprinting = false;
  Serial.println("StarWars befejezodott.");                                                                           
}  

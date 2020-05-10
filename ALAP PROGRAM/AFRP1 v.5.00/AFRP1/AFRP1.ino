#include "Ultrasonic.h"
#include "Arduino.h" 
#include "Servo.h"

             
#define MOTORLATCH 12                        
#define MOTORCLK 4                                   
#define MOTORENABLE 7                                
#define MOTORDATA 8       
 
#define MOTOR3_A 7 
#define MOTOR3_B 5                          /**         ////       ///////   ///////   ///////      ////                                        **/
#define MOTOR4_A 0                          /**        //  //      //        //   //   //   //     // //                                        **/
#define MOTOR4_B 6                          /**       ////////     ///////   ///////   ///////    //  //                  Credits to LORIXD     **/ 
                                            /**      //////////    //        ////      //             //                @@ Coprights 2014 @@    **/
#define MOTOR3_PWM 6                        /**     //        //   //        //  //    //             //                                        **/
#define MOTOR4_PWM 5                        /**    //          //  //        //   //   //             //                                        **/
#define SERVO1_PWM 10                                 
#define SERVO2_PWM 9                                   
   
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4 
   
#define SPEAKER 22
#define LED1 13
#define LED2 13
#define SERVO 10
   
   
Servo Head_rotate;     //Defines command for servo
Ultrasonic ultrasonic( 52, 53 );   //Defines ultrasonic sensor pins 

int  c = 261 , d = 294 , e = 329 , f = 349 , g = 391 , gS = 415 , a = 440 , aS = 455 , b = 466 ,  //Music notes in Hz
     cH = 523 , cSH = 554 , dH = 587 , dSH = 622 , eH = 659 , fH = 698 , fSH = 740 , gH = 784  , 
     gSH = 830 , aH = 880;  
    
int  LED1State   = LOW ,   //It will help on sincronizating the leds whit the piezo speaker                       
      LED2State  = LOW ,       
       LED_Blink = 0   ;   //Because we have 2 leds we need this variable to   

int  Fatigue   = 0       ,  // It will help at simulating the fatigue.. Motorspeed=Speed-Fatigue
      Waittime = 3000    ;  //Wait time before fatigue increases.Has as value 3 seconds. 

long Previous_millis = 0 ,  // Saves the millis in this variable when fatigue increases than if the milis-this variable > the waittime 
     Previous_time   = 0 ;  // Saves the current value of the millis in this variable every 10ms and helps at exactity of the ultrasonic senzor

int  Star_Wars_will_be = false, //Its false if the starwars wont t and its true if it will be
     Stop_repeat       = false, // A variable that when its increased it will end a while funcion 
     Dont_print_motors = false; // when this number is true the robot doesnt prints anything about motors, when its false the robot works normal 

int  Stunned         , //A function what when it earns a specified value the robot concludes that it s stunned
      Stun_point = 75; //A variable that will store a number. When "Stunned" is greater that this value the robot realises that its been stunned
                                                  
long Random_action     , //A value that generates a number whit some circumstances (down in the program). Depending on the value the robot chooses what to do.  
      Random_speed     , //-||-.Depending on the value the robot chooses the speed. Motorspeed=Random_speed-Fatigue
       Random_direction; //-||-.Depending on the value the robot chooses the direction (left or right)

int  Second = 1000; //Creates a variable which has a second as value                                               

int  Front_distance         , //This value will store the distance for the ultrasonic sensor to the object when its head is 90 degree (front)
      Front_distance_verify , //This value will veryfy if the first was correct or it wasn t
     Side_distance          ; //This variable will store the distance for the ultrasonic sensor to the object when its head is 0 degree (right) or 180 degree (left)     
     
int  Side_move; // A variable that helps on the "void Walk" logic 
     
/******************************************************************************************************************************************************************************/
/******************************************************************************************************************************************************************************/
/******************************************************************************************************************************************************************************/
/******************************************************************************************************************************************************************************/

void setup()                                                                   
{                                            
     Serial.begin(9600); //begins serial at 9600 baud
     Serial.println("");  
 
     Serial.print("A");delay(75);Serial.print("F");delay(125);Serial.print("R");delay(175);Serial.print("P");delay(275);Serial.print("1");delay(275);
     Serial.print(" ");delay(175);Serial.print("E");delay(75);Serial.print("l");delay(145);Serial.print("i");delay(75);Serial.print("n");delay(125); 
     Serial.print("d");delay(125);Serial.print("u");delay(155);Serial.print("l");delay(75);Serial.print("t ");delay(155);Serial.println("!");delay(300);
                                                                                                          // Writes "AFRP1 Elindult" whit an effect
     Serial.println("");           
     pinMode(LED1, OUTPUT);              /** view colum 27  */
     Serial.print("LED1 = ");     
     Serial.println(LED1);                                    

     pinMode(LED2, OUTPUT);              /** view colum 28  */
     Serial.print("LED2 = ");             
     Serial.println(LED2);                         

     pinMode(SPEAKER,OUTPUT);            /** view colum 26  */  
     Serial.print("Speaker = ");   
     Serial.println(SPEAKER);                                                

     Head_rotate.attach(SERVO);          /** view colum 29  */
     Serial.print("Servo = ");         /*Attaches servo motor*/
     Serial.println(SERVO);                 
     Serial.println("");             

     Head_rotate.write(90);    //Servo at 90 degree                          
     delay(300);               //Delays (x) miliseconds (1000 ms = 1 sec)  
   
     beep(900,300);    
     beep(1200,200);                     /** view colum 633  */                                 
     beep(900,300);    
     beep(1200,500); 
  
     Serial.println("");           
}
     
void loop()
{            
    Front_distance = ultrasonic.Ranging(CM);   /** view colum 33,63  */ // colum 76 is needed for this too
    delay(20);    
   
    Verify_stun();    /** view colum 172 */  
    delay(5);  
 
    Walk();       /** view colum 203 */ 
    delay(5); 
     
  if (millis() - Previous_millis > Waittime)  /** view colum 46,44 */ 
  {
      Previous_millis = millis();

      Fatigue++;     /** view colum 43 */ 
    
      Serial.print("Faradtsag = ");    
      Serial.println(Fatigue);         
      Serial.println("");                  
  }
 
  if ( Front_distance>0 && Front_distance<=13 )  /** view colum 63 */                                                  
  {     
      Serial.print("Targy ");          
      Serial.print(Front_distance);    
      Serial.println("cm -re.");                                                         


      Fatigue++;    /** view colum 43 */ 
       Serial.print("Faradtsag = ");   
       Serial.println(Fatigue);                

      ALLBRAKE(30);                                               
      delay(20);                                                 

      Serial.println("");             
      
      beep(500,Second/2);                                                        
      beep(300,Second/3);                                                        
      
      Serial.println("");            
  
      Detect();  /** view colum 393 */ 
      
      }                                                                                                                                                                                                               
   
 if (Serial.available())
 {
     Keyboard_control(); /** view colum 521 */ 
     delay(15);  //for safety
 }
}

/******************************************************************************************************************************************************************************/
/******************************************************************************************************************************************************************************/
/******************************************************************************************************************************************************************************/

/** CREATES GROUPS  **/


void Verify_stun() 
{ 
   Dont_print_motors = false; 
  
  if (Stunned >= Stun_point)
  {  
      Stunned = 0;
  
      Serial.println("Azt hiszem beragadtam");  
      Serial.println("");    
    
      ALLBACKWARD(255);
      delay(1000);                                          

      Serial.println(""); 

      ALLLEFT(250);                                  
      delay(1400);                                            

      Serial.println(""); 
     
      ALLBRAKE(30);
      delay(100);
     
      Stunned = 0;    
   
      Serial.println("");       
  } 
}                 


void Walk()
{    
   Dont_print_motors = true;

   Random_action    = random(1,100);   
   Random_speed     = random(200,255); 
   Random_direction = random(1,4); 
 
   delay(5);

  if (Random_action<85 || Side_move>=1)
  {             
      ALLFORWARD(Random_speed-Fatigue); 
      delay(200);       
      
     if (millis() - Previous_millis > Waittime)
     { 
         Serial.print("Motor = 1;");                 
         Serial.print(" Parancs = 1;");              
         Serial.print(" Gyorsasag = ");            
         Serial.println(Random_speed-Fatigue);             
  
         Serial.print("Motor = 1;");                    
         Serial.print(" Parancs = 1;");              
         Serial.print(" Gyorsasag = ");             
         Serial.println(Random_speed-Fatigue);           
      }       
 
       Side_move --;        
       Stunned ++;  
      
       Side_distance = ultrasonic.Ranging(CM);             
      
     if (Random_direction == 1 && Side_move <= -4 && Side_distance<=20)
     {
         serpos(45);                                                                               
         delay(125); 
                
         Serial.println("Sokat mentem igy ,ezert kicsit jobbra fordulok!");           
         Serial.println("");                                                           
       
         ALLRIGHT(Random_speed-Fatigue);          
         delay(200);                     
      
         Head_rotate.write(90);             
         delay(125); 
     
         Side_move = 0; 
         Stunned --; 
     }     
     else if (Random_direction == 2 && Side_move <= -4 && Side_distance<=20)
     {
         serpos(135);                                                                             
         delay(125);    
                 
         Serial.println("Sokat mentem igy ,ezert kicsit balra fordulok!");            
         Serial.println("");                                                        
       
         ALLLEFT(Random_speed-Fatigue);            
         delay(200);                    
      
         Head_rotate.write(90);             
         delay(125);         
     
         Side_move = 0; 
         Stunned ++;  
     }        
  }   
  else if (Random_action>=85 && Random_action<94 && Side_move <= -1)
  {
      serpos(45);                           
      delay(125); 
              
      Serial.println("Szetnezek jobbra is!");            
      Serial.println("");                                
      
      ALLRIGHT(Random_speed-Fatigue); 
      delay(200);                   
      
      Head_rotate.write(90);                
      delay(125);   
 
      Side_move = 0;     
  }  
  else if (Random_action>=94 && Random_action<=100 && Side_move <= -1)
  {
      serpos(135);                          
      delay(125); 
              
      Serial.println("Szetnezek balra is!");          
      Serial.println("");                              
      
      ALLLEFT(Random_speed-Fatigue); 
      delay(200);                   
     
      Head_rotate.write(90);                
      delay(125); 
     
      Side_move = 0; 
  }
  Dont_print_motors = false;
}


char scan() 
{                                                                                                         
    int leftscanval,leftcentscanval,rightcentscanval,rightscanval,centerscanval;      

    char choice;                                         

stage1: 

  serpos(170);                                                                        
  delay(500);

  leftscanval = ultrasonic.Ranging(CM);     

  Serial.print("Balra levo legkozelebbi targy ");                     
  Serial.print(leftscanval);                                  
  Serial.println("cm -re");                                            
  Serial.println("");                                         
  //Moves its head to 170 degree (left) and saves the distance (in cm)
  //from the first object seen to its head in variable : leftscanval

stage2:   

  serpos(90);                                                     
  delay(500);

  centerscanval = ultrasonic.Ranging(CM);   

  Serial.print("Kozepen levo legkozelebbi targy ");             
  Serial.print(centerscanval);                                 
  Serial.println("cm -re");                                                     
  Serial.println("");                                         
  //Moves its head to 90 degree (front) and saves the distance (in cm)
  //from the first object seen to its head in variable : centerscanval 

stage3: 

  serpos(10); 
  delay(500);

  rightscanval = ultrasonic.Ranging(CM);    

  Serial.print("Jobbra levo legkozelebbi targy ");            
  Serial.print(rightscanval);                                 
  Serial.println("cm -re");                                                
  Serial.println("");                                     
 //Moves its head to 10 degree (nearly right) and saves the distance (in cm)
 //from the first object seen to its head in variable : rightscanval  
 
stage_combiner:

    Head_rotate.write(90);                                     
    delay(200);
  
    Serial.print("Servo vissza ");                              
    Serial.println("");                                                                   

  if (centerscanval>=20 && leftscanval>=10 && rightscanval>=10  )   
  {                                                                    
      Serial.println("Mozgo targy lehetett, mar nincs itt, elore megyek");                          
      Serial.println("");                                                                           
      choice = 'c';                                                
  }                                                          
  else if (leftscanval>=centerscanval && leftscanval>=rightscanval && leftscanval>=10 )              
  {                                                             
      Serial.println("Balra megyek");                                                               
      Serial.println("");                                                                           
      choice = 'l';                                                 
  }                        
  else  if (rightscanval>=centerscanval   &&  rightscanval>=leftscanval && rightscanval>=10 )         
  {                                                               
      Serial.println("Jobbra megyek");                                                              
      Serial.println("");                                                                          
      choice = 'r';                                                
  }  
  else    //Else choice= "s"
  {
      Serial.println("Hatra tolatok majd szetnezek");                                           
      Serial.println("");                                                                        
      choice = 's';
  }                                                                                                              
    
    return choice; 
    delay(30); 
}    

                    
void Detect()
{
     Stop_repeat = false;
 
    if (millis() > 250000 || millis() > 60000 )                                            
     {  
       Star_Wars_will_be = true;  
     }
  
    if (Front_distance == 0)
    {
      Stop_repeat = true;
    }
 
  while (Stop_repeat == false)
  {  
      char turndirection = scan();   //Decides where to turn   
      delay(50);
  
    switch (turndirection)  
    {                                                                                                                              
   case 'l':   //case l (left)    

       Stop_repeat = true;    Stunned = 0;

       ALLBACKWARD(255-Fatigue);  //All motors backward     
       delay(700);                                               

       Serial.println("");     

       ALLLEFT(250);  //All motors left (right motor forward , left motor backward)                                     
       delay(700);                                            

       Serial.println("");      
      
       ALLBRAKE(30);    //All motors brake 
       delay(100);
      
       Serial.println("");     
      
       break;  //ends the switch command                                                 

   case 'r':  //case r (right)     
  
       Stop_repeat = true;    Stunned = 0;                                                                                               

       ALLBACKWARD(255-Fatigue);                                
       delay(700);                                            

       Serial.println("");      

       ALLRIGHT(250);  //All motors right                                      
       delay(700);                                           

       Serial.println("");      

       ALLBRAKE(30);                                          
       delay(100);     
     
       Serial.println("");   
      
       break;                                                 

   case 'c':  //case cent (center)                                                                                                                                                                 
       
        if ( Stunned >= Stun_point )
        {
           Stop_repeat = true;        
           Stunned++;
       
           delay(50);     
           break;
        }
        else if (Star_Wars_will_be == true && Stunned < Stun_point)
        {   
           Stop_repeat = true;
         
           ALLBACKWARD(255-Fatigue);                                
           delay(1000);                                                                                                                

           Serial.println("");       

           ALLBRAKE(30);            
           delay(100);  
 
           Serial.println("");           
           delay(20);       
       
           Star_Wars_will_be = false;
      
           delay(50);     
           break;
        }
        else
        {  
           Stop_repeat = true;      
      
           delay(50);     
           break;
        }      

   case 's':  //case s (stop)                                                                                                                                                               
      
       Stunned = 0;

       ALLBACKWARD(255-Fatigue);                                
       delay(700);                                                                                                                

       Serial.println("");       

       ALLBRAKE(30);            
       delay(100);  
 
       Serial.println("");           
       delay(20);                                                                                                                                                                                                                                                                                
    }          
  }
  
   if (millis() > 60000  && Star_Wars_will_be == true || 
       millis() > 250000 && Star_Wars_will_be == true  )                                            
     {                       
        StarWars();   
        delay(15);  
     } 
    
 }    


void Keyboard_control()
{
  char Command = Serial.read();

  switch (Command)
  {
  case 'S':
    StarWars();  
 
  case 'R':
    ALLBRAKE(30);                                             
    delay(100); 
   
    asm volatile ("  jmp 0");   
    break; 
 
  case 'I':
  
    Stop_repeat = false;
    ALLBRAKE(30);  
   
     Serial.println("/********************************************************************************************************/");     
     Serial.println("/********                                                                   BY LORIXD                   */");       
     Serial.println("/********                                                                                               */");       
     Serial.println("/********                                       Parancsok:                                              */");       
     Serial.println("/********                                                                                               */");      
     Serial.println("/********      S = StarWars Elindul                              D = Senzor Erzekel                     */");       
     Serial.println("/********      R = Ujrainditas                                   1 = LED1 ki/be kapcsolasa              */");      
     Serial.println("/********      2 = LED2 ki/be kapcsolasa                                                                */");      
     Serial.println("/********                                                                                               */");      
     Serial.println("/********************************************************************************************************/");      
     Serial.println("Ird hogy 'E' majd nyomj Entert a kilepeshez..");                                                                    
                                                                                                             
    
    while(Stop_repeat == false)
    {   
      char Command2 = Serial.read();
    
     if(Command2 == 'E')
      {
        Serial.println("");        
        Stop_repeat = true;
      }
     else
      {          
        Serial.print("."); 
        delay(500);
      }
    }
   
   break;
  
 case 'D': 
    Serial.print("Targy ");            
    Serial.print(Front_distance);      
    Serial.println("cm -re");                                                            


    Fatigue++;  
     Serial.print("Faradtsag = ");     
     Serial.println(Fatigue);                        

    ALLBRAKE(30);                                            
    delay(100);                                                 

    Serial.println("");        
    beep(500,Second/2);                                             
    beep(300,Second/3);                                              
    Serial.println("");         
         
    Detect();      
    break; 

  case '1':   
    if (LED1State == LOW)  
    {  
      LED1State = HIGH;  
       Serial.println("LED1 = ON");       
    }
    else
    {
      LED1State = LOW;   
       Serial.println("LED1 = OFF");     
    }    
    digitalWrite(LED1, LED1State);        
    delay(15); 
   
    break;  
   
  case '2':   
    if (LED2State == LOW)
    {  
      LED2State = HIGH;     
       Serial.println("LED2 = ON");        
    }
    else
    {
     LED2State = LOW;      
      Serial.println("LED2 = OFF");       
    }    
   digitalWrite(LED2, LED2State);        
   delay(15); 
  
   break;   
  }
}

/******************************************************************************************************************************************************************************/
/******************************************************************************************************************************************************************************/

/** DEFINES COMMANDS  **/

void beep(register int note, register int duration)                                
{                                                                                       
  tone(SPEAKER, note, duration);                                                                                       
  //SPEAKER  Formula: beep(frequency,duration)
  
  Serial.print("Beep = ");          
  Serial.print(note);                                 
  Serial.print("hz ");                   
  Serial.print(duration);          
  Serial.print("ms");             
  
  if(LED_Blink % 2 == 0)                                                
  {                                                               
    Serial.println(" LED1-el");  
     digitalWrite(LED1, HIGH);                                   
     delay(duration);                                              
     digitalWrite(LED1, LOW);                                      
  }
  else                                                           
  {                                                              
    Serial.println(" LED2-vel");  
     digitalWrite(LED2, HIGH);                                     
     delay(duration);                                              
     digitalWrite(LED2, LOW);                                  
  }
  LED_Blink ++;      
}  
void serpos (register float pos)
{  
  Serial.print("Servo ");     
  Serial.print(pos);           
  Serial.println("-foknal");   
  
  if(pos == 90)
 {
  Head_rotate.write(pos-1);  
 }
 else
 {
  Head_rotate.write(pos);
 }  

}  

void motor(register int nMotor, register int command, register int speed)                   
{                                                                 
  int motorA, motorB;    

 if ( Dont_print_motors == true)
  {
  }
 else if (millis() - Previous_millis > 2000)
  {    
    Serial.print("Motor = ");       
    Serial.print(nMotor);           
    Serial.print(" Parancs = ");    
    Serial.print(command);          
    Serial.print(" Gyorsasag = ");  
    Serial.println(speed);             
  }    

  if (nMotor == 3 || 4)                           
  {                                                          
    switch (nMotor)                                               
    {                                                                                                                      
    case 3:                      //MOTOR                THE DEFINITION OF MOTOR COMMAND...
      motorA   = MOTOR3_A;       //MOTOR             
      motorB   = MOTOR3_B;       //MOTOR       Formula:
      break;                     //MOTOR          motor(motor pin, action, speed) 
    case 4:                      //MOTOR   motor:1(not_in_use) 2(not_in_use) 3(right) 4(left)      
      motorA   = MOTOR4_A;       //MOTOR   action: FORWARD BACKWARD BRAKE RELEASE       
      motorB   = MOTOR4_B;       //MOTOR             1        2      3      4
      break;                     //MOTOR   speed:0-255 -- if speed = 255 :1400ms are needed for the tyre for 1 turn...if 1 tyre is in use      
    default:                     //MOTOR         the robot goes ~90degree in 1400 ms 
      break;                                                                 
    }                            
    switch (command)                                             
    {                                                            
    case FORWARD:                                                
      motor_output (motorA, HIGH, speed);                         
      motor_output (motorB, LOW, -1);            
      break;                                                      
    case BACKWARD:                                                
      motor_output (motorA, LOW, speed);                          
      motor_output (motorB, HIGH, -1);          
      break;                                                      
    case BRAKE:                                                   
      motor_output (motorA, LOW, 255);     // 255: max speed         
      motor_output (motorB, LOW, -1);                
      break;                                                      
    case RELEASE:                                                 
      motor_output (motorA, LOW, 0);       // 0: output floating.     
      motor_output (motorB, LOW, -1);                 
      break;                                                      
    default:                                                      
      break;                                                      
    }                                                             
    }                                                               
    }                                                                 
void motor_output ( register int output, register int high_low, register int speed)  {        
                                                               
  int motorPWM;                                                   

  switch (output)                                                 
  {                                                                                                                                                        
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
void shiftWrite( register int output, register int high_low) {                                                                                    
  
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


void ALLFORWARD (register int sp)                              //MOTOR    ALLFORWARD command formula                                          
{                                                     //MOTOR
  motor(3, FORWARD , sp); // MOTOR 2 BACKWARD         //MOTOR            ALLFORWARD(sp)        -- ex. ALLFORWARD(255);
  motor(4, FORWARD , sp); // MOTOR 3 BACKWARD         //MOTOR        ALL MOTOR FORWARD(speed)
}                                                     //MOTOR --END
void ALLBACKWARD (register int sp)                             //MOTOR    ALLBACKWARD command formula 
{                                                     //MOTOR    
  motor(3, BACKWARD, sp); // MOTOR 2 BACKWARD         //MOTOR            ALLBACKWARD(sp)       -- ex. ALLBACKWARD(255);
  motor(4, BACKWARD, sp); // MOTOR 3 BACKWARD         //MOTOR        ALL MOTOR BACKWARD(speed)
}                                                     //MOTOR--END
void ALLRIGHT (register int sp)                                //MOTOR    ALLLEFT command formula  
{                                                     //MOTOR
  motor(3, BACKWARD, sp); // MOTOR 2 BACKWARD         //MOTOR            ALLLEFT(sp)           -- ex. ALLLEFT(255);          
  motor(4, FORWARD, sp); // MOTOR 3 BACKWARD          //MOTOR        THE ROBOT GOES RIGHT(speed) 
}                                                     //MOTOR--END
void ALLLEFT (register int sp)                                 //MOTOR    ALLRIGHT command formula 
{                                                     //MOTOR
  motor(3, FORWARD, sp); // MOTOR 2 BACKWARD          //MOTOR            ALLRIGHT(sp)          -- ex. ALLRIGHT(255);                                                            
  motor(4, BACKWARD , sp); // MOTOR 3 BACKWARD        //MOTOR       THE ROBOT GOES LEFT(speed)
}                                                     //MOTOR--END
void ALLBRAKE (register int sp)                                //MOTOR    ALLBRAKE command formula 
{                                                     //MOTOR
  motor(3,  BRAKE  , sp); // MOTOR 2 BACKWARD         //MOTOR            ALLBRAKE(sp)          -- ex. ALLBRAKE(255); 
  motor(4,  BRAKE  , sp); // MOTOR 3 BACKWARD         //MOTOR          STOP MOTORS(speed)
}                                                     //MOTOR--END

/******************************************************************************************************************************************************************************/
/******************************************************************************************************************************************************************************/

/** ANOTHER NEVER NEED TO BE EDITED VOIDS  **/

void StarWars ()                                                
{                                                                                                                                                                                                                                                                         
 Serial.println("StarWars Indul.."); 
 Serial.println("");                 
 Serial.println("");                  

                     Serial.println("");                           
                      ALLFORWARD(100);     Serial.println("");          
                       delay(100);     
  beep(a, 500);                                                
  beep(a, 500);                                                      
  beep(a, 500);      Serial.println("");                                                                              
                      ALLBACKWARD(250);     Serial.println("");          
                       delay(25);   
  beep(f, 350);      Serial.println("");                                                                          
                      ALLFORWARD(100);     Serial.println("");      
                       delay(100);
  beep(cH, 150);                                                     
  beep(a, 500);      Serial.println("");                                                                                
                      ALLBACKWARD(250);     Serial.println("");     
                       delay(25);
  beep(f, 350);      Serial.println("");                                                                    
                      ALLFORWARD(100);     Serial.println("");       
                       delay(100);
  beep(cH, 150);                                                  
  beep(a, 650);      Serial.println("");                                                                                                                                                                                 
                      ALLBRAKE(255);                                                    

  delay(500);                                               
                     Serial.println("");                          
                      ALLFORWARD(100);     Serial.println("");     
                       delay(100);
  beep(eH, 500);                                                 
  beep(eH, 500);                                                
  beep(eH, 500);     Serial.println("");                                                                             
                      ALLBACKWARD(250);     Serial.println("");      
                       delay(25);
  beep(fH, 350);     Serial.println("");                                                                               
                      ALLFORWARD(100);     Serial.println("");         
                       delay(100);
  beep(cH, 150);                                                 
  beep(gS, 500);     Serial.println("");                                                                               
                      ALLBACKWARD(250);     Serial.println("");       
                       delay(25);
  beep(f, 350);      Serial.println("");                                                                              
                      ALLFORWARD(100);     Serial.println("");      
                       delay(100);
  beep(cH, 150);                                                  
  beep(a, 650);      Serial.println("");                                                     
                      ALLBRAKE(255);                                                                     

  delay(500);                                                    
                     Serial.println("");                                  
                      motor(4, FORWARD , 250);     Serial.println("");       
                       delay(25);                                                              
  beep(aH, 500);     Serial.println("");                                                       
                      motor(4, BACKWARD , 100);     Serial.println("");   
                       delay(100);
  beep(a, 300);                                                   
  beep(a, 150);     Serial.println("");                                                           
                     ALLBRAKE(255);   Serial.println("");                 
                      motor(3, FORWARD , 250);     Serial.println("");       
                      delay(25);   
  beep(aH, 500);     Serial.println("");                                                                        
                      motor(3, BACKWARD , 100);      Serial.println("");   
                       delay(100);
  beep(gSH, 325);                                                     
  beep(gH, 175);    Serial.println("");                                   
                     ALLBRAKE(255);                                                  
                      ALLBACKWARD(250);     Serial.println("");           
                       delay(70);
  beep(fSH, 125);                                                 
  beep(fH, 125);                                                 
  beep(fSH, 250);    Serial.println("");                                                                        
                      ALLBRAKE(255);       

  delay(325);                                                   
                     Serial.println("");                                 
                      ALLFORWARD(100);     Serial.println("");           
                       delay(100);                                                                         
  beep(aS, 250);                                                  
  beep(dSH, 500);                                                 
  beep(dH, 325);     Serial.println("");                                                           
                      ALLBACKWARD(250);     Serial.println("");          
                       delay(70);
  beep(cSH, 175);                                            
  beep(cH, 125);
  beep(b, 125);                                                   
  beep(cH, 250);     Serial.println("");                                                 
                      ALLBRAKE(255);      

  delay(350);                                                     
                     Serial.println("");                                 
                      ALLFORWARD(100);     Serial.println("");         
                       delay(100);                                                       
  beep(f, 250);                                                   
  beep(gS, 500);    Serial.println("");                                  
                     ALLBRAKE(255);                                                         
                      motor(4, FORWARD , 250);     Serial.println("");        
                       delay(25); 
  beep(f, 350);      Serial.println("");                                                                        
                      motor(4, BACKWARD , 100);      Serial.println("");    
                       delay(100);
  beep(a, 125);                                                  
  beep(cH, 500);   Serial.println("");                                    
                    ALLBRAKE(255);             Serial.println("");      
                      motor(3, FORWARD , 250);      Serial.println("");  
                       delay(25); 
  beep(a, 375);      Serial.println("");                                                      
                      motor(3, BACKWARD , 100);     Serial.println("");      
                       delay(100);
  beep(cH, 125);                                                 
  beep(eH, 650);    Serial.println("");                                                              
                      ALLBRAKE(255);

  delay(500);                                                     
                     Serial.println("");                                
                      motor(3, FORWARD , 250);      Serial.println("");   
                       delay(25);                                                                                            
  beep(aH, 500);     Serial.println("");                                                 
                      motor(3, BACKWARD , 100);     Serial.println("");      
                       delay(100);
  beep(a, 300);                                                   
  beep(a, 150);    Serial.println("");                                              
                    ALLBRAKE(255);    
                      motor(4, FORWARD , 250);     Serial.println("");      
                       delay(25);   
  beep(aH, 500);     Serial.println("");                                                                        
                      motor(4, BACKWARD , 100);      Serial.println("");    
                       delay(100);
  beep(gSH, 325);                                                
  beep(gH, 175);     Serial.println("");                                                                   
                      ALLBACKWARD(250);     Serial.println("");           
                       delay(70);
  beep(fSH, 125);                                                
  beep(fH, 125);                                               
  beep(fSH, 250);   Serial.println("");                                      
                     ALLBRAKE(255);                                                          
  delay(325);                                               
                     Serial.println("");                                
                      ALLFORWARD(100);     Serial.println("");            
                       delay(100);                                                                         
  beep(aS, 250);                                                 
  beep(dSH, 500);                                              
  beep(dH, 325);     Serial.println("");                                                                
                      ALLBACKWARD(250);     Serial.println("");            
                       delay(70);
  beep(cSH, 175);                                                 
  beep(cH, 125);
  beep(b, 125);                                              
  beep(cH, 250);     Serial.println("");                                                           
                      ALLBRAKE(255);                                                      

  delay(350);                                                   
                     Serial.println("");                                  
                      ALLFORWARD(100);     Serial.println("");             
                       delay(100);                                                            
  beep(f, 250);                                                  
  beep(gS, 500);   Serial.println("");                                    
                    ALLBRAKE(255);                                                       
                      motor(4, FORWARD , 250);     Serial.println("");       
                       delay(25);
  beep(f, 375);      Serial.println("");                                                  
                      motor(4, BACKWARD , 100);      Serial.println("");   
                       delay(100);
  beep(cH, 125);                                          
  beep(a, 500);    Serial.println("");                                    
                     ALLBRAKE(255);                                                  
                       motor(3, FORWARD , 250);     Serial.println("");      
                        delay(25);  
  beep(f, 375);     Serial.println("");                                                   
                      motor(3, BACKWARD  , 100);     Serial.println("");   
                       delay(100);
  beep(cH, 125);                                                  
  beep(a, 500);      Serial.println("");                                                
                      ALLBRAKE(255);     Serial.println("");                                                                              

  delay(650);                                                     

 Serial.println("");                      
}  

/**************************************************************************************************************************/
/********                                                                   BY LORIXD                                     */
/********                                                                                                                 */
/********                                  Key Commands:                                                                  */
/********                                                                                                                 */
/********      S = StarWars starts                              D = Ultrasonic detects                                    */
/********      R = Restart program                              I = Show this information                                 */
/********      1 = LED1 on/off                                  2 = LED2 on/off                                           */
/********                                                                                                                 */
/********                                                                                                                 */

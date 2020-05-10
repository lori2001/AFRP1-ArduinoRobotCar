
#include "Ultrasonic.h"
#include "Arduino.h"
#include "Servo.h"

Servo Head_rotate;
Ultrasonic ultrasonic( 52, 53 );

#define VOICE 22
#define NECK 10

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
 #define MOTOR4_A 6 
 #define MOTOR4_B 0 

 #define FLAG_PWM 11
 #define MOTOR3_PWM 6 
 #define MOTOR4_PWM 5
 #define FLASH_PWM   3

 #define FORWARD 1
 #define BACKWARD 2
 #define BRAKE 3
 #define RELEASE 4


char AFRP1[16] = "AFRP1 Elindult!";
int LED[7] = {43, 42, 39, 38, 35, 34};

int distance_limit = 15, //Sets the limit of distance 
    distance, //Measures ultrasonic distance 
    distance_check; //Measures it second time to make sure the measurements are right 

int Second = 1000; //Creates a variable which has a second as value- makes delay easier
byte action; //Helps at randomizing the nezt walk-action
    
boolean noprinting = false; // If true nothing is printed 
byte forwardnr; //Numerotates the forward-s 

char turndirection; //Stores the direction choosen
boolean looping; //For looping the detection state

#include "Commands.h" //Commands.h-normally  || Silentmode.h-when working silently

char Scan();

void setup()
{
  Serial.begin(9600);   //1xSerial.println("");----means newline
                        //2xSerial.println("");----means 1 free line
                        //!!!commands (beep,serpos,motor) have newline implemented
                        
  /* for(int x=0;x<16;++x)
   { 
    Serial.print(AFRP1[x]);
    delay(125);
  }*/
 
   for(int x=0;x<6;x++)
   {
     pinMode(LED[x], OUTPUT);
   }
   
  Head_rotate.attach(NECK);
  
  Head_rotate.write(90);    //Servo at 90 degree
  delay(300);               //Delays (x) miliseconds (1000 ms = 1 sec)

  Serial.println("");
  beep(900,300);
  beep(1200,200);
  beep(900,300);
  beep(1200,500);
}

void loop()
 {
 distance = ultrasonic.Ranging(CM);
 distance_check = ultrasonic.Ranging(CM);    

 if (Serial.available())
 {
     Keyboard_control(); /** view colum 521 */ 
     delay(15);  //for safety
 }

 if//(distance > 0 && distance_check > 0 && (distance <= distance_limit || distance_check <= distance_limit) &&
   // distance - distance_check <= 2 && distance_check - distance <= 2) 
   (distance <= distance_limit && distance_check <= distance_limit)
  { 
   Serial.println(""); Serial.println("");
   Serial.print("------------OBJECT ");
   Serial.print(distance);
   Serial.print("-CM AWAY------------"); 

   brake(30);
   delay(100);
   
   Serial.println("");    
   beep(800,Second/3);
   beep(900,Second/4);
   
   forwardnr = 0;
   looping = true;
   
   while(looping)
  {
   turndirection = Scan();
   Serial.println("");
   Serial.print("-----------------------------------------");
  
   switch(turndirection) 
   {
    case 'c':
     Serial.println(""); Serial.println("");
     Serial.print("|----------CONTINUE-----------|");
     
     looping = false;
    break;
   
    case 'r':
     Serial.println(""); Serial.println("");
     Serial.print("------------------RIGHT------------------");
   
     backward(255);
     delay(700);

     Serial.println("");
     right(255);
     delay(1500);

     noprinting=true;
     brake(30);
     delay(100);
     noprinting=false;

     Serial.println("");
     Serial.print("-----------------------------------------");

     looping = false;
    break;
   
    case 'l':
     Serial.println(""); Serial.println("");
     Serial.print("------------------LEFT-------------------");
   
     backward(255);
     delay(700);

     Serial.println("");
     left(255);
     delay(1500);

     noprinting=true;
     brake(30);
     delay(100);
     noprinting=false;

     Serial.println("");
     Serial.print("------------------------------------------");
     
     looping = false;
    break;
   
    case 'b':
     Serial.println(""); Serial.println("");
     Serial.print("------------------BACK-------------------");
   
     backward(255);
     delay(700);

     left(255);
     delay(1300);

     noprinting=true;
     brake(30);
     delay(100);
     noprinting=false;

    break;
   }
  }
 }
 else 
 { 
  action = random(1,101);  
  
  if (action>0 && action<15 && forwardnr>3)
  {
   forwardnr = 0;
    
   Serial.println(""); Serial.println("");
   Serial.print("--RIGHT SIDEMOVE(");
   Serial.print(action);
   Serial.print(")--------------------");

   serpos(45,125);

   right(255);
   delay(175);

   serpos(90,125);
   
   Serial.println("");
   Serial.print("---------------------------------------");
  }
  else if (action>15 && action<=30 && forwardnr>3)
  {
   forwardnr = 0;
    
   Serial.println(""); Serial.println("");
   Serial.print("--LEFT SIDEMOVE(");
   Serial.print(action);
   Serial.print(")--------------------");

   serpos(135,125);

   left(255);
   delay(175);

   serpos(90,125);
   
   Serial.println("");
   Serial.print("---------------------------------------");
  }
  else if(action>30) 
  {      
   if(forwardnr > 0)
   {noprinting = true;}

   if(!noprinting)
   {Serial.println(""); Serial.println("");
    Serial.print("----------------FORWARD----------------");}  
    
   forward(255);
   delay(500); 

   forwardnr++;

   if(forwardnr == 1){Serial.println("");}
   Serial.print("-");
   Serial.print(distance);
   Serial.print("-"); 
   Serial.print(" ");
   
   noprinting = false;
  }  
 } 
}
char Scan()
{
 int leftscanval,leftcentscanval,rightcentscanval,rightscanval,centerscanval;
 char choice;
 boolean action = random(0,2);  

 Serial.println("");

 if(!action)
 {
  serpos(10,500);
  rightscanval = ultrasonic.Ranging(CM);
  delay(50);

  Serial.println("");
  Serial.print("Right distance=");
  Serial.print(rightscanval); 
  
  serpos(90,500);
  centerscanval = ultrasonic.Ranging(CM);
  delay(50);

  Serial.println("");
  Serial.print("Center distance=");  
  Serial.print(centerscanval);

  serpos(170,500);
  leftscanval = ultrasonic.Ranging(CM);
  delay(50); 

  Serial.println("");
  Serial.print("Left distance=");
  Serial.print(leftscanval);
 }
 else
 {
  serpos(170,500);
  leftscanval = ultrasonic.Ranging(CM);
  delay(50); 

  Serial.println("");
  Serial.print("Left distance=");
  Serial.print(leftscanval);
  
  serpos(90,500);
  centerscanval = ultrasonic.Ranging(CM);
  delay(50);

  Serial.println("");
  Serial.print("Center distance=");  
  Serial.print(centerscanval);

  serpos(10,500);
  rightscanval = ultrasonic.Ranging(CM);
  delay(50);

  Serial.println("");
  Serial.print("Right distance=");
  Serial.print(rightscanval);
 }

 noprinting = true;
 serpos(90,200);
 noprinting = false;

 if(centerscanval > distance_limit+5 && turndirection != 'b')
 {
  choice = 'c';
 }
 else if((rightscanval>leftscanval && rightscanval>distance_limit) || (rightscanval==leftscanval && action==1))
 {
  choice = 'r';
 }
 else if((leftscanval>rightscanval && leftscanval>distance_limit) || (leftscanval==rightscanval && action==0))
 {
  choice = 'l';
 }
 else 
 {
  choice = 'b';
 }

 return choice;
}
void Keyboard_control()
{
  char Command = Serial.read();
  boolean Stop_repeat = true;
  
  switch (Command)
  {
  case 'S':
    Serial.println(""); 
    StarWars();  
    Serial.println(""); 

  case 'R':
    noprinting = true;
    brake(30);                                             
    delay(100);
    noprinting = false;
    
    Serial.println(""); 
    Serial.println(""); 
    Serial.println(""); 
    
    asm volatile ("  jmp 0");   
    break; 
 
  case 'I':
  
    Stop_repeat = false;
    brake(30);  
   
     Serial.println("/********************************************************************************************************/");     
     Serial.println("/********                                                                   BY LORIXD                   */");       
     Serial.println("/********                                                                                               */");       
     Serial.println("/********                                       Parancsok:                                              */");       
     Serial.println("/********                                                                                               */");      
     Serial.println("/********      S = StarWars Elindul                              R = Ujrainditas                        */");           
     Serial.println("/********                                                                                               */");      
     Serial.println("/********************************************************************************************************/");      
     Serial.print("Ird hogy 'E' majd nyomj Entert a kilepeshez..");                                                                    
                                                                                                             
    
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
        delay(1000);
      }
    }
   
   break;
  }
}

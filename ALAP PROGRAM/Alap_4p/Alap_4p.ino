#include "Ultrasonic.h"                                           //SZENZOR--Felolvassa az Ultrasonic.h
#include "Arduino.h"                                              //SZENZOR--Felolvassa az Arduino.h
#include <Servo.h>                                                //SZERVO --Felolvassa a  Servo.h

#define MOTORLATCH 12                                             //MOTOR  --meghatarozza MOTORLATCH
#define MOTORCLK 4                                                //MOTOR  --meghatarozza MOTORCLK 4 
#define MOTORENABLE 7                                             //MOTOR  --meghatarozza MOTORENABLE 7  
#define MOTORDATA 8                                               //MOTOR  --meghatarozza MOTORDATA 8
#define MOTOR1_A 2                                                //MOTOR  --meghatarozza MOTOR1_A 2
#define MOTOR1_B 3                                                //MOTOR  --meghatarozza MOTOR1_B 3 
#define MOTOR2_A 1                                                //MOTOR  --meghatarozza MOTOR2_A 1 
#define MOTOR2_B 4                                                //MOTOR  --meghatarozza MOTOR2_B 4  
#define MOTOR3_A 5                                                //MOTOR  --meghatarozza MOTOR3_A 5 
#define MOTOR3_B 7                                                //MOTOR  --meghatarozza MOTOR3_B 7
#define MOTOR4_A 0                                                //MOTOR  --meghatarozza MOTOR4_A 0
#define MOTOR4_B 6                                                //MOTOR  --meghatarozza MOTOR4_B 6 
#define MOTOR1_PWM 11                                             //MOTOR  --meghatarozza MOTOR1_PWM 11
#define MOTOR2_PWM 3                                              //MOTOR  --meghatarozza MOTOR2_PWM 3 
#define MOTOR3_PWM 6                                              //MOTOR  --meghatarozza MOTOR3_PWM 6
#define MOTOR4_PWM 5                                              //MOTOR  --meghatarozza MOTOR4_PWM 5 
#define SERVO1_PWM 10                                             //SZERVO --meghatarozza SERVO1_PWM 10                                             
#define SERVO2_PWM 9                                              //SZERVO --meghatarozza SERVO2_PWM 9 
#define FORWARD 1                                                 //MOTOR  --meghatarozza FORWARD 1
#define BACKWARD 2                                                //MOTOR  --meghatarozza BACKWARD 2
#define BRAKE 3                                                   //MOTOR  --meghatarozza BRAKE 3
#define RELEASE 4                                                 //MOTOR  --meghatarozza RELEASE 4    

Servo headRotate;                                                 //SZPEAKER ---a szervo hatarozoja                                                        
Ultrasonic ultrasonic( 48, 49 );                                  //SZENZOR  --megadja a szenzor labait
long previousMillis = 0;                                          //DELAY-- segit majd a varas nelkuli idoziteshez                              
int cm;                                                           //SZPEAKER --meghatarozza a cm valtozot                             
int SPEAKER = 51;                                                 //SZPEAKER --megadja a szpeaker labait
int servo = 10;                                                   //SZPEAKER --meghatarozza a servo valtozot servo=0
int sec=1310;                                                     //SZPEAKER --meghatarozza a sec valtozot sec=1310
int c = 261;                                                      //SZPEAKER --meghatarozza a c valtozot
int d = 294;                                                      //SZPEAKER --meghatarozza a d valtozot
int e = 329;                                                      //SZPEAKER --meghatarozza a e valtozot
int f = 349;                                                      //SZPEAKER --meghatarozza a f valtozot
int g = 391;                                                      //SZPEAKER --meghatarozza a g valtozot
int gS = 415;                                                     //SZPEAKER --meghatarozza a gS valtozot
int a = 440;                                                      //SZPEAKER --meghatarozza a a valtozot
int aS = 455;                                                     //SZPEAKER --meghatarozza a aS valtozot
int b = 466;                                                      //SZPEAKER --meghatarozza a b valtozot
int cH = 523;                                                     //SZPEAKER --meghatarozza a cH valtozot
int cSH = 554;                                                    //SZPEAKER --meghatarozza a cSH valtozot
int dH = 587;                                                     //SZPEAKER --meghatarozza a dH valtozot
int dSH = 622;                                                    //SZPEAKER --meghatarozza a dSH valtozot
int eH = 659;                                                     //SZPEAKER --meghatarozza a eH valtozot
int fH = 698;                                                     //SZPEAKER --meghatarozza a fH valtozot
int fSH = 740;                                                    //SZPEAKER --meghatarozza a fSH valtozot
int gH = 784;                                                     //SZPEAKER --meghatarozza a gH valtozot
int gSH = 830;                                                    //SZPEAKER --meghatarozza a gSH valtozot
int aH = 880;                                                     //SZPEAKER --meghatarozza a aH valtozot
int DO = 261;                                                     //SZPEAKER --meghatarozza a DO valtozot
int RE = 294;                                                     //SZPEAKER --meghatarozza a RE valtozot
int MI = 329;                                                     //SZPEAKER --meghatarozza a MI valtozot
int FA = 349;                                                     //SZPEAKER --meghatarozza a FA valtozot
int SO = 391;                                                     //SZPEAKER --meghatarozza a SO valtozot
int La = 440;                                                     //SZPEAKER --meghatarozza a La valtozot
int SI = 466;                                                     //SZPEAKER --meghatarozza a SI valtozot
int LED1 = 13;                                                    //LED1 --meghatarozza a LED1 labat
int LED2 = 13;                                                    //LED2 --meghatarozza a LED2 labat
int VAR = 0;                                                      //LED1,2-- meghatarozza a  VAR valtozot ami majd segit a ritmushoz
int VARI = 0;
int Talalkozas = 0;                                               //SZPEAKER --meghatarozza a Talalkozas valtozot ami majd segit az idonkenti enekleshez      
int Faradtsag = 0;                                                //DELAY-- segit majd a faradtsag szimulalasahoz
int waittime = 3000;                                              //segit majd szinkronizalni a faradtsagot
int LED1State = LOW;                                              //segit majd a ledek ki es be gyujtasahoz
int LED2State = LOW;                                              //segit majd a ledek ki es be gyujtasahoz

/******************************************************************************************************************************************************************************/
/******************************************************************************************************************************************************************************/

void setup()    //Elkezdi azt a reszet a programnak amit csak a program elejen csinal meg                                                                 
{                               
  Serial.begin(9600);                                                            
  Serial.println("AFRP1 Elindult!");
  Serial.println("");                         

  pinMode(LED1, OUTPUT);   //LED1  output ba rakja  
  Serial.print("LED1 = "); 
  Serial.println(LED1);                            

  pinMode(LED2, OUTPUT);   //LED2 output ba rakja  
  Serial.print("LED2 = "); 
  Serial.println(LED2);                 

  pinMode(SPEAKER,OUTPUT);   //SZPEAKER output ba rakja
  Serial.print("Speaker = "); 
  Serial.println(SPEAKER);                                       

  headRotate.attach(servo);  //SZERVO elinditsa
  Serial.print("Servo = "); 
  Serial.println(servo);
  Serial.println("");    
  

  serpos(90);         //servo 90 foknal                           
  delay(100);         //(1000 ms =1sec)   

  Serial.println("");  
  beep(900,300);    
  beep(1200,200);                                                 
  beep(900,300);    
  beep(1200,500);                                                    
  Serial.println("");  
  
}

void loop()
{
  int timing;                                                     
  cm = ultrasonic.Ranging(CM);    //SZENZOR -- megadja a cm fogalmat --

  VARI = 0;

  delay(50);                                                          
  ALLFORWARD(255-Faradtsag);     //MOTOR Elinditsa mindket motort elore


  if (millis() - previousMillis > waittime)
  {
    previousMillis = millis();

    Faradtsag++;    
    Serial.println("");    
    Serial.print("Faradtsag = ");
    Serial.println(Faradtsag); 
    Serial.println("");        
  }


  if (cm<=7)   //SZENZOR-- magyarul== Ha a szenzor <=10cm re van valamitol akkor ((:))                                                

  { 

    Serial.print("Targy ");
    Serial.print(cm); 
    Serial.println("cm -re");                                                   
    Serial.println("");  

    Faradtsag++;  
    Serial.print("Faradtsag = ");
    Serial.println(Faradtsag); 

    Talalkozas++; 
    Serial.print("Talalkozas = ");
    Serial.println(Talalkozas); 

    ALLBRAKE(30);   //MOTOR feket huz mindket motoron                                             
    delay(20);                                                 

    
    Serial.println("");  
    beep(500,sec/2);                                             
    beep(300,sec/3);                                              
    Serial.println("");  
  
    detect();

  }                                                                                                                                                                                                             

  if (Talalkozas == 10)                                             
  {                
    Serial.print("Talalkozas = ");
    Serial.println(Talalkozas);                                             

    Serial.println("StarWars Indul..");
    Serial.println("");    
    Serial.println("");    
    StarWars();     
    Serial.println("");    
    

    Talalkozas=0;   
    Serial.print("Talalkozas = ");
    Serial.println(Talalkozas);                                                                
  }    


  if (Serial.available())
  {
    char parancs = Serial.read();

    switch (parancs)
    {
    case 'S':
      StarWars();  //starwarst elinditja
      Serial.println("StarWars Indul..");

    case 'R':
      delay(1000);
      asm volatile ("  jmp 0");   //programot ujrainditsa 
      break; 

    case 'D': 
      Serial.print("Targy ");
      Serial.print(cm); 
      Serial.println("cm -re");                                                   


      Faradtsag++;  
      Serial.print("Faradtsag = ");
      Serial.println(Faradtsag); 

      Talalkozas++; 
      Serial.print("Talalkozas = ");
      Serial.println(Talalkozas); 


      ALLBRAKE(30);   //MOTOR feket huz mindket motoron                                             
      delay(20);                                                 

      Serial.println("");  
      beep(500,sec/2);                                             
      beep(300,sec/3);                                              
      Serial.println("");  
      
      detect(); 
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
      break;   
    }
  }
}
/*DON'T CHANGE*************DON'T CHANGE********!!!ALUL CSAK AKKOR VALTOZTASS HA KIMONDOTTAN TUDOD HOGY MIT CSINALSZ!!!********DON'T CHANGE************DON'T CHANGE**************/
/*DON'T CHANGE*************DON'T CHANGE********************!!!CHANGE ONLY IF U REALLY KNOW WHAT YOU R DOING!!!****************DON'T CHANGE************DON'T CHANGE**************/

void beep(int note, int duration)                                
{                                                                                    
  tone(SPEAKER, note, duration);            //SPEAKER  beep parancs meghatarozasa:                                                                           
  //SPEAKER  keplet: beep(fregvencia,idotartam)
   
  Serial.print("Beep = ");   
  Serial.print(note);                   
  Serial.print("hz ");       
  Serial.print(duration);
  Serial.print("ms");
  
  if(VAR % 2 == 0)                                                
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
  VAR++;                                                        
}  

void StarWars ()                                                
{                                                                                                                                                                                                               
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
  beep(a, 650);                                                 
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
                     ALLBRAKE(255);     Serial.println("");                                                                   

  delay(500);                                                    
                     Serial.println("");  
                     motor(2, FORWARD , 250);     Serial.println("");    
                     delay(25);                                                              
  beep(aH, 500);     Serial.println("");                                                   
                     motor(2, BACKWARD , 100);     Serial.println("");  
                     delay(100);
  beep(a, 300);                                                   
  beep(a, 150);      Serial.println("");                                                     
                     ALLBRAKE(255); 
                     motor(3, FORWARD , 250);     Serial.println("");   
                     delay(25);   
  beep(aH, 500);     Serial.println("");                                                    
                     motor(3, BACKWARD , 100);      Serial.println("");  
                     delay(100);
  beep(gSH, 325);                                                 
  beep(gH, 175);     Serial.println("");                                               
                     ALLBACKWARD(250);     Serial.println("");  
                     delay(70);
  beep(fSH, 125);                                                 
  beep(fH, 125);                                                 
  beep(fSH, 250);    Serial.println("");                                                
                     ALLBRAKE(255);     Serial.println("");   

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
                     ALLBRAKE(255);      Serial.println("");  

  delay(350);                                                     
                     Serial.println("");  
                     ALLFORWARD(100);     Serial.println("");  
                     delay(100);                                                       
  beep(f, 250);                                                   
  beep(gS, 500);     Serial.println("");                                                  
                     motor(2, FORWARD , 250);     Serial.println("");    
                     delay(25); 
  beep(f, 350);      Serial.println("");                                                   
                     motor(2, BACKWARD , 100);      Serial.println("");  
                     delay(100);
  beep(a, 125);                                                  
  beep(cH, 500);                                                
  ALLBRAKE(255);     Serial.println("");  
                     motor(3, FORWARD , 250);      Serial.println("");  
                     delay(25);
  beep(a, 375);      Serial.println("");                                                  
                     motor(3, BACKWARD , 100);     Serial.println("");   
                     delay(100);
  beep(cH, 125);                                                 
  beep(eH, 650);                                                 
  ALLBRAKE(255);

  delay(500);                                                     
                     Serial.println("");  
                     motor(2, FORWARD , 250);      Serial.println("");   
                     delay(25);                                                                                            
  beep(aH, 500);     Serial.println("");                                              
                     motor(2, BACKWARD , 100);     Serial.println("");   
                     delay(100);
  beep(a, 300);                                                   
  beep(a, 150);                                            
  ALLBRAKE(255);     Serial.println("");    
                     motor(3, FORWARD , 250);     Serial.println("");   
                     delay(25);   
  beep(aH, 500);     Serial.println("");                                            
                     motor(3, BACKWARD , 100);      Serial.println("");  
                     delay(100);
  beep(gSH, 325);                                                
  beep(gH, 175);     Serial.println("");                                                 
                     ALLBACKWARD(250);     Serial.println("");  
                     delay(70);
  beep(fSH, 125);                                                
  beep(fH, 125);                                               
  beep(fSH, 250);                                         
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
                     ALLBRAKE(255);       Serial.println("");                                                  

  delay(350);                                                   
                     Serial.println("");  
                     ALLFORWARD(100);     Serial.println("");  
                     delay(100);                                                            
  beep(f, 250);                                                    
  beep(gS, 500);     Serial.println("");                                                   
                     motor(2, FORWARD , 250);     Serial.println("");    
                     delay(25);
  beep(f, 375);      Serial.println("");                                                    
                     motor(2, BACKWARD , 100);      Serial.println("");  
                     delay(100);
  beep(cH, 125);                                              
  beep(a, 500);      Serial.println("");                                                    
                     motor(3, FORWARD , 250);     Serial.println("");   
                     delay(25);  
  beep(f, 375);      Serial.println("");                                                     
                     motor(3, BACKWARD  , 100);     Serial.println("");   
                     delay(100);
  beep(cH, 125);                                                  
  beep(a, 500);      Serial.println("");                                                
                     ALLBRAKE(255);     Serial.println("");                                                                    

  delay(650);                                                     
}  


void serpos (float pos)
{  
  headRotate.write(pos);   //SZERVO --a pos ertekenek megfelelo pozicioba megy a servo 

  Serial.print("Servo ");
  Serial.print(pos);
  Serial.println("-foknal");                                   
}

char scan()                                          
{                                                               
  int leftscanval,leftcentscanval,rightcentscanval,rightscanval,centerscanval;      

  char choice;                                         

stage1: 

  serpos(180);                                                 
  delay(500);

  leftscanval = ultrasonic.Ranging(CM);     

  Serial.print("Balra levo legkozelebbi targy ");         
  Serial.print(leftscanval);
  Serial.println("cm -re");           
  Serial.println("");  
  //SZERVO ebbe a pozicioba megnezi hany cm re van a hozza 
  //legkozelebben allo targy es lementi a leftscanval valtozoba

stage2:  

  serpos(135);                                                                                    
  delay(500);

  leftcentscanval = ultrasonic.Ranging(CM);    

  Serial.print("B-K  ra levo legkozelebbi targy ");
  Serial.print(leftcentscanval);
  Serial.println("cm -re");                          
  Serial.println("");  
  //SZERVO ebbe a pozicioba megnezi hany cm re van a hozza 
  //legkozelebben allo targy es lementi a leftcentscanval valtozoba     

stage3:   

  serpos(90);                                                     
  delay(500);

  centerscanval = ultrasonic.Ranging(CM);   

  Serial.print("Kozepen levo legkozelebbi targy ");
  Serial.print(centerscanval);
  Serial.println("cm -re");                      
  Serial.println("");  
  //SZERVO ebbe a pozicioba megnezi hany cm re van a hozza 
  //legkozelebben allo targy es lementi a centerscanval valtozoba  

stage4:

  serpos(45); 
  delay(500);    

  rightcentscanval = ultrasonic.Ranging(CM);   

  Serial.print("J-K  ra levo legkozelebbi targy ");
  Serial.print(rightcentscanval);
  Serial.println("cm -re");                      
  Serial.println("");    
  //SZERVO ebbe a pozicioba megnezi hany cm re van a hozza 
  //legkozelebben allo targy es lementi a rightcentscanval valtozoba  

stage5: 

  serpos(10); 
  delay(500);

  rightscanval = ultrasonic.Ranging(CM);    

  Serial.print("Jobbra levo legkozelebbi targy ");
  Serial.print(rightscanval);
  Serial.println("cm -re");                      
  Serial.println("");    
  //SZERVO ebbe a pozicioba megnezi hany cm re van a hozza 
  //legkozelebben allo targy es lementi a rightscanval valtozoba 


  headRotate.write(90);   //SZERVO --a pos ertekenek megfelelo pozicioba megy a servo 
  Serial.print("Servo vissza ");
  Serial.println("");                            



  if (centerscanval>7) 
  {                                                               
    Serial.println("Mozgo targy lehetett, mar nincs itt, elore megyek");
    Serial.println("");  
    choice = 'cent';                                                
  }                                                          
  else if (leftcentscanval>=rightcentscanval && leftcentscanval>=centerscanval    //SZERVO ha ... akkor a choice="lc"  
  && leftcentscanval>=rightscanval  && leftcentscanval>=30 
    && leftscanval>=30)        
  {                                                               
    Serial.println("B-K ra megyek");
    Serial.println("");
    choice = 'lc';                                                
  }                                                               
  else  if (rightcentscanval>=leftscanval && rightcentscanval>=leftcentscanval     //SZERVO ha ... akkor a choice="rc"
  && rightcentscanval>=centerscanval  && rightcentscanval>=30
    && rightscanval>=30)          
  {                                                               
    Serial.println("J-K ra megyek");
    Serial.println("");
    choice = 'rc';                                                
  } 
  else if (leftscanval>=centerscanval && leftscanval>=rightscanval     //SZERVO ha ... akkor a choice="l"        
  && leftscanval>=10                                        )           
  {                                                             
    Serial.println("Balra megyek");
    Serial.println("");
    choice = 'l';                                                 
  }                        
  else  if (rightscanval>=centerscanval   &&  rightscanval>=leftscanval  //SZERVO ha ... akkor a choice="r"
  && rightscanval>=10                                        ) 
  {                                                               
    Serial.println("Jobbra megyek");
    Serial.println("");
    choice = 'r';                                                
  }  
  else    {
    Serial.println("Hatra tolatok majd szetnezek");   //Maskepp choice= "s"
    Serial.println("");
    choice = 's';
  }                                                                                                              
  return choice;    //SZERVO visszamegy a choice hoz ( valami ilyesmi )                                              
}

void motor(int nMotor, int command, int speed)                   
{                                                                 
  int motorA, motorB;    

  if (millis() - previousMillis > waittime)
  {
    Serial.print("Motor = ");
    Serial.print(nMotor);
    Serial.print(" Parancs = ");
    Serial.print(command);
    Serial.print("  Gyorsasag = ");
    Serial.println(speed);     
  }    

  if (nMotor >= 1 && nMotor <= 4)                               
  {                                                          
    switch (nMotor)                                               
    {                                                              
    case 1:                                                     
      motorA   = MOTOR1_A;       //MOTOR                A MOTOR PARANCSOK MEGHATAROZASA....
      motorB   = MOTOR1_B;       //MOTOR             
      break;                     //MOTOR       Keplet:
    case 2:                      //MOTOR          motor(hanyas, merre, sebesseg) 
      motorA   = MOTOR2_A;       //MOTOR   hanyas:1(nincs) 2(jobb) 3(bal) 4(nincs      
      motorB   = MOTOR2_B;       //MOTOR   merre: FORWARD BACKWARD BRAKE RELEASE       
      break;                     //MOTOR             |        |      |      |
    case 3:                      //MOTOR           ELORE    HATRA   FEK  ELINDIT
      motorA   = MOTOR3_A;       //MOTOR   sebesseg:0-255 -- 255 es sebesseggel 1400ms alatt a kerek 1 et fordul... ha csak 1 kerek forog akkor a robotom ~90fok al fordul
      motorB   = MOTOR3_B;       //MOTOR pl.
      break;                     //MOTOR   motor(2, FORWARD, 255)
    case 4:                      //MOTOR   motor(2, BACKWARD, 255)
      motorA   = MOTOR4_A;       //MOTOR   motor(2, BRAKE, 30)
      motorB   = MOTOR4_B;       //MOTOR   motor(2, RELEASE, 0)
      break;                     //MOTOR   motor(3, FORWARD, 255)
    default:                     //MOTOR   motor(3, BACKWARD, 255)
      break;                     //MOTOR   motor(3, BRAKE, 30)
    }                              //MOTOR   motor(3, RELEASE, 0)

    switch (command)                                             
    {                                                            
    case FORWARD:                                                
      motor_output (motorA, HIGH, speed);                         
      motor_output (motorB, LOW, -1);      // -1: a PWM nem megy       
      break;                                                      
    case BACKWARD:                                                
      motor_output (motorA, LOW, speed);                          
      motor_output (motorB, HIGH, -1);     // -1: a PWM nem megy         
      break;                                                      
    case BRAKE:                                                   
      motor_output (motorA, LOW, 255);     // 255: maximum sebesseg          
      motor_output (motorB, LOW, -1);      // -1: a PWM nem megy            
      break;                                                      
    case RELEASE:                                                 
      motor_output (motorA, LOW, 0);       // 0: output floating.--nem toom      
      motor_output (motorB, LOW, -1);      // -1: a PWM nem megy             
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

void ALLFORWARD (int sp)                              //MOTOR    ALLFORWARD parancs meghatarozasa                                          
{                                                     //MOTOR
  motor(2, FORWARD , sp); // MOTOR 2 BACKWARD         //MOTOR             ALLFORWARD(sp)        -- pl. ALLFORWARD(255);
  motor(3, FORWARD , sp); // MOTOR 3 BACKWARD         //MOTOR    MINDKET MOTOR ELORE(gyorsasag)
}                                                     //MOTOR --BEF
void ALLBACKWARD (int sp)                             //MOTOR    ALLBACKWARD parancs meghatarozasa 
{                                                     //MOTOR    
  motor(2, BACKWARD, sp); // MOTOR 2 BACKWARD         //MOTOR             ALLBACKWARD(sp)       -- pl. ALLBACKWARD(255);
  motor(3, BACKWARD, sp); // MOTOR 3 BACKWARD         //MOTOR    MINDKET MOTOR HATRA(gyorsasag)
}                                                     //MOTOR--BEF
void ALLLEFT (int sp)                                 //MOTOR    ALLLEFT parancs meghatarozasa 
{                                                     //MOTOR
  motor(2, FORWARD , sp); // MOTOR 2 BACKWARD         //MOTOR                  ALLLEFT(sp)      -- pl. ALLLEFT(255);          
  motor(3, BACKWARD, sp); // MOTOR 3 BACKWARD         //MOTOR     A ROBOT BALRA FORDUL(gyorsasag) 
}                                                     //MOTOR--BEF
void ALLRIGHT (int sp)                                //MOTOR    ALLRIGHT parancs meghatarozasa
{                                                     //MOTOR
  motor(2, BACKWARD, sp); // MOTOR 2 BACKWARD         //MOTOR                 ALLRIGHT(sp)      -- pl. ALLRIGHT(255);                                                            
  motor(3, FORWARD , sp); // MOTOR 3 BACKWARD         //MOTOR    A ROBOT JOBBRA FORDUL(gyorsasag)
}                                                     //MOTOR--BEF
void ALLBRAKE (int sp)                                //MOTOR    ALLBRAKE parancs meghatarozasa
{                                                     //MOTOR
  motor(2,  BRAKE  , sp); // MOTOR 2 BACKWARD         //MOTOR              ALLBRAKE(sp)         -- pl. ALLBRAKE(255); 
  motor(3,  BRAKE  , sp); // MOTOR 3 BACKWARD         //MOTOR    A MOTROK MEGALLNAK(gyorsasag)
}                                                     //MOTOR--BEF

void detect()
{

  while (VARI == 0)
  {   
    char turndirection = scan();   //Eldonti hogy merre forduljon.                               
    switch (turndirection)                                       
    {                                                                    

    case 'l':   //l(left) esetben ((:))    

      VARI++;    

      ALLBACKWARD(255-Faradtsag);  //MOTOR Mindket motor hatra                               
      delay(700);                                               

      Serial.println(""); 

      ALLLEFT(250);  //MOTOR Mindket motor balra                                    
      delay(700);                                            

      Serial.println(""); 

      ALLBRAKE(30);    //MOTOR Mindket Fek  
     
      Serial.println(""); 
      
      break;  //ujrakezdi a loop parancsot                                                

    case 'lc':

      VARI++;

      ALLBACKWARD(255-Faradtsag);  //MOTOR Mindket motor hatra                               
      delay(500); 
 
      Serial.println(""); 

      motor(2, FORWARD , 255);  //MOTOR 2 elore
      delay(800); 

      Serial.println(""); 
     
      ALLBRAKE(30);                                              
     
      Serial.println(""); 
     
      break;   

    case 'r':  //r(right) esetben ((:))     

      VARI++;                                                                                                   

      ALLBACKWARD(255-Faradtsag);                                
      delay(700);                                            

      Serial.println(""); 

      ALLRIGHT(250);  //Mindket motor jobbra                                       
      delay(700);                                           

      Serial.println(""); 

      ALLBRAKE(30);                                          
     
      Serial.println(""); 
     
      break;                                                 

    case 'rc ':

      VARI++;

      ALLBACKWARD(255-Faradtsag);  //MOTOR Mindket motor hatra                            
      delay(500); 

      Serial.println(""); 

      motor(3, FORWARD , 255);  //MOTOR 2 elore
      delay(800); 

      Serial.println(""); 

      ALLBRAKE(30);                                              

      Serial.println("");      
     
      break;  

    case 'cent':  //c(center) esetben ((:))                                                                                                                                                                 

      VARI++;        

      ALLFORWARD(255-Faradtsag);      
      delay(100); 
      
      Serial.println(""); 

      ALLBRAKE(30);                                              
   
      Serial.println("");   
   
      break;       

    case 's':  //s(stop) esetben ((:))                                                                                                                                                                 

      ALLBACKWARD(200-Faradtsag);                                
      delay(700);                                                                                                                

      Serial.println(""); 

      ALLBRAKE(30);            
 
       Serial.println(""); 
 
      delay(20);                                                                                                                                                                                                                                                                            
    }       
  }
}
/**************************************************************************************************************************/
/********                                                                   BY LORIXD                                     */
/********                                                                                                                 */
/********                                       Parancsok:                                                                */
/********                                                                                                                 */
/********      S = StarWars Elindul                              D = Senzor Erzekel                                       */
/********      R = Ujrainditas                                   1 = LED1 ki/be kapcsolasa                                */
/********      2 = LED2 ki/be kapcsolasa                                                                                  */
/********                                                                                                                 */
/********                                                                                                                 */



#include "Ultrasonic.h"
#include "Arduino.h"

Ultrasonic ultrasonic( 52, 53 );

int cm;

  
void setup() {
  Serial.begin(9600);
}
  
void loop() {
  
    int timing;
  cm=ultrasonic.Ranging(CM);
  
  
       if (cm>=300)
         Serial.println("over 300cm");
          else
         {
         Serial.print("distance: ");
         Serial.print(cm);
         Serial.println("cm");
         }

delay(500);  
 }

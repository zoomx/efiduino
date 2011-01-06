
/**
 * EFIDuino - An Arduino EMS!
 * 
 * 
 **/


#include "Adc.h"

taskLoop(Adc){

  StartADCs();

  delay(100);



}

void setup(){


      
  Serial.begin(9600);

  createTaskLoop(Adc, NORMAL_PRIORITY);
  initMainLoopPriority(NORMAL_PRIORITY);

  
}


void loop(){



  delay(1000);

}





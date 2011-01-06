

#ifndef _ADC_H
#define _ADC_H


#include <WProgram.h>

enum ADCInputType{
  VBATT, // Battery voltage            - A0
  TPS,   // throttle position sensor   - A1
  CLT,   // Colant temperature         - A2
  MAT,   // Manifold Air temperature   - A3
  MAP,   // Manifold Absolute Pressure - A4
  KNOCK, // Knock sensor               - A5
  EGO,   // Exhaust Gas Oxygen         - A6   
  MAX_ADC_INPUTS
};



class ADCInput{
private:
  volatile int value;
public:
  uint8_t AnalogPin;
  uint8_t AnalogReference; 
  ADCInput(uint8_t analogPin, uint8_t mode);
  int Value();
  int SetValue(volatile int value){ 
    this->value = value; 
  }
};



extern ADCInput VBatt;
extern ADCInput Tps;
extern ADCInput Clt;
extern ADCInput Mat;
extern ADCInput Map;
extern ADCInput Knock;
extern ADCInput Ego;

void StartADCs();

#endif //_ADC_H










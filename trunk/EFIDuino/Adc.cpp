

#include "Adc.h"


ADCInput::ADCInput(uint8_t pin, uint8_t mode){
  AnalogPin = pin;
  AnalogReference = mode;
}

int ADCInput::Value()
{

  int val = value;

  return val;    

}


ADCInput VBatt(0, DEFAULT);
ADCInput Tps(1,DEFAULT);
ADCInput Clt(2,DEFAULT);
ADCInput Mat(3,DEFAULT);
ADCInput Map(4,DEFAULT);
ADCInput Knock(5,DEFAULT);
ADCInput Ego(6,DEFAULT);


ADCInput *ADCInputs[MAX_ADC_INPUTS] = {
  &VBatt,
  &Tps,
  &Clt,
  &Mat,
  &Map,
  &Knock,
  &Ego
};

uint8_t currentADCIdx;

void StartADCs(){

  currentADCIdx = 0;

    ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((ADCInputs[currentADCIdx]->AnalogPin >> 3) & 0x01) << MUX5);
    ADMUX = (ADCInputs[currentADCIdx]->AnalogReference << 6) | (ADCInputs[currentADCIdx]->AnalogPin & 0x07);
//    ADCSRA |= _BV(ADIF);
    ADCSRA |= ((1<<ADSC) | (1<<ADEN)  | (1<<ADIE) | (1<<ADIF));

}  


SIGNAL(SIG_ADC){

  ADCInput * adc = ADCInputs[currentADCIdx];

  uint8_t low, high;

  low = ADCL;
  high = ADCH;

  adc->SetValue((high << 8) | low);

  //  Serial.println("GOT HERE");
  currentADCIdx++;
  if(currentADCIdx >=MAX_ADC_INPUTS){
    ADCSRA &= ~_BV(ADIE); // disable interrupt
    currentADCIdx = 0;
  }
  else{
    ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((ADCInputs[currentADCIdx]->AnalogPin >> 3) & 0x01) << MUX5);
    ADMUX = (ADCInputs[currentADCIdx]->AnalogReference << 6) | (ADCInputs[currentADCIdx]->AnalogPin & 0x07);
    ADCSRA |= ((1<<ADSC) | (1<<ADEN)  | (1<<ADIE) | (1<<ADIF));
  }
}


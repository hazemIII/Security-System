/*
 * ADC.c
 *
 * Created: 30-Aug-14 12:20:46 PM
 *  Author: hazemmamdouh
 */ 

#include <avr/io.h>
#include "ADC.h"

void ADC_INI(INT8U Mode)
{  ADMUX = ADMUX_DEFAULT + Mode ;
   ADCSRA |= (1<<ADEN)|(1<<ADATE);

}

void ADC_START()
{  ADCSRA |= (1<<ADSC);
}

INT16U ADC_READ()
{
  INT16U reading;
  while(!(ADCSRA & (1<<ADIF))); 
  reading = ADCL +(ADCH<<8);			   
  return reading;	
}


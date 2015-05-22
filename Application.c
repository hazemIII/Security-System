/*
 * Application.c
 *
 * Created: 26-Oct-14 4:30:56 PM
 *  Author: hazemmamdouh
 */ 

#include "Application.h"

INT8U Temp_Value(INT16U sensor)
{ 
  INT8U value ;
  value = (INT8U)(sensor/2) ;
  if (value > 25)
  value--; 
  if (value > 61)
  value -- ;	  
  if (value > 100)
  value--;
  if (value > 137)
  value--;
  return value ; 	
}

INT16U ADC_Channel(INT8U Sensor)
{ 
  ADC_INI(Sensor);
  _delay_ms(5);
  ADC_START();	
  return ADC_READ();
}

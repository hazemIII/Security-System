/*
 * ADC.h
 *
 * Created: 30-Aug-14 12:21:23 PM
 *  Author: hazemmamdouh
 */ 


#ifndef ADC_H_
#define ADC_H_
#include "std_types.h"
#define ADMUX_DEFAULT 0X40
#define Temp_Sensor 0x00 
#define Proximity 0x01 
#define Open_Close 0x02
#define Out_Proximity PD2
#define Out_Open_Close PD3

void ADC_INI(INT8U);
void ADC_START();
INT16U ADC_READ();



#endif /* ADC_H_ */
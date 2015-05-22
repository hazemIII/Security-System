/*
 * test.c
 *
 * Created: 26-Oct-14 4:14:07 PM
 *  Author: hazemmamdouh
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Application.h"
#include "LCD_Driver.h"
#include "keypad.h"

INT16U TempValue,ProxValue,LDRValue;
INT8U First_time = 0 , last_Temp_value , OUTCHAR;
int main(void)
{   Key_ini();
	lcd_Init(MODE_4_LINES);
    sei();
	DDRC = 0xFF;
	DDRD = 0xFF;

    while(1)
    { 
      TempValue = Temp_Value(ADC_Channel(Temp_Sensor));
	  if(First_time == 0)
	  {
	  	lcd_Display_String("Temp. sensor is");
		First_time = 1;  	  
	    lcd_Goto_xy(2,0);
	    INT_DISP(TempValue);
		lcd_Display_Char(' ');
		last_Temp_value = TempValue ;
	  }
	  if(last_Temp_value != TempValue)
	  { last_Temp_value = TempValue ;
	    lcd_Goto_xy(2,0);
	    INT_DISP(TempValue);	
		lcd_Display_Char(' ');	  
	  }
	  
	  OUTCHAR =GetKey();
	  _delay_ms(750);
	 if (check == 1)   
	 {if (OUTCHAR == 0x01)
	   { lcd_Send_Command(CLEAR_DISPLAY_AND_RAM);
		 _delay_ms(250);
		 check = 0;  
		 First_time = 0 ;
	  }
	 else
	  { lcd_Display_Char(OUTCHAR);
        _delay_ms(250);
		check = 0;	
	  }	
	  
	}	
	
	  PORTD |= (1<<Proximity_input_pin);
	  ProxValue = ADC_Channel(Proximity); 
	  if (ProxValue < 1000)
	  PORTD |= (1<<Out_Proximity);
	  else 
	  PORTD &= ~(1<<Out_Proximity);
	  PORTD &= ~(1<<Proximity_input_pin);
	  LDRValue = ADC_Channel(Open_Close);
	  if (LDRValue >= 2)
	  PORTD |= (1<<Out_Open_Close);
	  else 
	  PORTD &= ~(1<<Out_Open_Close);
	    
    }
}


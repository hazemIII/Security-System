/*
 * keypad.c
 *
 * Created: 29-Aug-14 9:50:58 AM
 *  Author: hazemmamdouh
 */ 

#include"keypad.h"

INT8U  u8keypadArr [4][4]= {{'/','9','8','7'},{'*','6','5','4'},{'-','3','2','1'},{'+','=','0',0x01}};
INT8U  U8pressedkey;
INT8U  U8row[]= {0x7F,0xBF,0xDF,0xEF};
INT8U  U8col[]= {0x07,0x0B,0x0D,0x0E};	
INT8U  PINch[]= {0x80,0x40,0x20,0x10};	

void Key_ini()
{	DDRB = 0xF0;
	SFIOR &=~(1<<PUD);
}

INT8U GetKey()
{ INT8U row ,col;
	DDRB = 0xF0;
  for(row=0 ; row<4 ; row++)
    {	
		DDRB = PINch[row];
        PORTB = U8row[row];
	    for(col=0; col<4 ; col++)
		 { 
			if((PINB&0x0f) == U8col[col])
			 {U8pressedkey = u8keypadArr[row][col]; 
			  check = 1;	 
			 }		     		 
		 }
	}	
  return U8pressedkey ;	   
}
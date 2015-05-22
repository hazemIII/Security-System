
#include <avr/delay.h>
#include "LCD_Driver.h"


#define PERIOD 10
INT8U u8Mode ;




/// Sending LCD Commands
/** 
 ** @param cmd : the command to be send to LCD
 ** @ret void
 */
void lcd_Send_Command( INT8U cmd)
{
	if(u8Mode == MODE_8_LINES)
	{
		DATA_PORT = 0x00;
		DATA_PORT = cmd;
		CTRL_PORT = 0x00;
		_delay_ms(PERIOD);
		CTRL_PORT |= (1<<E_LCD);
	} 
	else if(u8Mode == MODE_4_LINES)
	{

		DATA_PORT &= 0x0f;
		DATA_PORT |= (cmd&0xF0);
		CTRL_PORT &= ~(1<<RS_LCD);
		CTRL_PORT &= ~(1<<RW_LCD);
		CTRL_PORT &= ~(1<<E_LCD);
		_delay_ms(PERIOD);
		CTRL_PORT |= (1<<E_LCD);
		_delay_ms(5);
		DATA_PORT &= 0x0F ;					// anding the PORTD with 0x0F to clear the brevious value on the LCD pins
		DATA_PORT |= ((cmd<<4) & 0xF0)	;
		CTRL_PORT &= ~(1<<RS_LCD);
		CTRL_PORT &= ~(1<<RW_LCD);
		CTRL_PORT &= ~(1<<E_LCD);
		_delay_ms(PERIOD);
		CTRL_PORT |= (1<<E_LCD);
		_delay_ms(5);

		
	}
	
}


/// intialize the LCD
/** 
 ** @param mode : mode of operation 8 or 4 
 ** @ret void 
 */
void lcd_Init( INT8U mode)
{
	DDR_CTRL |= (1<<RS_LCD)|(1<<E_LCD)|(1<<RW_LCD);
	CTRL_PORT = (1<<E_LCD);
	u8Mode = mode;
	if (mode == MODE_8_LINES)
	{
		DDR_DATA = 0xFF;
		
		lcd_Send_Command(MODE_8_BIT);
		
		lcd_Send_Command(MODE_8_BIT);

		
	}
	else if (mode == MODE_4_LINES)
	{
		DDR_DATA |= 0xF0;
		
		lcd_Send_Command(MODE_4_BIT);
		CTRL_PORT &= ~(1<<RS_LCD);
		CTRL_PORT &= ~(1<<RW_LCD);
		CTRL_PORT &= ~(1<<E_LCD);
		_delay_ms(PERIOD);
		CTRL_PORT |= (1<<E_LCD);		
		//_delay_ms(PERIOD);
		lcd_Send_Command(MODE_4_BIT);
	}
	else
	{
		// nothing
	}
	
	lcd_Send_Command(DISPLAY_ON_CURSOR_ON);
	lcd_Send_Command(CLEAR_DISPLAY_AND_RAM);
	
	
}

/// Display one character
/** 
 ** @param data: to be sent to lcd
 ** @ret void
 */
void lcd_Display_Char(  INT8U data)
{
	CTRL_PORT = (1<<E_LCD);
	if (u8Mode == MODE_8_LINES)
	{		
		DATA_PORT = data;
        CTRL_PORT |= (1<<RS_LCD);
        CTRL_PORT &=~ (1<<RW_LCD);
		CTRL_PORT &=~ (1<<E_LCD); 	
		_delay_ms(10);
		CTRL_PORT |= (1<<E_LCD);	
	}
	else if (u8Mode == MODE_4_LINES)
	{
		DATA_PORT &= 0x0F;
        DATA_PORT |= (data & 0xF0);
        CTRL_PORT |= (1<<RS_LCD);
		CTRL_PORT &= ~(1<<RW_LCD);
		CTRL_PORT &= ~(1<<E_LCD);
		_delay_ms(10);
		CTRL_PORT |= (1<<E_LCD);	
		
		DATA_PORT &= 0x0F;
		DATA_PORT |= ((data<<4)& 0xF0);
		CTRL_PORT |= (1<<RS_LCD);
		CTRL_PORT &= ~(1<<RW_LCD);
		CTRL_PORT &= ~(1<<E_LCD);
		_delay_ms(10);
		CTRL_PORT |= (1<<E_LCD);
	}
	else
	{
		// nothing
	}
}

/// Display String
/** 
 ** @param 
 ** @ret 
 */
void lcd_Display_String(INT8U str[])
{ INT8U i;
  for (i=0 ; i<strlen(str) ; i++)
  {  lcd_Display_Char(str[i]);
	 C++;
     if(C==16)
      {lcd_Send_Command(MOVE_DISPLAY);
	   K++;	  
	   C--;	
	  }	  
	if(K==39)
	 {lcd_Send_Command(RETURN_HOME);  
	  C=0;
	  K=16;
	 } 
  }
	
}


/// LCD Display number 
/** this function will convert the number to its ASCII to be able to display on screen 
 ** @param int number
 ** @ret void
 */
void INT_DISP(INT16S num)
{   
	INT8S number[5];
	INT16S i, reminder, length = 0, n;
 
    n = num;
	if(n<0)
	{ lcd_Display_Char('-');
	  num = abs(num);	
	}
    while (n != 0)
    {
        length++;
        n /= 10;
    }
	
    for (i = 0; i < length; i++)
    {
        reminder = num % 10;
        number [length -(i+1)]= (reminder + '0');
		num = num / 10;
		
    }
	for (i = 0;i<length ; i++)
	   { if(number [i] == 0 && length == 1)
		   { lcd_Display_Char(' ');
			 lcd_Display_Char('0');  
		   }		   
		 else if(number [i] > 0 && length== 1 )
		   { lcd_Display_Char(' ');
			 lcd_Display_Char(number[i]);
		   }			   
		 else
         lcd_Display_Char(number[i]);  
	   }	
    

}

/// GoTo XY at LCD
/** 
 ** @param 
 ** @ret 
 */
void lcd_Goto_xy(INT8U row ,INT8U col)
{   
    if (row == 1)
	{lcd_Send_Command(RETURN_HOME);
     lcd_Send_Command(MOVE_CURSOR+col+LCD_ROW_1);
	 C=col;	
	}		
	else if (row == 2)
	{lcd_Send_Command(RETURN_HOME);
     lcd_Send_Command(MOVE_CURSOR+col+LCD_ROW_2);
	 C=col;
	}	 	
	
	
	
}

lcd_Clear_Screen(void)
{
 lcd_Send_Command(CLEAR_DISPLAY_AND_RAM);	
}

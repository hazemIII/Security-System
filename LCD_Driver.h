


#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#include <avr/io.h>
#include "std_types.h"

/// # define part of the LCD Commands and constants
///////////////////////
#define MODE_8_BIT 0x38
///////////////////////
#define MODE_4_BIT 0x28
///////////////////////
#define DISPLAY_ON_CURSOR_ON 0x0E
///////////////////////
#define CLEAR_DISPLAY_AND_RAM 0x01
///////////////////////
#define LCD_ROW_1 0x00
///////////////////////
#define LCD_ROW_2 0x40
///////////////////////
#define MOVE_CURSOR 0x80
///////////////////////
#define CURSOR_BLINKING 0x0F
///////////////////////
#define MOVE_CURSOR_LEFT_BY_ONE 0x10 
///////////////////////
#define MOVE_CURSOR_RIGHT_BY_ONE 0x14 
///////////////////////
#define SHIFT_ENTIRE_DISPLAY_LEFT 0x18
///////////////////////
#define MOVE_DISPLAY 0x1C
/////////////////////////
#define RETURN_HOME 0x02
////////////////////////
#define CURSOR_OFF 0x0C
///////////////////////
#define RS_LCD PC0  // set to command
#define RW_LCD PC1 // set to write
#define E_LCD  PC2 // set to enable
#define DDR_CTRL DDRC
#define CTRL_PORT PORTC
#define DDR_DATA DDRC
#define DATA_PORT PORTC 
#define MODE_8_LINES 8
#define MODE_4_LINES 4


/// intialize the LCD
/** 
 ** @param 
 ** @ret 
 */
void lcd_Init( INT8U );			//done 

/// Sending LCD Commands
/** 
 ** @param 
 ** @ret 
 */
void lcd_Send_Command( INT8U );		// done

/// Display one character
/** 
 ** @param 
 ** @ret 
 */
void lcd_Display_Char(  INT8U );				// done
	
/// Clear LCD Screen
/** 
 ** @param 
 ** @ret 
 */
void lcd_Clear_Screen(void);

/// GoTo XY at LCD
/** 
 ** @param 
 ** @ret 
 */
void lcd_Goto_xy( INT8U,  INT8U);				//done 

/// Display String
/** 
 ** @param 
 ** @ret 
 */
void lcd_Display_String(  INT8U* );		//done



/// LCD Display number 
/** this function will convert the number to its ASCII to be able to display on screen 
 ** @param int number
 ** @ret void
 */
void INT_DISP(INT16S);





#endif

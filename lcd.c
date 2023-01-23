/*
@brief * lcd function firmware
@file * lcd.c 

This software contains all the functions for using the i2c peripheral with extern Lcd.
All the functions are commented but for a better understanding of their meaning you must read the 
report at section "visualization block",but also the corresponding datasheet of the lcd which can you find always on the report
*/

/*lcd.c include*/
#include "lcd.h"

/*variables definition and declarations. for local variables the prefix "l" is used
 for global variables "g" before the name, "b for boolean*/

/*/this is a global "local" variables used for using the i2c peripheral. It will be called in "lcd init" function.
 It is used only in this file by making a copy of the i2c variable generated by the CUBE_IDE. So doing we don't need 
 to cahnge every time in all the function, but just modyfing 1 line of function in the main.c*/

I2C_HandleTypeDef *g_lcd_i2c;



/*function n: */
void lcd_send_cmd ( char command )
{
  char l_data_u, l_data_l;
	uint8_t l_data[4];
	l_data_u = ( command & 0xf0 );
	l_data_l = (( command << I2C_PCK_SIZE ) & 0xf0 );
	l_data[0] = l_data_u|0x0C;  //en=1, rs=0
	l_data[1] = l_data_u|0x08;  //en=0, rs=0
	l_data[2] = l_data_l|0x0C;  //en=1, rs=0
	l_data[3] = l_data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (g_lcd_i2c, LCD_SLAVE_ADRESS,(uint8_t *)l_data, I2C_PCK_SIZE, I2C_DELAY);
}

/*function n:*/
void lcd_send_data( char data )
{
	char l_data_u, l_data_l;
	uint8_t l_data[I2C_PCK_SIZE];
	l_data_u = ( data & 0xf0);
	l_data_l = (( data << I2C_PCK_SIZE ) & 0xf0);
	l_data[0] = l_data_u|0x0D;  //en=1, rs=1
	l_data[1] = l_data_u|0x09;  //en=0, rs=1
	l_data[2] = l_data_l|0x0D;  //en=1, rs=1
	l_data[3] = l_data_l|0x09;  //en=0, rs=1
	HAL_I2C_Master_Transmit (g_lcd_i2c, LCD_SLAVE_ADRESS,(uint8_t *)l_data, I2C_PCK_SIZE, I2C_DELAY);
}

/*function n:*/
void lcd_clear ( void )
{
	lcd_send_cmd (0x00);
	for (int i=0; i<100; i++)
	{
		lcd_send_data (' ');
	}
}

/*function n:*/
void lcd_put_cur( int row, int column )
{
    switch (row)
    {
        case 0:
            column |= 0x80;
            break;
        case 1:
            column |= 0xC0;
            break;
    }

    lcd_send_cmd (column);
}

/*function n:*/
void lcd_init( I2C_HandleTypeDef *lcd_i2c )
{
    //making a copy of the i2c variables from main.c 
    g_lcd_i2c = lcd_i2c; 
	// 4 bit initialization
	HAL_Delay(50);  // wait for >40ms
	lcd_send_cmd (0x30);
	HAL_Delay(5);  // wait for >4.1ms
	lcd_send_cmd (0x30);
	HAL_Delay(1);  // wait for >100us
	lcd_send_cmd (0x30);
	HAL_Delay(10);
	lcd_send_cmd (0x20);  // 4bit mode
	HAL_Delay(10);

  // lcd initialization
	lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(1);
	lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(1);
	lcd_send_cmd (0x01);  // clear display
	HAL_Delay(1);
	HAL_Delay(1);
	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(1);
	lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

/*function n:*/
void lcd_send_string( char *str )
{
	while (*str) lcd_send_data(*str++);
}

/*function n: */
void print_on_lcd( char variable[] )
{
    lcd_clear();
	lcd_send_cmd (FIRST_COLUMN|FIRST_ROW);
	lcd_put_cur(CURSOR_1, CURSOR_2);
	lcd_send_string( variable );
}

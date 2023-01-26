/*
@brief: lcd.h
@file: lcd.h header file

This file was developed for the ESD Project
This is the header file for lcd function
All the function and variable used in this file are commented, but all the specification 
about the functions, how they where developed, variables and all the features can be read in
the report at section "visualization block"
 */

#ifndef __LCD_H
#define  __LCD_H

/*lcd.h private include*/
#include <stm32f4xx_hal.h>

/*lcd.h private define*/
# define FIRST_ROW 0x00 //address of the first row of the LCD retrieved by the datasheet
# define FIRST_COLUMN 0x80 //address of the first column of the LCD retrieved by the datasheet
# define CURSOR_1 0 //indicate the first row of the LCD
# define CURSOR_2 1 //indicate the second column of the LCD
# define LCD_SLAVE_ADRESS 0x4E // slave address value in hex. it is written in the datasheet of lcd 
# define I2C_DELAY 100
# define I2C_PCK_SIZE 4

/*lcd.h private function*/
void lcd_init( I2C_HandleTypeDef *lcd_i2c ); 
void lcd_send_cmd ( char command );
void lcd_send_data ( char data );
void lcd_send_string ( char *str );
void lcd_put_cur( int row, int column );
void lcd_clear( void );
void print_on_lcd( char variable[] );

#endif /* LCD_H  */
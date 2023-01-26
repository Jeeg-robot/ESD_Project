/**********/
/*This file was developed for the ESD Project
This is the header file file of visualization block 
All the function and variable used in this file are commented, but all the specification 
about the functions, how they where developed, variables and all the features can be read in
the report at section "visualization block" */
/*********/

#ifndef __VISUALIZE_H
# define __VISUALIZE_H

/*visualize.h private include*/
# include <stm32f4xx_hal.h>
# include <stdio.h>
# include <string.h>
# include <lcd.h>
# include <stdlib.h>
# include <main.h> //MODIFICARE
# include <usart.h> //MODIFICARE
# include <stdbool.h>


/*visualize.h private define */
# define FIRST_ROW 0x00 //First element of the first row specified by the datasheet
# define SECOND_ROW 0X80 //First element of the second row specified by the datasheet
# define CURSOR_1 0 //indicate the first row of the LCD
# define CURSOR_2 1 //indicate the second column of the LCD
# define LCD_REFRESH_THRESHOLD_COUNTER 100; //max value of refresh lcd counter
# define LCD_TEST 1
# define COMMAND_SIZE 1

/*visualize.h private typedef */
// define a new type of enum variables which contains all the possible variables to visualize on LCD and on Putty 
typedef enum
{
	NONE = 0,
    PHASE_SHIFT,      //1
    POWER_FACTOR,     //2
    ACTIVE_POWER,     //3
    REACTIVE_POWER,   //4
    APPARENT_POWER,   //5
    POWER_CONSUMPTION //6

}param_case_t; 

typedef enum
{
	FLAG_NOT_SET = 0,
	FLAG_SET
}bit_status_t;

/*visualize.h extern variables*/
extern param_case_t g_param_case;
extern bool b_lcd_refresh_flag;
extern bool b_uart_int_flag;
extern uint8_t g_lcd_refresh_counter;

/*visualize.h private functions*/
void visualize_virtual_main( void ); 
void HAL_UART_RxCpltCallback( UART_HandleTypeDef * huart );
void ask_new_variable( void );
void setup_putty_uart( UART_HandleTypeDef * huart );
#endif  /* VISUALIZE_H*/
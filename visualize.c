/*
 @brief * visualization block's firmware
 @file * visualize.c

 This software contain the following feautures:
 1) visualization on Lcd by i2c the following parameters : Phase Shift, Power Factor, Active Power,
 Reactive Power, Apparent Power, Power Consumption.
 2) UI by using serial communication (UART protocol) by using PUTTY. The standard library is used so the "printf" function refer to the visualization on PUTTY
 */

/*visualize.c include*/
#include "visualize.h"

/*variables definition and declarations. for local variables the prefix "l" is used
 for global variables "g" before the name, "b for boolean*/

param_case_t g_param_case = 0; // this parameter contain the state chosen by the user for the variable to visualize.
uint8_t buffer = 0;
UART_HandleTypeDef *g_putty_uart;

bool b_uart_int_flag = FLAG_NOT_SET;

bool b_lcd_refresh_flag = FLAG_NOT_SET;


#define _IsSet(reg,bit) (reg >> (bit - 1)) & 0x1

/*function n : this is the virtual main for visualize.c source file. */

void visualize_virtual_main(void) {

	if (b_uart_int_flag == FLAG_SET) {
		b_uart_int_flag = FLAG_NOT_SET;
		ask_new_variable();
	}

	if (b_lcd_refresh_flag == FLAG_SET) {
		b_lcd_refresh_flag = FLAG_NOT_SET;

		g_param_case  = g_param_case & 0x007;
		/* switch cases based on user's choice*/
		switch (g_param_case)
		{
		case NONE:
		break;

		case PHASE_SHIFT:
#ifndef PUTTY_TEST
			//printf("PHASE_SHIFT\n");
#endif

#ifndef LCD_TEST
		        print_on_lcd();
		         #endif
		break;

		case POWER_FACTOR:
#ifndef PUTTY_TEST
			//printf("POWER FACTOR\n");
#endif

#ifndef LCD_TEST
		         print_on_lcd();
		         #endif
		break;

		case ACTIVE_POWER:
#ifndef PUTTY_TEST
			//printf("ACTIVE POWER\n");
#endif

#ifndef LCD_TEST
		         print_on_lcd();
		         #endif
		break;

		case REACTIVE_POWER:
#ifndef PUTTY_TEST
			//printf("REACTIVE POWER\n");
#endif
		case APPARENT_POWER:
		break;
#ifndef LCD_TEST
		         print_on_lcd();
		         #endif
		break;

		case POWER_CONSUMPTION:
#ifndef PUTTY_TEST
			//printf("POWER CONSUMPTION \n");
#endif

#ifndef LCD_TEST
		         print_on_lcd();
		         #endif
		break;

//		default:
//#ifndef PUTTY_TEST
//			//printf("Wrong number inserted\n");
//#endif
//
//#ifndef LCD_TEST
//		         print_on_lcd();
//		         #endif
//			break;
		}
	}
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (g_putty_uart == huart )
	{
		//HAL_UART_Receive_IT(g_putty_uart, &g_param_case, COMMAND_SIZE);
		b_uart_int_flag = FLAG_SET;

	}
//}
}

void ask_new_variable(void) {

	/*visualization of the list of all possible parameters*/

	printf("\r\nWhat parameter do you want to read?");
	printf("\r\n\r1 : Phase Shift");
	printf("\r\n2 : Power Factor");
	printf("\r\n3 : Active Power");
	printf("\r\n4 : Reactive Power");
	printf("\r\n5 : Apparent Power");
	printf("\r\n6 : Power Consumption");
	printf(" \r\n");
	/*acquire user's choice*/
	//printf("\r\n param : ");

}

void setup_putty_uart(UART_HandleTypeDef *huart) {
	g_putty_uart = huart;
}

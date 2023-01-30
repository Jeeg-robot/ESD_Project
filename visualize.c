/*
 @brief * visualization block's firmware
 @file * visualize.c

 This software contain the following feautures:
 1) visualization on LCD by i2c the following parameters : Phase Shift, Power Factor, Active Power,
 Reactive Power, Apparent Power, Power Consumption.
 2) UI by using serial communication (UART protocol) by using PUTTY. The standard library is used so the "printf" function refer to the visualization on PUTTY
 */

/*visualize.c include*/
#include "visualize.h"

/*variables definition and declarations. for local variables the prefix "l" is used
 for global variables "g" before the name, "b for boolean*/

param_case_t g_param_case = WAITING; // this parameter contain the state chosen by the user for the variable to visualize.
uint8_t g_lcd_refresh_counter=0; //This code is used within the interrupt function systic_endler. At a frequency of 1kHz, the value of this variable increases by 1 when it reaches the value of 100, as defined by the LCD_REFRESH_THRESHOLD_COUNTER definition. 
								//Then, the value is reset to 0 and the b_lcd_refresh_flag is set.
UART_HandleTypeDef *g_putty_uart;

bool b_uart_int_flag = FLAG_NOT_SET;

bool b_lcd_refresh_flag = FLAG_NOT_SET;

char g_phase_delay_string[20];
char g_power_factor_string[10];
char g_active_power_string[20];
char g_reactive_power_string[30];
char g_apparent_power_string[20];
char g_voltage_eff_string[20];

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(g_putty_uart, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}

/*function n.1: this is the virtual main containing the switch case for the selected parameter. */

void visualize_virtual_main(void) {

	if (b_uart_int_flag == FLAG_SET) {
		b_uart_int_flag = FLAG_NOT_SET;
		ask_new_variable();
	}

	if (b_lcd_refresh_flag == FLAG_SET) {
		b_lcd_refresh_flag = FLAG_NOT_SET;

		g_param_case  = g_param_case & 0x007;
		/* switch cases based on user's choice*/
		switch (g_param_case) {
		case WAITING:
			break;

		case PHASE_SHIFT:

			snprintf(g_phase_delay_string,sizeof(g_phase_delay_string),"PD = %d",(int16_t)g_phase_delay);
			print_on_lcd(g_phase_delay_string);

			break;

		case POWER_FACTOR:

			snprintf(g_power_factor_string,sizeof(g_power_factor_string),"PF = %.4f", g_power_factor);
		    print_on_lcd(g_power_factor_string);

			break;

		case ACTIVE_POWER:

		   snprintf(g_active_power_string,sizeof(g_active_power_string),"AP = %.2fmW", g_active_power);
		   print_on_lcd(g_active_power_string);

			break;

		case REACTIVE_POWER:

			snprintf(g_reactive_power_string,sizeof(g_reactive_power_string),"RP = %.2fVAR", g_reactive_power);
			print_on_lcd(g_reactive_power_string);

        break;
		case APPARENT_POWER:

			snprintf(g_apparent_power_string,sizeof(g_apparent_power_string),"Ap.P = %.2fVA", g_apparent_power);
			print_on_lcd(g_apparent_power_string);

			break;

		case EFFECTIVE_VOLTAGE:

			snprintf(g_voltage_eff_string,sizeof(g_voltage_eff_string),"Veff = %.2fmV", g_voltage_eff);
			print_on_lcd(g_voltage_eff_string);

			break;
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
	printf("\r\n6 : Effective Voltage");
	printf(" \r\n");
	/*acquire user's choice*/
	//printf("\r\n param : ");

}

void setup_putty_uart(UART_HandleTypeDef *huart) {
	g_putty_uart = huart;
}

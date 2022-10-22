/*
 * PWM2S.h
 *
 *  Created on: Oct 22, 2022
 *      Author: Maxmi
 */

#ifndef INC_PWM2S_H_
#define INC_PWM2S_H_

/*PWM2S include*/
#include "main.h"
#include "stdbool.h"
/*PWM2S define*/
#define TIM2_CLOCK 21000000
#define DCoffset 4
#define FRQoffset 300

/*PWM2S function declaration*/
uint8_t GetDutyCycle(uint32_t ONstate, uint32_t period);
uint32_t GetFrequency(uint32_t TimerCounter, uint32_t TimerPrescaler);

#endif /* INC_PWM2S_H_ */

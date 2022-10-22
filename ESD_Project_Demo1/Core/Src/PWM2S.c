/*
 * PWM2S.c
 *
 *  Created on: Oct 22, 2022
 *      Author: Maxmi
 */

#include "PWM2S.h"










uint8_t GetDutyCycle(uint32_t ONstate, uint32_t period)
{ return (100*ONstate)/period + DCoffset;}

uint32_t GetFrequency(uint32_t TimerCounter, uint32_t TimerPrescaler)
{ return (TIM2_CLOCK/(TimerPrescaler + 1))/TimerCounter + FRQoffset;}




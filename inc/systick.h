/*
 * systick.h
 *
 *  Created on: 18/10/2015
 *      Author: MarcosDario
 */
#include "stdint.h"
#include "chip.h"

#ifndef SYSTICK_H_
#define SYSTICK_H_

void Configurar_Systick(void);
void SysTick_Handler(void);
void delay_ms (uint32_t delay_time);

#endif /* SYSTICK_H_ */

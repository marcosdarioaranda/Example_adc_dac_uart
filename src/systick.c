/*
 * systick.c
 *
 *  Created on: 18/10/2015
 *      Author: MarcosDario
 */
#include "systick.h"
#include "chip.h"

volatile uint32_t contador_ms; // contador para el SysTicks 1ms

void Configurar_Systick(void){
	contador_ms = 0;
	// Setup SysTick Timer to interrupt at 1 msec intervals
		if (SysTick_Config(SystemCoreClock / 1000)) {
		    while (1);  // Captura el error
		}
}

//  SysTick_Handler
void SysTick_Handler(void) {

	if(contador_ms>0)
		contador_ms--;
}

void delay_ms (uint32_t delay_time) {
	contador_ms = delay_time;
	while(contador_ms!=0);

}

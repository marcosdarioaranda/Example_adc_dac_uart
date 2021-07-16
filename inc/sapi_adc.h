/*
 * sapi_adc.h
 *
 *  Created on: 7 jul. 2021
 *      Author: MARCO
 */

#include <sapi_datatypes.h>
#include "chip.h"
#include "stdint.h"

#ifndef SAPI_ADC_H_
#define SAPI_ADC_H_

#define adcConfig adcInit

/*==================[typedef]================================================*/

typedef enum {
   ADC_ENABLE,
   ADC_DISABLE
} adcInit_t;

/*==================[external functions declaration]=========================*/

void adcInit( adcInit_t config );

uint16_t adcRead( adcMap_t analogInput );



#endif /* SAPI_ADC_H_ */

/*
 * sapi_adc.c
 *
 *  Created on: 7 jul. 2021
 *      Author: MARCO
 */
#include <sapi_adc.h>
#include "chip.h"
#include "stdint.h"

void adcInit( adcInit_t config )
{
   /*
   Pines ADC LPC1769

   ADC0 ---- P0_23
   ADC1 ---- P0_24
   ADC2 ---- P0_25
   ADC4 ---- P1_30
   ADC5 ---- P1_31

   */

   switch(config) {

      case ADC_ENABLE: {

         /* Config ADC sample mode */
         ADC_CLOCK_SETUP_T ADCSetup = {
            ADC_MAX_SAMPLE_RATE,   // ADC Sample rate:ADC_MAX_SAMPLE_RATE = 200KHz
            12,                    // ADC resolution: ADC_12BITS = 12
            0                      // ADC Burst Mode: (true or false)
         };

         Chip_ADC_Init( LPC_ADC, &ADCSetup );
         /* Disable burst mode */
         Chip_ADC_SetBurstCmd( LPC_ADC, DISABLE );
         /* Set sample rate to 200KHz */
         Chip_ADC_SetSampleRate( LPC_ADC, &ADCSetup, ADC_MAX_SAMPLE_RATE);
         /* Disable all channels */
         Chip_ADC_EnableChannel( LPC_ADC, ADC_CH0, DISABLE );
         Chip_ADC_Int_SetChannelCmd( LPC_ADC, ADC_CH0, DISABLE );

         Chip_ADC_EnableChannel( LPC_ADC, ADC_CH1, DISABLE );
         Chip_ADC_Int_SetChannelCmd( LPC_ADC, ADC_CH1, DISABLE );

         Chip_ADC_EnableChannel( LPC_ADC, ADC_CH2, DISABLE );
         Chip_ADC_Int_SetChannelCmd( LPC_ADC, ADC_CH2, DISABLE );

         Chip_ADC_EnableChannel( LPC_ADC, ADC_CH4, DISABLE );
         Chip_ADC_Int_SetChannelCmd( LPC_ADC, ADC_CH4, DISABLE );

         Chip_ADC_EnableChannel( LPC_ADC, ADC_CH5, DISABLE );
         Chip_ADC_Int_SetChannelCmd( LPC_ADC, ADC_CH5, DISABLE );

      }
      break;

      case ADC_DISABLE:
         /* Disable ADC peripheral */
         Chip_ADC_DeInit( LPC_ADC);
         break;
      }

}


/*
 * @brief   Get the value of one ADC channel. Mode: BLOCKING
 * @param   AI0 ... AIn
 * @return  analog value
 */
uint16_t adcRead( adcMap_t analogInput )
{

   uint16_t analogValue = 0;

   // Enable channel
   Chip_ADC_EnableChannel(LPC_ADC, analogInput, ENABLE);

   // Start conversion
   Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);

   // Wait for conversion complete
   while(
      (Chip_ADC_ReadStatus(LPC_ADC, analogInput, ADC_DR_DONE_STAT) != SET)
   );

   // Enable Read value
   Chip_ADC_ReadValue( LPC_ADC, analogInput, &analogValue );

   // Disable channel
   Chip_ADC_EnableChannel( LPC_ADC, analogInput, DISABLE );

   return analogValue;
}


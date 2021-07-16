/*
===============================================================================
 Name        : Example_adc_dac_uart.c
 Author      : Ms. Ing. Marcos D. Aranda
 Version     : 1.0
 Copyright   : $(copyright)
 Description : Este ejemplo lee datos del ADC0, para posteriormente mostrarlos
               por el DAC y la UART.
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include <sapi_gpio.h>
#include <sapi_adc.h>
#include <sapi_dac.h>
#include <sapi_uart.h>
#include <sapi_datatypes.h>
#include "systick.h"
#include "itoa.h"
// TODO: insert other definitions and declarations here

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();

#endif
#endif

    // TODO: insert code here
    /* ------------- INICIALIZACIONES ------------- */
    Configurar_Systick();

    gpioInit( 0,22, GPIO_OUTPUT );

    /* Inicializar UART_3 a 115200 baudios */
    uartInit( UART_3, 115200 );

    /* Inicializar AnalogIO */
    /* Posibles configuraciones:
     *    ADC_ENABLE,  ADC_DISABLE,
     *    ADC_ENABLE,  ADC_DISABLE,
     */
    adcConfig( ADC_ENABLE ); /* ADC */
    dacConfig( DAC_ENABLE ); /* DAC */

    /* Buffer */
    static char uartBuff[4];

    /* Variable para almacenar el valor leido del ADC CH0 */
    uint16_t muestra = 0;

    /* ------------- REPETIR POR SIEMPRE ------------- */
    while(1) {

          /* Leer la Entrada Analogica ADC0-CH0 */
          muestra = adcRead( CH0 );

          /* Enviar la primer parte del mnesaje a la UART3 */
          uartWriteString( UART_3, "ADC CH0 value: " );

          /* Conversión de muestra entera a ascii con base decimal */
          itoa( muestra, uartBuff, 10 ); /* 10 significa decimal */

          /* Enviar la muestra y Enter */
          uartWriteString( UART_3, uartBuff );
          uartWriteString( UART_3, ";\r\n" );

          delay_ms(100);
          /* Escribo la muestra en la Salida Analogica AOUT- DAC */
          dacWrite( DAC, muestra );


          if (muestra < 2056){
        	  gpioWrite( 0, 22, LOW);
          }
          else {
        	  gpioWrite( 0, 22, HIGH );
          }


    }

    /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es
     llamado por ningun S.O. */
    return 0 ;
 }



/* ***************************************************************** */
/* File name:        board.h                                         */
/* File description: Header file containing the peripherals mapping  */
/*                     of the peripheral board for the ES670 hardware*/
/*                                                                   */
/* Author name:      Rodrigo M Bacurau                               */
/* Creation date:    26fev2020                                       */
/* Revision date:    02mar2020                                       */
/* ***************************************************************** */

#ifndef SOURCES_BOARD_H_
#define SOURCES_BOARD_H_

/* system includes */
#include <MKL25Z4.h>

/* FDRMKL25Z RGB LED pins defintions */
#define RED_LED_PORT_BASE_PNT    PORTB /* peripheral port base pointer */
#define RED_LED_GPIO_BASE_PNT    PTB   /* peripheral gpio base pointer */
#define RED_LED_PIN		         (uint32_t) 18u
#define GREEN_LED_PORT_BASE_PNT  PORTB /* peripheral port base pointer */
#define GREEN_LED_GPIO_BASE_PNT  PTB   /* peripheral gpio base pointer */
#define GREEN_LED_PIN	         (uint32_t) 19u
#define BLUE_LED_PORT_BASE_PNT   PORTD /* peripheral port base pointer */
#define BLUE_LED_GPIO_BASE_PNT   PTD   /* peripheral gpio base pointer */
#define BLUE_LED_PIN	         (uint32_t) 1u


/* Configuração dos set-up necessários para utilizar os Led/Switch 
*  INICIO 
*/ 
#define uiPort1MaskEnable       0x02
#define uiPort1MaskDisable      0xFFFD
#define uiPort2MaskEnable       0x04
#define uiPort2MaskDisable      0xFFFB
#define uiPort4MaskEnable       0x010
#define uiPort4MaskDisable      0xFFEF
#define uiPort5MaskEnable       0x020
#define uiPort5MaskDisable      0xFFDF
#define uiSetPinAsGPIO			0x100
#define uiSetClockPort			0x0200

/* FIM das configurações dos set-up de Led/Switch*/




/* Configuração dos set-up para utilziar o LCD
 *
 * Quando LCD_RS = LCD_RS_HIGH => Registrador de dados é selecionados
 * Quando (LCD_RS = LCD_RS_LOW => Registrador de instruções é selecionado.
 */

#define LCD_PORT_BASE_PNT        PORTC
#define LCD_GPIO_BASE_PNT        PTC

#define LCD_RS_PIN               8U
#define LCD_RS_DIR				 kGpioDigitalOutput
#define LCD_RS_ALT				 kPortMuxAsGpio

#define LCD_ENABLE_PIN			 9U
#define LCD_ENABLE_DIR			 kGipioDigitalOutput
#define LCD_ENABLE_ALT			 kPortMuxAsGpio

#define LCD_RS_HIGH				 1U
#define LCD_RS_DATA				 LCD_RS_HIGH

#define LCD_RS_LOW				 0U
#define LCD_RS_CMD				 LCD_RS_LOW

#define LCD_ENABLED				 1U
#define LCD_DISABLED			 0U

#define LCD_DATA_DIR			 kGpioDigitalOutput
#define LCD_DATA_ALT			 kPortMuxAsGpio

#define LCD_DATA_DB0_PIN		 0U
#define LCD_DATA_DB1_PIN		 1U
#define LCD_DATA_DB2_PIN		 2U
#define LCD_DATA_DB3_PIN		 3U
#define LCD_DATA_DB4_PIN		 4U
#define LCD_DATA_DB5_PIN		 5U
#define LCD_DATA_DB6_PIN		 6U
#define LCD_DATA_DB7_PIN		 7U

/* Final das definições do LCD para a placa */





#endif /* SOURCES_BOARD_H_ */

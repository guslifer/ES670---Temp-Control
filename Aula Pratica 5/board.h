/* ************************************************************************ */
/*                                                                          */
/*   Nome do arquivo:        board.h                                        */
/*                                                                          */
/*   Descrição:              Arquivo header contendo as definicoes de       */
/*                           pinos e mascaras utilizadas durante o          */
/*                           projeto                                        */
/*                                                                          */
/*   Autores:                Gustavo Lino e Giácomo Dollevedo               */
/*   Criado em:              31/03/2020                                     */
/*   Ultima revisão em:      03/04/2020                                     */
/* ************************************************************************ */


#ifndef SOURCES_BOARD_H_
#define SOURCES_BOARD_H_

/* system includes */
#include <MKL25Z4.h>

/* FDRMKL25Z RGB LED pins defintions */
#define RED_LED_PORT_BASE_PNT    PORTB /* peripheral port base pointer */
#define RED_LED_GPIO_BASE_PNT    PTB   /* peripheral gpio base pointer */
#define RED_LED_PIN              (uint32_t) 18u
#define GREEN_LED_PORT_BASE_PNT  PORTB /* peripheral port base pointer */
#define GREEN_LED_GPIO_BASE_PNT  PTB   /* peripheral gpio base pointer */
#define GREEN_LED_PIN            (uint32_t) 19u
#define BLUE_LED_PORT_BASE_PNT   PORTD /* peripheral port base pointer */
#define BLUE_LED_GPIO_BASE_PNT   PTD   /* peripheral gpio base pointer */
#define BLUE_LED_PIN             (uint32_t) 1u



/*Mascaras de ativação de pinos de portas como saída ou entrada*/

#define uiPin0MaskEnable       0x01
#define uiPin0MaskDisable      0xFFFFFFFE
#define uiPin1MaskEnable       0x02
#define uiPin1MaskDisable      0xFFFFFFFD
#define uiPin2MaskEnable       0x04
#define uiPin2MaskDisable      0xFFFFFFFB
#define uiPin3MaskEnable       0x08
#define uiPin3MaskDisable      0xFFFFFFF7

#define uiPin4MaskEnable       0x010
#define uiPin4MaskDisable      0xFFFFFFEF
#define uiPin5MaskEnable       0x020
#define uiPin5MaskDisable      0xFFFFFFDF
#define uiPin6MaskEnable       0x040
#define uiPin6MaskDisable      0xFFFFFFBF
#define uiPin7MaskEnable       0x080
#define uiPin7MaskDisable      0xFFFFFF7F

#define uiPin8MaskEnable       0x100
#define uiPin8MaskDisable      0xFFFFFEFF
#define uiPin9MaskEnable       0x200
#define uiPin9MaskDisable      0xFFFFFDFF


#define uiSetPinAsGPIO         0x100
#define uiSetClockPort         0x0200



/* Configuração dos set-up para utilziar o LCD
 *
 * Quando LCD_RS = LCD_RS_HIGH => Registrador de dados é selecionados
 * Quando (LCD_RS = LCD_RS_LOW => Registrador de instruções é selecionado.
 */

#define uiSetClockPortC          0x0800
#define LCD_GPIO_BASE_PNT        PTC

#define LCD_RS_PIN               8U
#define LCD_RS_DIR               kGpioDigitalOutput
#define LCD_RS_ALT               kPortMuxAsGpio

#define LCD_ENABLE_DIR           kGipioDigitalOutput
#define LCD_ENABLE_ALT           kPortMuxAsGpio

#define LCD_RS_HIGH              0x0100
#define LCD_RS_DATA              LCD_RS_HIGH

#define LCD_RS_LOW               0x0000
#define LCD_RS_CMD               LCD_RS_LOW

#define LCD_ENABLED              uiPin9MaskEnable
#define LCD_DISABLED             uiPin9MaskDisable

#define LCD_DATA_DIR             kGpioDigitalOutput
#define LCD_DATA_ALT             kPortMuxAsGpio

#define LCD_DATA_DB0_PIN         0U
#define LCD_DATA_DB1_PIN         1U
#define LCD_DATA_DB2_PIN         2U
#define LCD_DATA_DB3_PIN         3U
#define LCD_DATA_DB4_PIN         4U
#define LCD_DATA_DB5_PIN         5U
#define LCD_DATA_DB6_PIN         6U
#define LCD_DATA_DB7_PIN         7U

/* Configuracao dos setups para utilizar o D7S*/

#define D7S_GPIO_CONFIG 		 0x3CFF

/* Final das definições do LCD para a placa */





#endif /* SOURCES_BOARD_H_ */
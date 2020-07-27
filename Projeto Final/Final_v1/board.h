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
/*   Ultima revisão em:      03/06/2020                                     */
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

/*CLOCK PORT ENABLE*/ 
#define PORTA_CLOCK_GATE	   0x0200
#define PORTB_CLOCK_GATE       0x0400
#define PORTC_CLOCK_GATE       0x0800
#define PORTD_CLOCK_GATE       0x1000
#define PORTE_CLOCK_GATE       0x2000

#define MUX_ALT3				0x300
#define MUX_ALT4				0x400


/* Configuração dos set-up para utilziar o LCD
 *
 * Quando LCD_RS = LCD_RS_HIGH => Registrador de dados é selecionados
 * Quando (LCD_RS = LCD_RS_LOW => Registrador de instruções é selecionado.
 */


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

#define LCD_RS_WAITING			 0xFFFFEFF	

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

/* formato letras display 7 seg */
/*  DP    g    f    e   d   c   b   a*/

#define DISP_0      0x003F
#define DISP_1      0x0006
#define DISP_2      0x005B
#define DISP_3      0x004F
#define DISP_4      0x0066 
#define DISP_5      0x006D
#define DISP_6      0x007D
#define DISP_7      0x0007
#define DISP_8      0x007F
#define DISP_9      0x006F
#define DISP_A      0x0077
#define DISP_B      0x007C
#define DISP_C      0x0039
#define DISP_D      0x005E
#define DISP_E      0x0079
#define DISP_F      0x0071
#define DISP_DP     0x0080
#define DISP_CLEAR  0xFFFFFF00
#define DISP_ALL    0x00FF

/* Final das definições do LCD para a placa */

/* Configuracao dos setups para utilizar o Timer/PWM*/

#define TPM1_CLOCK_GATE 		0x2000000

#define MCGIRCLK_SELECT			0x3000000


#define PWM_EVERY_CLOCK 		0x08



/* Final das definições do LCD para a placa */

/*Configuração dos set-ups para utilziar o Tacometro*/ 
#define SET_LTPMR0			 	0X01
#define TPM_EXTERNAL_CLOCK		0x10
#define TPM_MAX_VALUE_COUNT		0x0FFFF
#define TPM0CLKSEL_AS_CLKIN1	0x01000000

/*                 TEMPERATURE SENSOR DIODE DEFINITIONS           */

#define  THERMOMETER_PORT_BASE_PNT  PORTE                         /* peripheral port base pointer */
#define  THERMOMETER_GPIO_BASE_PNT  PTE                           /* peripheral gpio base pointer */
#define  THERMOMETER_PIN            21U                           /* thermometer pin */
#define  THERMOMETER_DIR            (GPIO_INPUT << TERMOMETER_PIN)
#define  THERMOMETER_ALT            0x00u

/*                 END OF TEMPERATURE SENSOR DIODE DEFINITIONS    */


/* REVISAO PWM - AULA 12 */

#define DISABLE_COUNTER			0xFFFFFFE7
#define PWM_UP_COUNTING			0xFFFFFFDF
#define EDGE_ALIGNED_HIGH_TRUE 	0xFFFFFFAB
#define CLEAR_16				0xFFFF0000

#define CLOCK_DIVIDER_1 		0x1F8
#define CLOCK_DIVIDER_2 		0x1F9
#define CLOCK_DIVIDER_4 		0x1FA
#define CLOCK_DIVIDER_8 		0x1FB
#define CLOCK_DIVIDER_16 		0x1FC
#define CLOCK_DIVIDER_32		0x1FD
#define CLOCK_DIVIDER_64		0x1FE
#define CLOCK_DIVIDER_128 		0x1FF

/* REVISAO TACOMETRO - AULA 14 */

#define TPM0_CLOCK_GATE 		0x800000
#define TPM0CLKSEL_AS_CLKIN0 	0xFEFFFFFF


#endif /* SOURCES_BOARD_H_ */
/* ***************************************************************** */
/* File name:        lcd.c                                           */
/* File description: File dedicated to the hardware abstraction layer*/
/*                   related to the LCD HARDWARE based on the KS006U */
/*                   controller                                      */
/* Author name:      dloubach, Gustavo L. Fernandes, 				 */
/*					 Giácomo A. Dollevedo                            */
/* Creation date:    16out2015                                       */
/* Revision date:    04abr2020                                       */
/* ***************************************************************** */

#include "lcd.h"
#include "KL25Z/es670_peripheral_board.h"
#include "Util/util.h"

/* system includes */
#include "fsl_clock_manager.h"
#include "fsl_port_hal.h"
#include "fsl_gpio_hal.h"

/* line and columns */
#define LINE0        0U
#define COLUMN0        0U

#define L0C0_BASE    0x80 /* line 0, column 0 */
#define L1C0_BASE    0xC0 /* line 1, column 0 */
#define MAX_COLUMN  15U

/* ************************************************ */
/* Method name:        lcd_initLcd                  */
/* Method description: Initialize the LCD function  */
/* Input params:       n/a                          */
/* Output params:       n/a                         */
/* ************************************************ */

/* Pinos de controle do dispositivo LCD estão		*/
/* conectados na porta C, de 0 a 9					*/
void lcd_initLcd(void)
{
    /* pins configured as outputs */

    /* un-gate port clock*/
    SIM_SCGC5 |= uiSetClockPortC;

    /* set pin as gpio */
    PORTC_PCR0 |= uiSetPinAsGPIO;
 	PORTC_PCR1 |= uiSetPinAsGPIO; 
    PORTC_PCR2 |= uiSetPinAsGPIO; 
    PORTC_PCR3 |= uiSetPinAsGPIO; 
    PORTC_PCR4 |= uiSetPinAsGPIO;
    PORTC_PCR5 |= uiSetPinAsGPIO;
    PORTC_PCR6 |= uiSetPinAsGPIO;
    PORTC_PCR7 |= uiSetPinAsGPIO;
    PORTC_PCR8 |= uiSetPinAsGPIO;
    PORTC_PCR9 |= uiSetPinAsGPIO;
   

    /* set pin as digital output */

    GPIOC_PDDR |= uiPin0MaskEnable;
    GPIOC_PDDR |= uiPin1MaskEnable;
    GPIOC_PDDR |= uiPin2MaskEnable;
    GPIOC_PDDR |= uiPin4MaskEnable;
    GPIOC_PDDR |= uiPin5MaskEnable;
    GPIOC_PDDR |= uiPin6MaskEnable;
    GPIOC_PDDR |= uiPin7MaskEnable;
    GPIOC_PDDR |= uiPin8MaskEnable;
    GPIOC_PDDR |= uiPin9MaskEnable;


    // turn-on LCD, with no cursor and no blink
    lcd_sendCommand(CMD_NO_CUR_NO_BLINK);

    // init LCD
    lcd_sendCommand(CMD_INIT_LCD);

    // clear LCD
    lcd_sendCommand(CMD_CLEAR);

    // LCD with no cursor
    lcd_sendCommand(CMD_NO_CURSOR);

    // cursor shift to right
    lcd_sendCommand(CMD_CURSOR2R);

}



/* ************************************************ */
/* Method name:        lcd_write2Lcd                */
/* Method description: Send command or data to LCD  */
/* Input params:       ucBuffer => char to be send  */
/*                     cDataType=>command LCD_RS_CMD*/
/*                     or data LCD_RS_DATA          */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_write2Lcd(unsigned char ucBuffer,  unsigned char cDataType)
{
    /* writing data or command */
    if(LCD_RS_CMD == cDataType)
        /* will send a command */
        GPIO_HAL_WritePinOutput(LCD_GPIO_BASE_PNT, LCD_RS_PIN, LCD_RS_CMD);
    else
        /* will send data */
        GPIO_HAL_WritePinOutput(LCD_GPIO_BASE_PNT, LCD_RS_PIN, LCD_RS_DATA);

    /* write in the LCD bus */

    GPIOC_PSOR |= ((ucBuffer & (1u << 0u)) >> 0u);
    GPIOC_PSOR |= ((ucBuffer & (1u << 1u)) >> 1u);
    GPIOC_PSOR |= ((ucBuffer & (1u << 2u)) >> 2u);
    GPIOC_PSOR |= ((ucBuffer & (1u << 3u)) >> 3u);
    GPIOC_PSOR |= ((ucBuffer & (1u << 4u)) >> 4u);
    GPIOC_PSOR |= ((ucBuffer & (1u << 5u)) >> 5u);
    GPIOC_PSOR |= ((ucBuffer & (1u << 6u)) >> 6u);
    GPIOC_PSOR |= ((ucBuffer & (1u << 7u)) >> 7u);

    /* enable, delay, disable LCD */
    /* this generates a pulse in the enable pin */

	GPIOA_PSOR |= LCD_ENABLED;
    util_genDelay1ms();
    GPIOA_PSOR |= LCD_DISABLED;
    util_genDelay1ms();
    util_genDelay1ms();
}



/* ************************************************ */
/* Method name:        lcd_writeData                */
/* Method description: Write data to be displayed   */
/* Input params:       ucData => char to be written */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_writeData(unsigned char ucData)
{
    /* just a relay to send data */
    lcd_write2Lcd(ucData, LCD_RS_DATA);
}



/* ************************************************ */
/* Method name:        lcd_sendCommand              */
/* Method description: Write command to LCD         */
/* Input params:       ucCmd=>command to be executed*/
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_sendCommand(unsigned char ucCmd)
{
    /* just a relay to send command */
    lcd_write2Lcd(ucCmd, LCD_RS_CMD);
}



/* ************************************************ */
/* Method name:        lcd_setCursor                */
/* Method description: Set cursor line and column   */
/* Input params:       cLine = LINE0..LINE1         */
/*                     cColumn = COLUMN0..MAX_COLUMN*/
/* Output params:       n/a                         */
/* ************************************************ */
void lcd_setCursor(unsigned char cLine, unsigned char cColumn)
{
    char cCommand;

    if(LINE0 == cLine)
        /* line 0 */
        cCommand = L0C0_BASE;
    else
        /* line 1 */
        cCommand = L1C0_BASE;

    /* maximum MAX_COLUMN columns */
    cCommand += (cColumn & MAX_COLUMN);

    // send the command to set the cursor
    lcd_sendCommand(cCommand);
}



/* ************************************************ */
/* Method name:        lcd_writeString              */
/* Method description: Write string to be displayed */
/* Input params:       cBuffer => string to be      */
/*                     written in LCD               */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_writeString(const char *cBuffer)
{
    while(*cBuffer)
    {
        lcd_writeData(*cBuffer++);
    };
}



/* ************************************************ */
/* Method name:        lcd_dummyText                */
/* Method description: Write a dummy hard coded text*/
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_dummyText(void)
{
    // clear LCD
    lcd_sendCommand(CMD_CLEAR);

    // set the cursor line 0, column 1
    lcd_setCursor(0,1);

    // send string
    lcd_writeString("*** ES670 ***");

    // set the cursor line 1, column 0
    lcd_setCursor(1,0);
    lcd_writeString("Prj Sis Embarcad");
}


/* ************************************************ */
/* Method name:        lcd_writeString              */
/* Method description: Write string to be displayed */
/* Input params:       cBuffer => string to be      */
/*                     written in LCD               */
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_writeString(const char *cBuffer)
{
    while(*cBuffer)
    {
        lcd_writeData(*cBuffer++);
    };
}

/* ************************************************ */
/* Method name:        lcd_writeText                */
/* Method description: Escreve um texto específico	*/
/*					   em uma das duas linhas do lcd*/
/* Input params:       cBuffer: Texto a ser inserido*/ 
/*					   linha: cLine = LINE0..LINE1   */
/*					   específica a linha 			*/
/* Output params:      n/a                          */
/* ************************************************ */
void lcd_writeText(unsigned char cBuffer, unsigned char cLine);
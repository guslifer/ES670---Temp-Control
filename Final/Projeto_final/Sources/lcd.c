/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        lcd.c                                                  */
/*                                                                                  */
/*   Descricao:             Arquivo contendo as implementacoes das funcoes          */
/*                          necessarias para a interface do LCD com o kit           */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo Dollevedo                       */
/*   Criado em:              07/04/2020                                             */
/*   Ultima revisao em:      31/07/2020                                             */
/* ******************************************************************************** */

/*Correções implementadas: Pino 3 da GPIO não setado resolvido setando  do Pino 3 como GPIO 
na função lcd_initLcd; 
No comando "GPIOC_PDOR |= LCD_RS_CMD;" poderia ser considerado valores anteriores, resolvido 
zerando a saida da porta C responsável pelo pino RS ao entrar  na função lcd_write2Lcd
inserido na board.h a constante LCD_RS_WAINTG; 
Não é alocado memória para a strings usada, resolvido dando malloc.
*/

#include "lcd.h"
#include "board.h"

/* Bibliotecas da linguagem */ 

#include <string.h>


/* line and columns */
#define LINE0        0U
#define LINE1        1U

#define COLUMN0      0U

#define L0C0_BASE    0x80 /* line 0, column 0 */
#define L1C0_BASE    0xC0 /* line 1, column 0 */
#define MAX_COLUMN   15U

/* ******************************************************************************** */
/* Nome do metodo:          lcd_initLcd                                             */ 
/* Descricao:               Inicializa as funcoes do LCD                            */
/*                                                                                  */
/* Parametros de entrada:   n/a                                                     */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_initLcd(void)
{
    /* pins configured as outputs */

    /* un-gate port clock*/
    SIM_SCGC5 |= PORTC_CLOCK_GATE;
    

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
    GPIOC_PDDR |= uiPin3MaskEnable;
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



/* ******************************************************************************** */
/* Nome do metodo:          lcd_write2Lcd                                           */ 
/* Descricao:               Escreve caracter no LCD                                 */
/*                                                                                  */
/* Parametros de entrada:   ucBuffer    -> char do dado que sera enviado            */
/*                          cDataType   -> commando (LCD_RS_CMD) ou dado            */
/*                                         (LCD_RS_DATA)                            */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_write2Lcd(unsigned char ucBuffer,  unsigned char cDataType)
{   
    //Vamos colocar apenas o pino RS como indefinido (em zero)
    GPIOC_PDOR &= LCD_RS_WAITING;

    /* writing data or command */
    if(LCD_RS_CMD == cDataType)
        /* will send a command */
        GPIOC_PDOR |= LCD_RS_CMD;
    else
        /* will send data */
        GPIOC_PDOR |= LCD_RS_DATA;

    /*Zera as portas de dados que sera utilizada e insere o valor binario do caracter*/
    GPIOC_PDOR &= 0xFFFFFF00;
    GPIOC_PDOR |= ucBuffer;

    /* enable, delay, disable LCD */
    /* this generates a pulse in the enable pin */

    GPIOA_PDOR |= LCD_ENABLED;
    util_genDelay1ms();
    GPIOA_PDOR &= LCD_DISABLED;
    //util_genDelay1ms();
    //util_genDelay1ms();
}



/* ******************************************************************************** */
/* Nome do metodo:          lcd_writeData                                           */ 
/* Descricao:               Escreve um dado no LCD                                  */
/*                                                                                  */
/* Parametros de entrada:   Um unsigned char que serÃƒÂ¡ escrito                    */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_writeData(unsigned char ucData)
{
    /* just a relay to send data */
    lcd_write2Lcd(ucData, LCD_RS_DATA);
}



/* ******************************************************************************** */
/* Nome do metodo:          lcd_sendCommand                                         */ 
/* Descricao:               Escreve um comando no LCD                               */
/*                                                                                  */
/* Parametros de entrada:   Um unsigned char descrevendo o comando que sera feito   */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_sendCommand(unsigned char ucCmd)
{
    /* just a relay to send command */
    lcd_write2Lcd(ucCmd, LCD_RS_CMD);
}



/* ******************************************************************************** */
/* Nome do metodo:          lcd_setCursor                                           */ 
/* Descricao:               Move o cursor no LCD para uma posicao especifica        */
/*                                                                                  */
/* Parametros de entrada:   Dois unsigned char, contendo a linha (cLine) e coluna   */
/*                          (cColumn) para onde o cursor sera movido no display     */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
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


/* ******************************************************************************** */
/* Nome do metodo:          lcd_dummyText                                           */ 
/* Descricao:               Escreve um texto padrao no LCD                          */
/*                                                                                  */
/* Parametros de entrada:   n/a                                                     */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_dummyText(void)
{
    // clear LCD
    lcd_sendCommand(CMD_CLEAR);

    // set the cursor line 0, column 1
    lcd_setCursor(LINE0,1);

    // send string
    lcd_writeString("*** ES670 ***");

    // set the cursor line 1, column 0
    lcd_setCursor(1,0);
    lcd_writeString("Prj Sis Embarcad");
}


/* ******************************************************************************** */
/* Nome do metodo:          lcd_writeString                                         */ 
/* Descricao:               Escreve uma string no LCD                               */
/*                                                                                  */
/* Parametros de entrada:   Um array dinamico de char, contendo a string que sera   */
/*                          escrita                                                 */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_writeString(const char *cBuffer){
    while(*cBuffer){
        lcd_writeData(*cBuffer++);
    }
}

/* ******************************************************************************** */
/* Nome do metodo:          lcd_writeText                                           */ 
/* Descricao:               Escreve um texto especifico em uma das duas linhas      */
/*                          do LCD                                                  */
/*                                                                                  */
/* Parametros de entrada:   Uma string contendo o texto a ser escrito e um inteiro  */
/*                          indicando a linha (0 ou 1) do LCD para escrita          */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_writeText(const char *cBuffer, int iLine)
{

    int ilen = strlen(cBuffer); 
    char *cLine1, *cLine2;
    cLine1 = (char*)malloc(sizeof(char) * 16);
    cLine2 = (char*)malloc(sizeof(char) * 16);
    // clear LCD
    lcd_sendCommand(CMD_CLEAR);
    // identifica a linha desejada
    if(0 == iLine)
        lcd_setCursor(LINE0,1);
    else
        lcd_setCursor(LINE1,1);

    // send string


    if(ilen < 17){ 
        lcd_writeString(cBuffer);
    }

    else if(ilen < 37){ 
        strncpy(cLine1, cBuffer, 16);
        strcpy(cLine2, &cBuffer[17]);
        lcd_writeString(cLine1);

        lcd_setCursor(LINE1,1);
        lcd_writeString(cLine1);

    }

    else{ 
        lcd_setCursor(LINE0,1);
        lcd_writeString("Too Many Car");

    }


}

/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        lcd.h                                                  */
/*                                                                                  */
/*   Descrição:              Arquivo Header contendo a declaração                   */
/*                           das funções de interface do microcontrolador           */
/*                           com o LCD do kit                                       */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giácomo Dollevedo                       */
/*   Criado em:              07/04/2020                                             */
/*   Ultima revisão em:      09/04/2020                                             */
/* ******************************************************************************** */

#ifndef SOURCES_LCD_H_
#define SOURCES_LCD_H_

/* lcd basic commands list */
#define CMD_INIT_LCD        0x0F
#define CMD_CLEAR           0x01
#define CMD_NO_CURSOR       0x0C
#define CMD_CURSOR2R        0x06 /* cursor to right */
#define CMD_NO_CUR_NO_BLINK 0x38 /* no cursor, no blink */


/* ******************************************************************************** */
/* Nome do metodo:          lcd_initLcd                                             */ 
/* Descrição:               Envia um comando ou dado para o LCD                     */
/*                                                                                  */
/* Parametros de entrada:   ucBuffer    -> char do dado que sera enviado            */
/*                          cDataType   -> commando (LCD_RS_CMD) ou dado            */
/*                                         (LCD_RS_DATA)                            */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_initLcd(void);


/* ******************************************************************************** */
/* Nome do metodo:          lcd_write2Lcd                                           */ 
/* Descrição:               Inicializa as funcoes do LCD                            */
/*                                                                                  */
/* Parametros de entrada:   n/a                                                     */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_write2Lcd(unsigned char ucBuffer,  unsigned char cDataType)


/* ******************************************************************************** */
/* Nome do metodo:          lcd_writeData                                           */ 
/* Descrição:               Escreve um dado no LCD                                  */
/*                                                                                  */
/* Parametros de entrada:   Um unsigned char que será escrito                       */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_writeData(unsigned char ucData);


/* ******************************************************************************** */
/* Nome do metodo:          lcd_sendCommand                                         */ 
/* Descrição:               Escreve um comando no LCD                               */
/*                                                                                  */
/* Parametros de entrada:   Um unsigned char descrevendo o comando que será feito   */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_sendCommand(unsigned char ucCmd);


/* ******************************************************************************** */
/* Nome do metodo:          lcd_writeString                                         */ 
/* Descrição:               Escreve uma string no LCD                               */
/*                                                                                  */
/* Parametros de entrada:   Um array dinamico de char, contendo a string que sera   */
/*                          escrita                                                 */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_writeString(const char *cBuffer);


/* ******************************************************************************** */
/* Nome do metodo:          lcd_setCursor                                           */ 
/* Descrição:               Move o cursor no LCD para uma posicao especifica        */
/*                                                                                  */
/* Parametros de entrada:   Dois unsigned char, contendo a linha (cLine) e coluna   */
/*                          (cColumn) para onde o cursor sera movido no display     */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_setCursor(unsigned char cLine, unsigned char cColumn);


/* ******************************************************************************** */
/* Nome do metodo:          lcd_dummyText                                           */ 
/* Descrição:               Escreve um texto padrão no LCD                          */
/*                                                                                  */
/* Parametros de entrada:   n/a                                                     */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_dummyText(void);


/* ******************************************************************************** */
/* Nome do metodo:          lcd_writeText                                           */ 
/* Descrição:               Escreve um texto específico em uma das duas linhas      */
/*                          do LCD                                                  */
/*                                                                                  */
/* Parametros de entrada:   Uma string contendo o texto a ser escrito e um char     */
/*                          indicando a linha (0 ou 1) do LCD para escrita          */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_writeText(const char *cBuffer, unsigned char cLine);

#endif /* SOURCES_LCD_H_ */

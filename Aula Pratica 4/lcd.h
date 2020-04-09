/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        lcd.h                                                  */
/*                                                                                  */
/*   DescriÃ§Ã£o:              Arquivo Header contendo a declaraÃ§Ã£o                   */
/*                           das funÃ§Ãµes de interface do microcontrolador           */
/*                           com o LCD do kit                                       */
/*                                                                                  */
/*   Autores:                Gustavo Lino e GiÃ¡como Dollevedo                       */
/*   Criado em:              07/04/2020                                             */
/*   Ultima revisÃ£o em:      09/04/2020                                             */
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
/* DescriÃ§Ã£o:               Envia um comando ou dado para o LCD                     */
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
/* DescriÃ§Ã£o:               Inicializa as funcoes do LCD                            */
/*                                                                                  */
/* Parametros de entrada:   n/a                                                     */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_write2Lcd(unsigned char ucBuffer,  unsigned char cDataType);


/* ******************************************************************************** */
/* Nome do metodo:          lcd_writeData                                           */ 
/* DescriÃ§Ã£o:               Escreve um dado no LCD                                  */
/*                                                                                  */
/* Parametros de entrada:   Um unsigned char que serÃ¡ escrito                       */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_writeData(unsigned char ucData);


/* ******************************************************************************** */
/* Nome do metodo:          lcd_sendCommand                                         */ 
/* DescriÃ§Ã£o:               Escreve um comando no LCD                             */
/*                                                                                  */
/* Parametros de entrada:   Um unsigned char descrevendo o comando que serÃ¡ feito  */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_sendCommand(unsigned char ucCmd);


/* ******************************************************************************** */
/* Nome do metodo:          lcd_writeString                                         */ 
/* DescriÃ§Ã£o:               Escreve uma string no LCD                               */
/*                                                                                  */
/* Parametros de entrada:   Um array dinamico de char, contendo a string que sera   */
/*                          escrita                                                 */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_writeString(const char *cBuffer);


/* ******************************************************************************** */
/* Nome do metodo:          lcd_setCursor                                           */ 
/* DescriÃ§Ã£o:               Move o cursor no LCD para uma posicao especifica        */
/*                                                                                  */
/* Parametros de entrada:   Dois unsigned char, contendo a linha (cLine) e coluna   */
/*                          (cColumn) para onde o cursor sera movido no display     */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_setCursor(unsigned char cLine, unsigned char cColumn);


/* ******************************************************************************** */
/* Nome do metodo:          lcd_dummyText                                           */ 
/* DescriÃ§Ã£o:               Escreve um texto padrÃ£o no LCD                          */
/*                                                                                  */
/* Parametros de entrada:   n/a                                                     */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_dummyText(void);


/* ******************************************************************************** */
/* Nome do metodo:          lcd_writeText                                           */ 
/* DescriÃ§Ã£o:               Escreve um texto especÃ­fico em uma das duas linhas      */
/*                          do LCD                                                  */
/*                                                                                  */
/* Parametros de entrada:   Uma string contendo o texto a ser escrito e um inteiro  */
/*                          indicando a linha (0 ou 1) do LCD para escrita          */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcd_writeText(unsigned char *cBuffer, int iLine);

#endif /* SOURCES_LCD_H_ */

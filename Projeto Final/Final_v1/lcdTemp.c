/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:       lcdTemp.c                                               */
/*                                                                                  */
/*   Descricao:             Funcoes para operar o LCD uteis no contexto do projeto  */
/*	 						do controlador de temperatura 							*/
/*                                                                                  */
/*   Autores:               Gustavo Lino e Giacomo A. Dollevedo                    */
/*   Criado em:             28/07/2020                                             */
/*   Ultima revisao em:     28/07/2020                                             */
/* ******************************************************************************** */

/* Incluindo bibliotecas */
#include "lcd.h"


/* ******************************************************************************** */
/* Nome do metodo:          lcdTemp_init                                            */ 
/* Descricao:               Inicializa as funcoes do LCD                            */
/*                                                                                  */
/* Parametros de entrada:   n/a                                                     */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcdTemp_init(void){

	lcd_initLcd();

}


/* **************************************************************************** */
/* Nome do metodo:          showLCDdisp                                         */
/* Descricao:               Realiza a troca de mensagem no LCD de acordo com    */
/*                          estado                                              */
/*                                                                              */
/* Parametros de entrada:   unsigned char ucFrame -> Indica o frame que sera    */
/*                          mostrado                                            */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
void showLCDdisp(unsigned char ucFrame){

    switch(ucFrame){
    case 0:
        /*Nada*/
        break;

    case 1:
        lcd_setCursor(LINE0,0);
        lcd_writeString("Configure a Temp");
        lcd_setCursor(LINE1,0);
        lcd_writeString("Temp Alvo: 00C");
        break;

     case 2:
        lcd_setCursor(LINE0,0);
        lcd_writeString("UART HABILITADO");
        lcd_setCursor(LINE1,0);
        lcd_writeString("Temp Alvo:   C");
        break;

     default:
         break;
    }

}


/* **************************************************************************** */
/* Nome do metodo:          attTempAlvo                                         */
/* Descricao:               Atualiza o display com a temperatura desejada       */
/*                                                                              */
/* Parametros de entrada:   unsigned char ucDezena -> Indica a dezena da temp.  */
/*                          alvo                                           	 	*/
/* 							unsigned char ucUnidade -> Indica a unidade da temp.*/
/*							alvo 												*/
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
void attTempAlvo(unsigned char ucDezena, unsigned char ucUnidade){

	    lcd_setCursor(LINE1,11);
        lcd_writeData(ucDezena+48);
        lcd_setCursor(LINE1,12);
        lcd_writeData(ucUnidade+48);

}
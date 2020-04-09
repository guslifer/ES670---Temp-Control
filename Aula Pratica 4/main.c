/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        main.c                                                 */
/*                                                                                  */
/*   Descrição:              Arquivo main para teste das funcoes implementadas      */
/*                           para interfacear o microcontrolador com o LCD          */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giácomo Dollevedo                       */
/*   Criado em:              08/04/2020                                             */
/*   Ultima revisão em:      09/04/2020                                             */
/* ******************************************************************************** */

/* Incluindo bibliotecas */
#include "board.h"  
#include "lcd.h"
#include "ledSwi.h"


/* Variaveis globais */

/* Strings para testar display LCD */
static unsigned char ucLcdText1[32]  = "Funcionou!"; 
static unsigned char ucLcdText2[32]  = "microcomputador tem 15 letras!";

/* **************************************************************************** */
/* Nome do metodo:          boardInit                                           */
/* Descrição:               Inicializa os parametros necessarios para o         */
/*                          teste                                               */
/*                                                                              */
/* Parametros de entrada:   n/a                                                 */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
void boardInit(void)
{
    /* inicializando o LCD */
    lcd_initLcd();

    /* inicializando as entradas e saidas */
    ledSwi_init(false, false, false, true);
}



/* **************************************************************************** */
/* Nome do metodo:          main                                                */
/* Descrição:               Executa um teste de cada funcao implementada em     */
/*                          "lcd", combinando as entradas de botoes e LEDs      */
/*                                                                              */
/* Parametros de entrada:   n/a                                                 */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
int main(void)
{
    /* executando rotina de inicializacao */
    boardInit();

    /* acendendo o LED 4 do kit para referencia */
    writeLED(4, true);

    /* escrevendo o texto padrao no lcd */
    lcd_dummyText();

    /* main loop */
    while (1){

        if(true == readSwitch(1)){
            toggleLED(4);
            lcd_writeText(ucLcdText1, 1);
        }

        if(true == readSwitch(2)){
            toggleLED(4);
            lcd_writeText(ucLcdText2, 0);
        }


        /* Este botao envia o comando de "clear" para o LCD */
        if (true == readSwitch(3)){
            toggleLED(4);
            lcd_sendCommand(CMD_CLEAR);

        }

}

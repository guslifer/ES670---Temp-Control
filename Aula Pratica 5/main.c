/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        main.c                                                 */
/*                                                                                  */
/*   DescriÃƒÂ§ÃƒÂ£o:        Arquivo main para teste das funcoes implementadas      */
/*                           para interfacear o microcontrolador com o D7S          */
/*                                                                                  */
/*   Autores:                Gustavo Lino e GiÃƒÂ¡como Dollevedo                    */
/*   Criado em:              14/04/2020                                             */
/*   Ultima revisÃƒÂ£o em:   14/04/2020                                             */
/* ******************************************************************************** */

/* Incluindo bibliotecas */
#include "board.h"  
#include "lcd.h"
#include "ledSwi.h"
#include "lptrm.h"
#include "display7seg"


/* Variaveis globais */

/* Strings para testar display LCD */
static const char ucLcdText1[32]  = "Funcionou!";
static const char ucLcdText2[32]  = "microcomputador tem 15 letras!";
unsigned int ui4ms = 4; 
bool refresh = false; 



/*configure cyclic executive interruption*/



void_d7s_segurador(void)
{
	refresh = true;
}


voidtc_installLptmr0(ui4ms, void_d7s_segurador);

/* **************************************************************************** */
/* Nome do metodo:          boardInit                                           */
/* DescriÃƒÂ§ÃƒÂ£o:               Inicializa os parametros necessarios para o         */
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
/* DescriÃƒÂ§ÃƒÂ£o:         Escreve um número de 4 digitos usando os D7S        */
/*                          utilizando as interrupções para manter visivel      */
/*                                                                              */
/* Parametros de entrada:   n/a                                                 */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
int main(void)
{
    /* executando rotina de inicializacao */
    boardInit();
    display7seg_init();

  
    int aux = 0;

    unsigned char ucCaracterD1 = 1; //milhares
    unsigned char ucCaracterD2 = 2;
    unsigned char ucCaracterD3 = 3;
    unsigned char ucCaracterD4 = 4; // unidades


// Separa cada caracter do valor desejado em uma variavel


	while(true == refresh){  //Entra assim que haver uma interrupção

		if(aux = 0){ //liga o display 1
			display7seg_writeSymbol(1, ucCaracterD1);
			aux ++; 
			refresh = false; 
		}
		if(aux = 1){ //liga o display 2
			display7seg_writeSymbol(2, ucCaracterD2);
			aux ++; 
			refresh = false; 
		}
		if(aux = 2){ //liga o display 3
			display7seg_writeSymbol(3, ucCaracterD3);
			aux ++; 
			refresh = false; 
		}
		if(aux = 3){ //liga o display 4
			display7seg_writeSymbol(4, ucCaracterD4);
			aux = 0; 
			refresh = false; 
		}
	}
}

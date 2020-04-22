/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        main.c                                                 */
/*                                                                                  */
/*   DescriÃƒÂ§ÃƒÂ£o:        Arquivo main para teste das funcoes implementadas      */
/*                           para interfacear o microcontrolador com o D7S          */
/*                                                                                  */
/*   Autores:                Gustavo Lino e GiÃƒÂ¡como Dollevedo                    */
/*   Criado em:              14/04/2020                                             */
/*   Ultima revisÃƒÂ£o em:   22/04/2020                                             */
/* ******************************************************************************** */

/* Incluindo bibliotecas */
#include "board.h"  
#include "lptmr.h"
#include "display7seg.h"


/* Variaveis globais */

/* Strings para testar display LCD */
unsigned int ui4ms = 4; 
unsigned char refresh = 0;



/*configure cyclic executive interruption*/



void d7s_segurador(void)
{
    refresh = 1;
    return;
}


void tc_installLptmr0(ui4ms, d7s_segurador);

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
    /* inicializando o D7S */
	display7seg_init();
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


  
    int aux = 0;

    unsigned char ucCaracterD1 = 1; //milhares
    unsigned char ucCaracterD2 = 2;
    unsigned char ucCaracterD3 = 3;
    unsigned char ucCaracterD4 = 4; // unidades


// Separa cada caracter do valor desejado em uma variavel

    while(1){
        while(1 == refresh){  //Entra assim que haver uma interrupção

            if(0 == aux){ //liga o display 1
                display7seg_writeSymbol(1, ucCaracterD1);
                aux ++; 
                refresh = 0;
            }
            if(1 == aux){ //liga o display 2
                display7seg_writeSymbol(2, ucCaracterD2);
                aux ++; 
                refresh = 0;
            }
            if(2 == aux){ //liga o display 3
                display7seg_writeSymbol(3, ucCaracterD3);
                aux ++; 
                refresh = 0;
            }
            if(3 == aux){ //liga o display 4
                display7seg_writeSymbol(4, ucCaracterD4);
                aux = 0; 
                refresh = 0;
            }
        }
    }
}

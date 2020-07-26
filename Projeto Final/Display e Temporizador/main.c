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

unsigned int ui4ms = 400; 
unsigned char uiDispRefresh = 0;




/*configure cyclic executive interruption*/



void d7s_segurador(void)
{
    uiDispRefresh = 1;
    return;
}


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
    tc_installLptmr0(ui4ms, d7s_segurador)
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


  
    int iActualDisp = 0;

    unsigned char ucCaracterD1 = 1; //milhares
    unsigned char ucCaracterD2 = 2;
    unsigned char ucCaracterD3 = 3;
    unsigned char ucCaracterD4 = 4; // unidades


// Separa cada caracter do valor desejado em uma variavel


    while(1){
        while(1 == uiDispRefresh){  //Entra assim que haver uma interrupção

            if(0 == iActualDisp){ //liga o display 1
                display7seg_writeSymbol(1, ucCaracterD1);
                iActualDisp ++; 
                uiDispRefresh = 0;
            }
            if(1 == iActualDisp){ //liga o display 2
                display7seg_writeSymbol(2, ucCaracterD2);
                iActualDisp ++; 
                uiDispRefresh = 0;
            }
            if(2 == iActualDisp){ //liga o display 3
                display7seg_writeSymbol(3, ucCaracterD3);
                iActualDisp ++; 
                uiDispRefresh = 0;
            }
            if(3 == iActualDisp){ //liga o display 4
                display7seg_writeSymbol(4, ucCaracterD4);
                iActualDisp = 0; 
                uiDispRefresh = 0;
            }
        }
    }
}

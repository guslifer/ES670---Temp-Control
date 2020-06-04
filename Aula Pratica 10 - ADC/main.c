/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        main.c                                                 */
/*                                                                                  */
/*   Descricao:             Arquivo main para teste das funcoes implementadas       */
/*                           para o microcontrolador utilizar o protocolo UART      */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo A. Dollevedo                	*/
/*   Criado em:              23/05/2020                                             */
/*   Ultima revisao em:   	 23/05/2020                                             */
/* ******************************************************************************** */

/* Incluindo bibliotecas */
#include "board.h"  
#include "UART.h"
#include "print_scan.h"
#include "communicationStateMachine.h"
#include "util.h"



/* **************************************************************************** */
/* Nome do metodo:          boardInit                                           */
/* Descricao:               Inicializa os parametros necessarios para o         */
/*                          teste                                               */
/*                                                                              */
/* Parametros de entrada:   n/a                                                 */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
void boardInit(void)
{
    boardInit();

    UART0_init();
    UART0_enableIRQ();

}



/* **************************************************************************** */
/* Nome do metodo:          main                                                */
/* Descricao:               Testa GET e SET da maquina de estados 				*/
/*                                                                              */
/*                                                                              */
/* Parametros de entrada:   n/a                                                 */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
int main(void){

    boardInit();

    processByteCommUART('#');
    util_genDelay100ms();

    processByteCommUART('g');
    util_genDelay100ms();

    processByteCommUART('t');
    util_genDelay100ms();

    processByteCommUART(';');
    util_genDelay100ms();

    processByteCommUART('#');
	util_genDelay100ms();

	processByteCommUART('s');
	util_genDelay100ms();

	processByteCommUART('b');
	util_genDelay100ms();

    for(unsigned char i=0; i<7; i++){
    	processByteCommUART('0');
    	util_genDelay100ms();
    }

    processByteCommUART(';');


}   

/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:       display7Temp.c                                          */
/*                                                                                  */
/*   Descricao:             Funcoes para operar o D7S uteis no contexto do projeto  */
/*	 						do controlador de temperatura 							*/
/*                                                                                  */
/*   Autores:               Gustavo Lino e Giacomo A. Dollevedo                     */
/*   Criado em:             29/07/2020                                              */
/*   Ultima revisao em:     31/07/2020                                              */
/* ******************************************************************************** */

/* Incluindo bibliotecas */
#include "display7seg.h"
#include "variaveis_globais.h"

/* ******************************************************************************** */
/* Nome do metodo:          display7Temp_init                                       */ 
/* Descricao:               Inicializa os registradores para funcionamento do D7S   */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void display7Temp_init(void){

	display7seg_init();

}


/* ******************************************************************************** */
/* Nome do metodo:          attDisp7Temp                                      		*/ 
/* Descricao:               Atualiza o D7S com a temperatura atual da resistencia   */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void attDisp7Temp(void){

    display7seg_writeSymbol(1, ucDezTempAtual);
    display7seg_writeSymbol(2, ucUnTempAtual);
    display7seg_writeSymbol(3, 20);
    display7seg_writeChar(4, 'c');

}

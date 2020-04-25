/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        main.c                                                 */
/*                                                                                  */
/*   DescriÃƒÂ§ÃƒÂ£o:        Arquivo main para teste das funcoes implementadas      */
/*                           para interfacear o microcontrolador com o D7S          */
/*                                                                                  */
/*   Autores:                Gustavo Lino e GiÃƒÂ¡como Dollevedo                    */
/*   Criado em:              25/04/2020                                             */
/*   Ultima revisÃƒÂ£o em:   25/04/2020                                             */
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
/* DescriÃƒÂ§ÃƒÂ£o:               Inicializa os parametros necessarios para o   */
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
    /* executando rotina de inicializacao:
    * Placa do microcontrolador 
    * Configuração da modulação PWM 
    * Inicialização do cooler 
    * Inicialização do aquecedor */
    boardInit();
    PWM_init();
    coolerfan_init();
    heater_init();

    float fCoolerDuty = 0.5; 
    float fHeaterDuty = 0.5; 

    /*Passa a % de tensão desejada no cooler e no aquecedor*/
    coolerfan_PWMDuty(fCoolerDuty);
    heater_PWMDuty(fHeaterDuty);

}

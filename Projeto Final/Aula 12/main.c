/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        main.c                                                 */
/*                                                                                  */
/*   Descricao:        Arquivo main para teste das funcoes implementadas      		*/
/*                           para interfacear o microcontrolador com o PWM          */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo A. Dollevedo                	*/
/*   Criado em:              25/04/2020                                             */
/*   Ultima revisao em:   	 24/07/2020                                             */
/* ******************************************************************************** */

/* Incluindo bibliotecas */
#include "board.h"  
#include "aquecedorECooler.h"

void boardInit(void)
{
    boardInit();
    /* executando rotina de inicializacao:
    * Placa do microcontrolador 
    * Configuração da modulação PWM 
    * Inicialização do cooler 
    * Inicialização do aquecedor */
    PWM_init();
    coolerfan_init();
    heater_init();
}



/* **************************************************************************** */
/* Nome do metodo:          main                                                */
/* DescriÃƒÂ§ÃƒÂ£o:         Inicializa o aquecedor e o cooler com 50% da tensão */
/*                                                                              */
/*                                                                              */
/* Parametros de entrada:   n/a                                                 */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
int main(void)
{

    boardInit();

    float fCoolerDuty = 0.5; 
    float fHeaterDuty = 0.5; 

    /*Passa a % de tensão desejada no cooler e no aquecedor*/
    coolerfan_PWMDuty(fCoolerDuty);
    heater_PWMDuty(fHeaterDuty);

}

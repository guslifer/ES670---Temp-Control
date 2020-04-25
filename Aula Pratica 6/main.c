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


void boardInit(void)
{
    boardInit();
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
    /* executando rotina de inicializacao:
    * Placa do microcontrolador 
    * Configuração da modulação PWM 
    * Inicialização do cooler 
    * Inicialização do aquecedor */
    PWM_init();
    coolerfan_init();
    heater_init();

    float fCoolerDuty = 0.5; 
    float fHeaterDuty = 0.5; 

    /*Passa a % de tensão desejada no cooler e no aquecedor*/
    coolerfan_PWMDuty(fCoolerDuty);
    heater_PWMDuty(fHeaterDuty);

}

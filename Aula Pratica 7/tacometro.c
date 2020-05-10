/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        tacometro.c                                            */
/*                                                                                  */
/*   Descricao:              Arquivo contendo as funcoes de interface do uC         */
/*                           com o encoder do kit, para leitura da rotacao do       */
/*                           cooler                                                 */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo Dollevedo                       */
/*   Criado em:              08/05/2020                                             */
/*   Ultima revisao em:      10/05/2020                                             */
/* ******************************************************************************** */

#include "board.h"
#include "tacometro.h"


/* ******************************************************************************** */
/* Nome do metodo:          tachometer_init                                         */ 
/* Descricao:               Inicializa os registradores para funcionamento do TPM0  */
/*                          como contador de pulsos                                 */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void tachometer_init(){ 


//Liberar o Clock para o timer E Clock para porta E
	SIM_SCGC6 |= PORTE_CLOCK_GATE;
	SIM_SCGC6 |= SET_LTPMRO;
//Configurar o divisor de clock em 1
	TPM0_SC  |= CLOCK_DIVIDER_1;

//Configurar contador para clock externo 
	TPM0_SC |= TPM_EXTERNAL_CLOCK;
//Seta o valor maximo de contagem 
	TPM0_SC |= TPM_MAX_VALUE_COUNT;

//configurar o pino PTE29 como external clock (ALT4) e o CLKIN0 como entrada 
    PORTE_PCR29  |= MUX_ALT4;
    SIM_SOPT4	 |= TPM0CLKSEL_AS_CLKIN0;

}


/* ******************************************************************************** */
/* Nome do metodo:          tachometer_readSensor                                   */ 
/* Descricao:               Le a velocidade do cooler (RPM) e a retorna             */
/*                                                                                  */
/* Parametros de entrada:    uiPeriod -> periodo da janela de contagem (LPTMR0)     */
/*                                                                                  */
/* Parametros de saida:      Um unsigned int indicando a rotacao (RPM) do cooler    */
/* ******************************************************************************** */
unsigned int tachometer_readSensor(unsigned int uiPeriod){

unsigned int iCounted = TPM_CNT; 
TPM_CNT &= 0x0000;
unsigned int iRotations = iCounted/7;

unsigned int iCoolerFreq = iCounted/uiPeriod;
unsigned int iCoolerRPM = iCoolerFreq * 60;

return iCoolerRPM;


}


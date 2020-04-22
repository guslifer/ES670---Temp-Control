/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        aquecedorECooler.c                                     */
/*                                                                                  */
/*   Descricao:              Arquivo contendo a implementacao                       */
/*                           das funcoes de interface do microcontrolador           */
/*                           com a resistencia de aquecimento e cooler do kit       */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo Dollevedo                       */
/*   Criado em:              21/04/2020                                             */
/*   Ultima revisao em:      21/04/2020                                             */
/* ******************************************************************************** */

#include "board.h"
#include "aquecedorECooler.h"
         

/* ******************************************************************************** */
/* Nome do metodo:          PWM_init                                                */ 
/* Descricao:               Inicializa os registradores para funcionamento do PWM   */
/*                          entre 5 e 20Hz                                          */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void PWM_init(void){


    /* Liberando o Clock para o timer/pwm*/
    SIM_SCGC6 |= TPM1_CLOCK_GATE;


    /*Divisor pro clock*/
    TPM1_SC   |= CLOCK_DIVIDER_64;

    /*Selecao do clock de 32kHz*/
    SIM_SOPT2 |= MCGIRCLK_SELECT;


    /*Modo de up-counting */
    TPM1_SC   |= PWM_UP_COUNTING;

    /*Conta todos pulsos*/
    TPM1_SC   |= PWM_EVERY_CLOCK;   

    /*Modulo configurado para 49 (chegar numa freq de 10Hz)*/
    TPM1_MOD  |= 0x0031;

    /*Configurando modo Edge Aligned PWM e High True Pulses nos canais 0 e 1*/
    TPM1_C0SC |= EDGE_ALIGNED_HIGH_TRUE;
    TPM1_C1SC |= EDGE_ALIGNED_HIGH_TRUE;

    /*DUTY CYCLE*/

}



/* ******************************************************************************** */
/* Nome do metodo:          coolerfan_init                                          */ 
/* Descricao:               Configura a liberacao do sinal PWM no pino PTA13        */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void coolerfan_init(void){

    SIM_SCGC5 |= PORTA_CLOCK_GATE;

    PORTA_PCR13 |= MUX_ALT3;

}

/* ******************************************************************************** */
/* Nome do metodo:          heater_init                                             */ 
/* Descricao:               Configura a liberacao do sinal PWM no pino PTA12        */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void heater_init(void){

    SIM_SCGC5 |= PORTA_CLOCK_GATE;

    PORTA_PCR12 |= MUX_ALT3;
}


/* ******************************************************************************** */
/* Nome do metodo:          coolerfan_PWMDuty                                       */ 
/* Descricao:               Configura o Duty Cycle do PWM para o cooler             */
/*                                                                                  */
/* Parametros de entrada:   fCoolerDuty -> valor entre 0 e 1 indicando o Duty Cycle */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void coolerfan_PWMDuty(float fCoolerDuty){
   
}

/* ******************************************************************************** */
/* Nome do metodo:          heater_PWMDuty                                          */ 
/* Descricao:               Configura o Duty Cycle do PWM para o cooler             */
/*                                                                                  */
/* Parametros de entrada:   fHeaterDuty -> valor entre 0 e 1 indicando o Duty Cycle */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void heater_PWMDuty(float fHeaterDuty){

}

#endif /* SOURCES_D7S_ */

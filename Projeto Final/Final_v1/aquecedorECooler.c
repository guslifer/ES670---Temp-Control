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
/*   Ultima revisao em:      23/04/2020                                             */
/* ******************************************************************************** */

/* REVISÃO: */
/* ALTERADO PARA "&=" no UP_COUNTING, e sua mascara no board.h */
/* ADICIONADO DISABLE_COUNTER */
/* ALTERADO PARA "&=" no EDGE_ALIGNED, e sua mascara no board.h */
/* ADICIONADO UM CLEAR PARA "TPM_CNT" na inicializacao*/
/* ADICIONADA UMA FUNCAO PARA RESETAR O "TPM_CNT" (PWM_clearCounter)*/
/* ADICIONADO "CLEAR_16" no board.h */
/* ALTERADAS AS MASCARAS PARA "CLOCK_DIVIDER" no board.h*/
/* ALTERADO PARA "&=" no CLOCK_DIVIDER */


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
    /*MCGIRCLK == internal reference clock*/
    SIM_SOPT2 |= MCGIRCLK_SELECT;


    /*Desabilitando o LPTPM Counter para poder alterar o modo de contagem*/
    TPM1_SC &= DISABLE_COUNTER;
    
    /*Modo de up-counting */
    TPM1_SC &= PWM_UP_COUNTING;

    /*Incrementa a cada pulso*/
    TPM1_SC   |= PWM_EVERY_CLOCK;   

    /*Modulo configurado para 49 (chegar numa freq de 10Hz)*/
    /*Portanto, conta ate 50 (0 a 49)*/
    TPM1_MOD  |= 0x0031;

    /*Configurando modo Edge Aligned PWM e High True Pulses nos canais 0 e 1*/
    TPM1_C0SC &= EDGE_ALIGNED_HIGH_TRUE;
    TPM1_C1SC &= EDGE_ALIGNED_HIGH_TRUE;

    /*DUTY CYCLE 50%*/
    /*Inverte o sinal apos contar 25 vezes*/
    TPM1_C0V |= 0x0019;
    TPM1_C1V |= 0x0019;

    TPM1_CNT &= CLEAR_16; 
}


/* ******************************************************************************** */
/* Nome do metodo:          PWM_clearCounter                                        */ 
/* Descricao:               Reseta o contador TPM1_CNT para nao haver overflow      */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void PWM_clearCounter(void){

    if(TPM1_CNT >= 0x7FFF)
        TPM1_CNT &= CLEAR_16;

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
   
    unsigned char ucDuty = 0;

    if(0 <= fCoolerDuty && 1 >= fCoolerDuty){
        ucDuty = 50*fCoolerDuty;
    }

    else{
        ucDuty = 0x0019;
    }

    TPM1_C1V &= CLEAR_16;
    TPM1_C1V |= ucDuty;

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

    unsigned char ucDuty = 0;

    if(0 <= fHeaterDuty && 1 >= fHeaterDuty){
         ucDuty = 50*fHeaterDuty;
    }

    else{
        ucDuty = 0x0019;
    }

    TPM1_C0V &= CLEAR_16;
    TPM1_C0V |= ucDuty;

}

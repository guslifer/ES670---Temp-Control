/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        aquecedorECooler.h                                     */
/*                                                                                  */
/*   Descricao:              Arquivo Header contendo a declaracao                   */
/*                           das funcoes de interface do microcontrolador           */
/*                           com a resistencia de aquecimento e cooler do kit       */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo Dollevedo                       */
/*   Criado em:              21/04/2020                                             */
/*   Ultima revisao em:      23/04/2020                                             */
/* ******************************************************************************** */

#ifndef SOURCES_COOLER_HEATER_
#define SOURCES_COOLER_HEATER_

#define CLEAR_16 = 0x0000

/* ******************************************************************************** */
/* Nome do metodo:          PWM_init                                                */ 
/* Descricao:               Inicializa os registradores para funcionamento do PWM   */
/*                          entre 5 e 20Hz                                          */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void PWM_init(void){}


/* ******************************************************************************** */
/* Nome do metodo:          coolerfan_init                                          */ 
/* Descricao:               Configura a liberacao do sinal PWM no pino PTA13        */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void coolerfan_init(void){}


/* ******************************************************************************** */
/* Nome do metodo:          heater_init                                             */ 
/* Descricao:               Configura a liberacao do sinal PWM no pino PTA12        */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void heater_init(void){}

/* ******************************************************************************** */
/* Nome do metodo:          coolerfan_PWMDuty                                       */ 
/* Descricao:               Configura o Duty Cycle do PWM para o cooler             */
/*                                                                                  */
/* Parametros de entrada:   fCoolerDuty -> valor entre 0 e 1 indicando o Duty Cycle */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void coolerfan_PWMDuty(float fCoolerDuty){}

/* ******************************************************************************** */
/* Nome do metodo:          heater_PWMDuty                                          */ 
/* Descricao:               Configura o Duty Cycle do PWM para o cooler             */
/*                                                                                  */
/* Parametros de entrada:   fHeaterDuty -> valor entre 0 e 1 indicando o Duty Cycle */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void heater_PWMDuty(float fHeaterDuty){}
#endif /* SOURCES_COOLER_HEATER_ */

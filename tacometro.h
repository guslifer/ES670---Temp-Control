/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        tacometro.h                                            */
/*                                                                                  */
/*   Descricao:              Arquivo Header contendo a declaracao                   */
/*                           das funcoes de interface do microcontrolador           */
/*                           com o encoder do kit, para leitura da rotacao do       */
/*                           cooler                                                 */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo Dollevedo                       */
/*   Criado em:              08/05/2020                                             */
/*   Ultima revisao em:      08/05/2020                                             */
/* ******************************************************************************** */

#ifndef SOURCES_TACHOMETER_
#define SOURCES_TACHOMETER_


/* ******************************************************************************** */
/* Nome do metodo:          tachometer_init                                         */ 
/* Descricao:               Inicializa os registradores para funcionamento do TPM0  */
/*                          como contador de pulsos                                 */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void tachometer_init(void);


/* ******************************************************************************** */
/* Nome do metodo:          tachometer_readSensor                                   */ 
/* Descricao:               Le a velocidade do cooler (RPM) e a retorna             */
/*                                                                                  */
/* Parametros de entrada:    uiPeriod -> periodo da janela de contagem (LPTMR0)     */
/*                                                                                  */
/* Parametros de saida:      Um unsigned int indicando a rotacao (RPM) do cooler    */
/* ******************************************************************************** */
unsigned int tachometer_readSensor(unsigned int uiPeriod);


#endif /* SOURCES_COOLER_HEATER_ */

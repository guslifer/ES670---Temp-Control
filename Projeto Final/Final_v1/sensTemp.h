/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:       sensTemp.h                                              */
/*                                                                                  */
/*   Descricao:             Declaracao das funcoes implementadas no arquivo         */
/*                          sensTemp.c                                              */
/*                                                                                  */
/*   Autores:               Gustavo Lino e Giacomo A. Dollevedo                     */
/*   Criado em:             29/07/2020                                              */
/*   Ultima revisao em:     29/07/2020                                              */
/* ******************************************************************************** */

#ifndef SOURCES_SENSTEMP_
#define SOURCES_SENSTEMP_

/* ******************************************************************************** */
/* Nome do metodo:          sensTemp_init                                           */ 
/* Descricao:               Inicializa as funcoes do ADC para sensor de temperatura */
/*                                                                                  */
/* Parametros de entrada:   n/a                                                     */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void sensTemp_init(void);


/* **************************************************************************** */
/* Nome do metodo:          readTemp                                            */
/* Descricao:               Le o ADC conectado ao sensor de temperatura e       */
/*                          converte o valor pela lookup table em graus Celsius */
/*                                                                              */
/* Parametros de entrada:   n/a                                                 */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
void readTemp(void);


#endif SOURCES_SENSTEMP_
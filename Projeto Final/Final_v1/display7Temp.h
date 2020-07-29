/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:       display7Temp.c                                          */
/*                                                                                  */
/*   Descricao:             Declaracao das funcoes para operar o D7S uteis no       */
/*                          contexto do projeto do controlador de temperatura       */
/*                                                                                  */
/*   Autores:               Gustavo Lino e Giacomo A. Dollevedo                     */
/*   Criado em:             29/07/2020                                              */
/*   Ultima revisao em:     29/07/2020                                              */
/* ******************************************************************************** */

#ifndef SOURCES_D7TEMP_H_
#define SOURCES_D7TEMP_H_

/* ******************************************************************************** */
/* Nome do metodo:          display7Temp_init                                       */ 
/* Descricao:               Inicializa os registradores para funcionamento do D7S   */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void display7Temp_init(void);


/* ******************************************************************************** */
/* Nome do metodo:          attDisp7Temp                                            */ 
/* Descricao:               Atualiza o D7S com a temperatura atual da resistencia   */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void attDisp7Temp(void);

#endif SOURCES_D7TEMP_H_
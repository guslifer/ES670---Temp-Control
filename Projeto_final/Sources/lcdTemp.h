/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:       lcdTemp.h                                               */
/*                                                                                  */
/*   Descricao:             Arquivo Header contendo as declaracoes das funcoes      */
/*                          definidas em lcdTemp.c                                  */
/*                                                                                  */
/*   Autores:               Gustavo Lino e Giacomo A. Dollevedo                    */
/*   Criado em:             28/07/2020                                             */
/*   Ultima revisao em:     28/07/2020                                             */
/* ******************************************************************************** */

#ifndef SOURCES_LCDTEMP_H_
#define SOURCES_LCDTEMP_H_


/* ******************************************************************************** */
/* Nome do metodo:          lcdTemp_init                                            */ 
/* Descricao:               Inicializa as funcoes do LCD                            */
/*                                                                                  */
/* Parametros de entrada:   n/a                                                     */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void lcdTemp_init(void);


/* **************************************************************************** */
/* Nome do metodo:          showLCDdisp                                         */
/* Descricao:               Realiza a troca de mensagem no LCD de acordo com    */
/*                          estado                                              */
/*                                                                              */
/* Parametros de entrada:   unsigned char ucFrame -> Indica o frame que sera    */
/*                          mostrado                                            */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
void showLCDdisp(unsigned char ucFrame);

/* **************************************************************************** */
/* Nome do metodo:          attTempAlvo                                         */
/* Descricao:               Atualiza o display com a temperatura desejada       */
/*                                                                              */
/* Parametros de entrada:   unsigned char ucDezena -> Indica a dezena da temp.  */
/*                          alvo                                           	 	*/
/* 							unsigned char ucUnidade -> Indica a unidade da temp.*/
/*							alvo 												*/
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
void attTempAlvo(unsigned char ucDezena, unsigned char ucUnidade);

#endif /*SOURCES_LCDTEMP_H_*/

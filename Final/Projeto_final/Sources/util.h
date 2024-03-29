/* ***************************************************************** */
/* File name:        util.h                                          */
/* File description: Header file containing the function/methods     */
/*                   prototypes of util.c                            */
/*                   Those delays were tested under the following:   */
/*                   core clock @ 40MHz                              */
/*                   bus clock @ 20MHz                               */
/* Author name:      dloubach                                        */
/* Creation date:    09jan2015                                       */
/* Revision date:    09jun2020                                       */
/* ***************************************************************** */

#ifndef UTIL_H
#define UTIL_H

/* ************************************************ */
/* Method name:        util_genDelay088us           */
/* Method description: generates ~ 088 micro sec    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay088us(void);


/* ************************************************ */
/* Method name:        util_genDelay250us           */
/* Method description: generates ~   250 micro sec  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay250us(void);


/* ************************************************ */
/* Method name:        util_genDelay1ms             */
/* Method description: generates ~   1 mili sec     */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay1ms(void);


/* ************************************************ */
/* Method name:        util_genDelay10ms            */
/* Method description: generates ~   10 mili sec    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay10ms(void);

/* ************************************************ */
/* Method name:        util_genDelay10ms            */
/* Method description: generates ~   100 mili sec    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay100ms(void);

/* **************************************************************************** */
/* Nome do metodo:          extrai_digito                                    	*/
/* Descricao:               Extrai digitos de um numero e armazena num vetor 	*/
/*                                                                              */
/*                                                                              */
/* Parametros de entrada:   numero -> numero que os digitos serao extraidos		*/
/*							digitos -> vetor onde os digitos serao armazenados  */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
void extrai_digito(unsigned int numero, unsigned char* digitos);

#endif /* UTIL_H */

/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        display7seg.h                                          */
/*                                                                                  */
/*   Descricao:              Arquivo Header contendo a declaracao                   */
/*                           das funcoes de interface do microcontrolador           */
/*                           com o display de 7 segmentos do kit                    */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo Dollevedo                       */
/*   Criado em:              13/04/2020                                             */
/*   Ultima revisao em:      13/04/2020                                             */
/* ******************************************************************************** */

#ifndef SOURCES_D7S_
#define SOURCES_D7S_


/* ******************************************************************************** */
/* Nome do metodo:          display7Seg_init                                        */ 
/* Descricao:               Inicializa os registradores para funcionamento do D7S   */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void display7seg_init(void);

/* ******************************************************************************** */
/* Nome do metodo:          display7seg_writeChar 									*/
/* Descricao:               Escreve uma letra em um D7S                           	*/
/*                                                                                  */
/* Parametros de entrada:   ucDisplay -> indica o D7S no qual sera escrito (1 a 4)  */
/*                          ucValue -> valor indicando a letra que sera escrita 	*/
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void display7seg_writeChar(unsigned char ucDisplay, unsigned char ucChar);


/* ******************************************************************************** */
/* Nome do metodo:          display7seg_writeSymbol                                 */ 
/* Descricao:               Escreve um caracter em um D7S                           */
/*                                                                                  */
/* Parametros de entrada:   ucDisplay -> indica o D7S no qual sera escrito (1 a 4)  */
/*                          ucValue -> valor indicando o caracter que sera escrito  */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void display7seg_writeSymbol(unsigned char ucDisplay,  unsigned char ucValue);


/* ******************************************************************************** */
/* Nome do metodo:          selectDisp                                              */ 
/* Descricao:               Seleciona o D7S que sera escrito                        */
/*                                                                                  */
/* Parametros de entrada:   ucDisplay -> indica o D7S no qual sera escrito (1 a 4)  */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void selectDisp(unsigned char ucDisplay);



#endif /* SOURCES_D7S_ */

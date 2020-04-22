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
/*   Ultima revisao em:      21/04/2020                                             */
/* ******************************************************************************** */

#ifndef SOURCES_D7S_
#define SOURCES_D7S_

/* formato letras display 7 seg */
/*  DP    g    f    e   d   c   b   a*/

#define DISP_0      0x003F
#define DISP_1      0x0006
#define DISP_2      0x005B
#define DISP_3      0x004F
#define DISP_4      0x0066 
#define DISP_5      0x006D
#define DISP_6      0x007D
#define DISP_7      0x0007
#define DISP_8      0x007F
#define DISP_9      0x006F
#define DISP_A      0x0077
#define DISP_B      0x007C
#define DISP_C      0x0039
#define DISP_D      0x005E
#define DISP_E      0x0079
#define DISP_F      0x0071
#define DISP_DP     0x0080
#define DISP_CLEAR  0xFFFFFF00
#define DISP_ALL    0x00FF

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

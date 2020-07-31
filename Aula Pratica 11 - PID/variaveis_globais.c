/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        variaveis_globais.c                                    */
/*                                                                                  */
/*   Descricao:             Contém as variaveis globais que são alteradas e         */
/*                          acessadas constantemente                                */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo A. Dollevedo                    */
/*   Criado em:              27/07/2020                                             */
/*   Ultima revisao em:      28/07/2020                                             */
/* ******************************************************************************** */

unsigned char ucTempAlvo 		= 30; 
unsigned char ucTempAtual		= 0; 
unsigned char ucDezTempAlvo     = 0;
unsigned char ucUnTempAlvo      = 0;
unsigned char ucUnTempAtual     = 0;
unsigned char ucDezTempAtual    = 0;
float fDutyCycle_Heater;
float fKp;
float fKi;
float fKd;
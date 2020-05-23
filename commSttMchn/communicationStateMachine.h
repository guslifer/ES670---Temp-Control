/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        communicationStateMachine.h                            */
/*                                                                                  */
/*   Descricao:              Arquivo contendo a bilioteca das funcoes 				*/
/*							 de que implementam uma     							*/				
/*                           maquina de estados para comunicacao UART               */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo Dollevedo                       */
/*   Criado em:              21/05/2020                                             */
/*   Ultima revisao em:      21/05/2020                                             */
/* ******************************************************************************** */


#ifndef _COMMUNICATIONSTATEMACHINE_H
#define _COMMUNICATIONSTATEMACHINE_H




/* ******************************************************************************** */
/* Nome do metodo:          returnParam                                             */ 
/* Descricao:               Imprime no terminal de comunicacao UART os parametros   */
/*                          solicitados pelo comando Get                 			*/
/*                                                                                  */
/* Parametros de entrada:    Parametro solicitado (de acordo com dicionario)        */
/*                                                                                  */
/* Parametros de saida:      Comunicação UART -> parametro solicitado				*/
/*							 temperatura atual 										*/
/*							 duty cycle cooler										*/
/*							 duty cycle heater									    */            
/* ******************************************************************************** */
void returnParam(unsigned char ucParam);


/* ******************************************************************************** */
/* Nome do metodo:          setParam                                                */ 
/* Descricao:               Define valores de controle/usabilidade necessarios para */
/*                          garantir a interface e funcionamento adequado do uC:	*/
/*							Temperatura Máxima										*/
/*							Disponibilidade dos botoões							    */
/*                                                                                  */
/* Parametros de entrada:    Configuração desejado (de acordo com dicionario)       */
/*                                                                                  */
/* Parametros de saida:      Função ou ação sobre as variaveis                      */
/* ******************************************************************************** */
void setParam(unsigned char ucParam, unsigned char ucValue);

/* ******************************************************************************** */
/* Nome do metodo:          processByteCommUART                                     */ 
/* Descricao:               Realiza todos os processos para que a comunicacao UART  */
/*                          ocorra, baseado numa maquina de estados                 */
/*                                                                                  */
/* Parametros de entrada:    Comandos em Bytes enviados através da comunicação UART */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void processByteCommUART(unsigned char ucCmdByte);



#endif /* _COMMUNICATIONSTATEMACHINE_H */
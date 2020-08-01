/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        communicationStateMachine.c                            */
/*                                                                                  */
/*   Descricao:              Arquivo contendo as funcoes de que implementam uma     */
/*                           maquina de estados para comunicacao UART               */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo Dollevedo                       */
/*   Criado em:              21/05/2020                                             */
/*   Ultima revisao em:      29/07/2020                                             */
/* ******************************************************************************** */

/*REVISAO:*/
/*ALTERADO O FUNCIONAMENTO DA FUNCAO "setParam"*/
/*ALTERADA AS -VARIAVEIS DE TESTE- */

/*Revisão: 28/07/2020 23:18*/ 
/*Inserido a possibilidade de setar os parametros de ganho Kp, Ki e Kd*/

/* Comandos utilizados (dicionario): 
   "#gt;" Get valor de temperatura atual 
   "#gc;" Get Duty Cycle Cooler 
   "#gh;" Get Duty Cycle Heater 

   "#sb<N>;" Set Button On/OFF, onde N é qualquer número de até de 7 bytes. 
   "#st<N>;" Set Temperatura Máxima desejada para controle, onde N é qualquer número de até de 7 byte. 
   "#sc<N>;" Set duty cycle do cooler, onde N é qualquer número de até de 7 bytes.
   "#sh<N>;" Set duty cycle do heater, onde N é qualquer número de até de 7 bytes.
   "#sp<N>;" Set ganho prporcional do controlador PID, onde N é qualquer número de até 7 bytes.
   "#si<N>;" Set ganho integrativo do controlador PID, onde N é qualquer número de até 7 bytes.
   "#sd<N>;" Set ganho derivativo do controlador PID, onde N é qualquer número de até 7 bytes.



   "<#a<p>;" Respostas do parametro solicitado, onde p pode ser t,c ou h. 

   É previsto nas próximas versões do código que haja a solicitação de todos os parametros e sua respostas

*/

#include "aquecedorECooler.h"
#include "variaveis_globais.h"
#include <stdlib.h>



#define IDLE    0
#define READY   1
#define GET     2
#define SET     3
#define PARAM   4
#define VALUE   5

#define MAX_VALUE_LENGTH  7

unsigned char ucCurrentState = IDLE;
unsigned char ucValueCounter = 0;

/*VARIAVEIS DE TESTE*/
unsigned char ucMaxTempTest[MAX_VALUE_LENGTH+1] = "30";
unsigned char ucCurrTempTest[MAX_VALUE_LENGTH+1]= "25";
unsigned char fCoolerDutyTest[5] = "0,75";
unsigned char fHeaterDutyTest[5] = "0,50";


/* ******************************************************************************** */
/* Nome do metodo:          returnParam                                             */ 
/* Descricao:               Imprime no terminal de comunicacao UART os parametros   */
/*                          solicitados pelo comando Get                 			*/
/*                                                                                  */
/* Parametros de entrada:   ucParam -> Parametro solicitado (de acordo com dicionario)*/
/*                                                                                  */
/* Parametros de saida:     n/a								    					*/
/* ******************************************************************************** */
void returnParam(unsigned char ucParam){

    switch(ucParam){

        case 't':
            debug_printf("#a%dºC;", ucTempAtual);
            break;

        case 'c':
            debug_printf("#a%c%c%c%c;", fCoolerDutyTest[0], fCoolerDutyTest[1], fCoolerDutyTest[2], fCoolerDutyTest[3]);
            break;

        case 'h':
            debug_printf("#a%c%c%c%c;", fHeaterDutyTest[0], fHeaterDutyTest[1] ,fHeaterDutyTest[2], fHeaterDutyTest[3]);
            break;

        case 'p':
            debug_printf("#a%f;", fKp);
            break;

        case 'i':
            debug_printf("#a%f;", fKi);
            break;

        case 'd':
            debug_printf("#a%f;", fKd);
            break;

    }


}


/* ******************************************************************************** */
/* Nome do metodo:          setParam                                                */ 
/* Descricao:               Define valores de controle/usabilidade necessarios para */
/*                          garantir a interface e funcionamento adequado do uC:	*/
/*							Temperatura Máxima										*/
/*							Disponibilidade dos botoes							    */
/*                                                                                  */
/* Parametros de entrada:   ucParam -> Parametro que sera alterado 					*/
/* 							*ucValue ->  Array com valores de alteracao             */
/*                                                                                  */
/* Parametros de saida:     n/a  													*/
/* ******************************************************************************** */
void setParam(unsigned char ucParam, unsigned char *ucValue){

    unsigned char ucContador = 0;
    unsigned char ucFlag = 0;
    unsigned char ucStrValue[5] = "0,00\0";
    float fAux = 0;

    switch(ucParam){

        case 't':
            while('\0' != ucValue[ucContador]){
            //Pega o valor da dezena                
                if(0 == ucContador){ 
                    if(9 == ucValue[ucContador]){
                        //Limita em 90 a temperatura maxima
                        fAux = 90; 
                        ucTempAlvo = fAux;
                        ucDezTempAlvo = 9;
                        ucUnTempAlvo = 0;
                        break;
                    }
                    fAux = ucValue[ucContador] -48;
                    fAux = fAux*10;
                }
            //Pega o valor da unidade    
                else if(1 == ucContador){ 
                    fAux = fAux + (ucValue[ucContador] -48);
                    ucTempAlvo = fAux;
                }
                if(2 < ucContador){ 
            //Caso o usuario tente inserir uma temperatura maior que 2 digitos, seta a temperatura alvo par ao padrão    
                    ucTempAlvo = 30;
                }
                ucContador++;
            }
            ucDezTempAlvo = ucTempAlvo/10;
            ucUnTempAlvo = ucTempAlvo%10;
            break;

        //Habilitar ou desabilitar os botões da interface do microcontrolador.
        case 'b':
            /* Espera ucValue num formato especifico*/
            if('\0' != ucValue[4]) {
                if((0 != ucValue[0] && 1 != ucValue[0]) && (0 != ucValue[1] && 1 != ucValue[1]))
                    if((0 != ucValue[2] && 1 != ucValue[2]) && (0 != ucValue[3] && 1 != ucValue[3]))
                        ledSwi_init(ucValue[0], ucValue[1], ucValue[2], ucValue[3]);
                        break;
             }

            else{
                break;
            }

        /* Caso para setar Duty Cycle do cooler */
        case 'c':
            ucContador  = 0;
            ucFlag      = 0;
            fAux        = 0;

            while('\0' != ucValue[ucContador]){
                if('1' == ucValue[0]){
                    coolerfan_PWMDuty(1.0);
                    break;
                }

                if(',' == ucValue[ucContador]){
                    ucFlag = 1;
                }

                else if (1 == ucFlag){
                    fAux += ucValue[ucContador] - 48;
                    fAux = fAux*10;
                }

                ucContador++;
            }

            if(1 == ucFlag){
                while(fAux > 0)
                    fAux = fAux/10;

            coolerfan_PWMDuty(fAux);
            }

            break;

        /* Caso para setar Duty Cycle do heater */
        case 'h':
            ucContador  = 0;
            ucFlag      = 0;
            fAux        = 0;
            while('\0' != ucValue[ucContador]){
                if('1' == ucValue[0]){ //Seria melhor generalizar para qualquer valor diferente de zero?
                    heater_PWMDuty(0.5);
                    fDutyCycle_Heater = 0.5;
                    break;
                }

                if(',' == ucValue[ucContador]){
                    ucFlag = 1;
                }

                else if (1 == ucFlag){
                    fAux += ucValue[ucContador] - 48;
                    fAux = fAux*10;
                }

                ucContador++;
            }

            if(1 == ucFlag){
                while(fAux > 0)
                    fAux = fAux/10;

                if(0.5 < fAux){
                    heater_PWMDuty(0.5);
                    fDutyCycle_Heater = 0.5;
                }
                
                else{
                    heater_PWMDuty(fAux);
                    fDutyCycle_Heater = fAux;
                }
        
            break;

        case 'p':

       
            ucContador  = 0;
            fAux        = 0;

            while('\0' != ucValue[ucContador]){

                if(',' != ucValue[ucContador]){
                    ucStrValue[ucContador] = ucValue[ucContador];
                }
                //Converte virgula para ponto
                else{ 

                    ucStrValue[ucContador] = '.';

                }
                ucContador++;
            }

            fAux = strtof(ucStrValue, NULL); 
            fKp = fAux;

            break;

        case 'i':

       
            ucContador  = 0;
            fAux        = 0;

            while('\0' != ucValue[ucContador]){

                if(',' != ucValue[ucContador]){
                    ucStrValue[ucContador] = ucValue[ucContador];
                }
                //Converte virgula para ponto
                else{ 

                    ucStrValue[ucContador] = '.';

                }
                ucContador++;
            }

            fAux = strtof(ucStrValue, NULL); 
            fKi = fAux;

            break;

        case 'd':

       
            ucContador  = 0;
            fAux        = 0;

            while('\0' != ucValue[ucContador]){

                if(',' != ucValue[ucContador]){
                    ucStrValue[ucContador] = ucValue[ucContador];
                }
                //Converte virgula para ponto
                else{ 

                    ucStrValue[ucContador] = '.';

                }
                ucContador++;
            }

            fAux = strtof(ucStrValue, NULL); 
            fKd = fAux;

            break;
        
    }

}
}


/* ******************************************************************************** */
/* Nome do metodo:          processByteCommUART                                     */ 
/* Descricao:               Realiza todos os processos para que a comunicacao UART  */
/*                          ocorra, baseado numa maquina de estados                 */
/*                                                                                  */
/* Parametros de entrada:   ucCmdByte-> Comandos em Bytes enviados por UART 		*/
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void processByteCommUART(unsigned char ucCmdByte){ 


    static unsigned char ucParam;
    static unsigned char ucValue[MAX_VALUE_LENGTH + 1];

    if('#' == ucCmdByte)
        ucCurrentState = READY;

    else
        if(IDLE != ucCurrentState)
            switch(ucCurrentState ){

                case READY:
                    if('g' == ucCmdByte)
                        ucCurrentState = GET;

                    if('s' == ucCmdByte)
                        ucCurrentState = SET;
                    
                    else
                        ucCurrentState = IDLE;

                    break;
                    

                case GET:
                    if('t' == ucCmdByte || 'c' == ucCmdByte || 'h' == ucCmdByte || 'i' == ucCmdByte || 'p' == ucCmdByte || 'd' == ucCmdByte){
                        ucParam = ucCmdByte;
                        ucCurrentState = PARAM;
                    }

                    else
                        ucCurrentState = IDLE;

                    break;

                case SET:
                    if('t' == ucCmdByte || 'b' == ucCmdByte || 'c' == ucCmdByte || 'h' == ucCmdByte || 'p' == ucCmdByte || 'i' == ucCmdByte || 'd' == ucCmdByte){
                        ucParam = ucCmdByte;
                        ucValueCounter = 0;
                        ucCurrentState = VALUE;
                    }

                    else
                        ucCurrentState = IDLE;

                    break;

                case PARAM:
                    if(';' == ucCmdByte)
                        returnParam(ucParam);

                    ucCurrentState = IDLE;

                    break;

                case VALUE:
                    if((ucCmdByte >= '0' && ucCmdByte <= '9') || ','){
                        if(ucValueCounter < MAX_VALUE_LENGTH){
                            ucValue[ucValueCounter] = ucCmdByte;
                            ucValueCounter++;
                        }
                    }
                        
                    else{
                        if(';' == ucCmdByte){
                            ucValue[ucValueCounter] = '\0';
                            setParam(ucParam, ucValue);
                        }

                        ucCurrentState = IDLE;

                    }
                    break;

                default:
                    ucCurrentState = IDLE;
            }
}

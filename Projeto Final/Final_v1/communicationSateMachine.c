/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        communicationStateMachine.c                            */
/*                                                                                  */
/*   Descricao:              Arquivo contendo as funcoes de que implementam uma     */
/*                           maquina de estados para comunicacao UART               */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo Dollevedo                       */
/*   Criado em:              21/05/2020                                             */
/*   Ultima revisao em:      25/07/2020                                             */
/* ******************************************************************************** */

/*REVISAO:*/
/*ALTERADO O FUNCIONAMENTO DA FUNCAO "setParam"*/
/*ALTERADA AS -VARIAVEIS DE TESTE- */

/* Comandos utilizados (dicionario): 
   "#gt;" Get valor de temperatura atual 
   "#gc;" Get Duty Cycle Cooler 
   "#gh;" Get Duty Cycle Heater 

   "#sb<N>;" Set Button On/OFF, onde N é qualquer número de até de 7 bytes. 
   "#st<N>;" Set Temperatura Máxima desejada para controle, onde N é qualquer número de até de 7 bytes. 
   "#sc<N>;" Set duty cycle do cooler, onde N é qualquer número de até de 7 bytes.
   "#sh<N>;" Set duty cycle do heater, onde N é qualquer número de até de 7 bytes.

   "<#a<p>;" Respostas do parametro solicitado, onde p pode ser t,c ou h. 

   É previsto nas próximas versões do código que haja a solicitação de todos os parametros e sua respostas

*/

#include "aquecedorECooler.h"

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
            debug_printf("#a%c;", ucCurrTempTest);
            break;

        case 'c':
            debug_printf("#a%c%c%c%c;", fCoolerDutyTest[0], fCoolerDutyTest[1], fCoolerDutyTest[2], fCoolerDutyTest[3]);
            break;

        case 'h':
            debug_printf("#a%c%c%c%c;", fHeaterDutyTest[0], fHeaterDutyTest[1] ,fHeaterDutyTest[2], fHeaterDutyTest[3]);
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
    float fAux = 0;

    switch(ucParam){

        case 't':
            while('\0' != ucValue[ucContador]){
                ucMaxTempTest[ucContador] = ucValue[ucContador];
                ucContador++;
            }
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
                if('1' == ucValue[0]){
                    heater_PWMDuty(0.5);
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

                if(0.5 < fAux)
                    heater_PWMDuty(0.5);
                
                else
                    heater_PWMDuty(fAux);
            }
        
            break;
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
                    if('t' == ucCmdByte || 'c' == ucCmdByte || 'h' == ucCmdByte){
                        ucParam = ucCmdByte;
                        ucCurrentState = PARAM;
                    }

                    else
                        ucCurrentState = IDLE;

                    break;

                case SET:
                    if('t' == ucCmdByte || 'b' == ucCmdByte || 'c' == ucCmdByte || 'h' == ucCmdByte){
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

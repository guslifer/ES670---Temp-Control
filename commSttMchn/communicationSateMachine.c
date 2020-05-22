/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        communicationStateMachine.c                            */
/*                                                                                  */
/*   Descricao:              Arquivo contendo as funcoes de que implementam uma     */
/*                           maquina de estados para comunicacao UART               */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo Dollevedo                       */
/*   Criado em:              21/05/2020                                             */
/*   Ultima revisao em:      21/05/2020                                             */
/* ******************************************************************************** */

#include "board.h"
#include "UART.h"
#include "ledSwi.h"

#define IDLE    0
#define READY   1
#define GET     2
#define SET     3
#define PARAM   4
#define VALUE   5

#define MAX_VALUE_LENGTH = 7

unsigned char ucCurrentState = IDLE;
unsigned char ucValueCounter = 0;

unsigned char ucMaxTempTest = 4;
unsigned char ucCurrTempTest = 3;
char fCoolerDutyTest[3];   
char fHeaterDutyTest[3];

fCoolerDutyTest[0] = '0';
fCoolerDutyTest[1] = ',';
fCoolerDutyTest[2] = '7';
fCoolerDutyTest[3] = '5';

fHeaterDutyTest[0] = '0';
fHeaterDutyTest[1] = ',';
fHeaterDutyTest[2] = '5';
fHeaterDutyTest[3] = '0';

/* ******************************************************************************** */
/* Nome do metodo:          returnParam                                             */ 
/* Descricao:               Realiza todos os processos para que a comunicacao UART  */
/*                          ocorra, baseado numa maquina de estados                 */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void returnParam(unsigned char ucParam){

    switch(ucParam){

        case 't':
            debug_putchar(ucCurrTempTest);
            break;

        case 'c':
            debug_printf("%c%c%c%c", fCoolerDutyTest[0], fCoolerDutyTest[1], fCoolerDutyTest[2], fCoolerDutyTest[3]);
            break;

        case 'h':
            debug_printf("%c%c%c%c", fHeaterDutyTest[0], fHeaterDutyTest[1] ,fHeaterDutyTest[2], fHeaterDutyTest[3]);
            break;

    }


}


/* ******************************************************************************** */
/* Nome do metodo:          setParam                                                */ 
/* Descricao:               Realiza todos os processos para que a comunicacao UART  */
/*                          ocorra, baseado numa maquina de estados                 */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void setParam(unsigned char ucParam, unsigned char ucValue){

    switch(ucParam){

        case 't':
            ucMaxTempTest = ucValue;
            break;


        case 'b':
            if(ucValue > 0){
                ledSwi_init(0, 0, 0, 0);
            }

            else{
                ledSwi_init(1, 1, 1, 1);
            }
            break;

    }


}


/* ******************************************************************************** */
/* Nome do metodo:          processByteCommUART                                     */ 
/* Descricao:               Realiza todos os processos para que a comunicacao UART  */
/*                          ocorra, baseado numa maquina de estados                 */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void processByteCommUART(unsigned char ucCmdByte){ 


    static unsigned char ucParam;
    static unsigned char ucValue[MAX_VALUE_LENGTH+1];

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
                    if('t' == ucCurrentState || 'b' == ucCurrentState){
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
                    if((ucCmdByte >= '0' && ucCmdByte <= '9') || ',')
                        if(ucValueCounter < MAX_VALUE_LENGTH){
                            ucValue[ucValueCounter] = ucCmdByte;
                            ucValueCounter++;
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

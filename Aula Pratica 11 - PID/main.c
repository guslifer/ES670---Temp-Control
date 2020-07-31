/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        main.c                                                 */
/*                                                                                  */
/*   Descricao:             Projeto final do controlador de temperatura com         */
/*                          interface                                               */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo A. Dollevedo                    */
/*   Criado em:              27/07/2020                                             */
/*   Ultima revisao em:      28/07/2020                                             */
/* ******************************************************************************** */

/* Incluindo bibliotecas */
#include "board.h"  
#include "util.h"
#include "adc.h"
#include "lut_adc_3v3.h"
#include "lptmr.h"
#include "lcd.h"
#include "ledSwi.h"
#include "pid.h"
#include "display7seg.h"
#include "uart.h"
#include "variaveis_globais.h"
#include "sensTemp.h"
#include "aquecedorECooler.h"
#include "communicationStateMachine.h"
#include "stdio.h"

/********************************************************************************/
/********************           DECLARANDO CONSTANTES       *********************/

/*Temperatura*/
#define TEMP_DEFAULT 30

/*Tick base do timer*/
#define TICK_4MS     4000

/*Estados principais do sistema*/
#define CONFIG      0
#define CONTROLE    1

/*Subestados CONFIG*/
#define UNIDADE     0
#define DEZENA      1

/*Subestados UNIDADE e DEZENA*/
#define STATE_0     0
#define STATE_N     1
#define STATE_9     2

/*Constante de ganho do controlador*/ 

#define FKP         0.001f
#define FKI         0.002f
#define FKD         0.003f

/********************           FIM DAS CONSTANTES          *********************/
/********************************************************************************/

/*Variaveis para operacao do sistema*/
unsigned char ucEstado      = 0;
unsigned char ucSubestado1  = 0;
unsigned char ucSubestado2  = 0;

/*Variaveis referentes a temperatura*/
unsigned char ucDezTempAlvo     = 0;
unsigned char ucUnTempAlvo      = 0;
unsigned char ucUnTempAtual     = 0;
unsigned char ucDezTempAtual    = 0;

int           iRawTempAtual = 0;
extern const unsigned char tabela_temp[256];


/*Variaveis para manter controle do tempo durante execucao*/
unsigned char ucContador1       = 0;
unsigned char ucContador2       = 0;
unsigned char ucContadorCtrl    = 0;
unsigned char ucSegundos        = 0;
unsigned char ucMinutos         = 0;
unsigned char ucIdleTime        = 0;

/*Variaveis relacionadas aos displays*/
unsigned char ucD7Flag      = 0;
unsigned char ucLCDFrame    = 1;
unsigned char ucDisableD7   = 0;
unsigned char ucLCDFlag     = 0;



/* **************************************************************************** */
/* Nome do metodo:          timerAtt                                            */
/* Descricao:               Callback da interrupcao gerada pelo timer ltpmr0    */
/*                          para controlar os displays e demais elementos       */
/*                          sensiveis ao tempo                                  */
/*                                                                              */
/* Parametros de entrada:   n/a                                                 */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
void timerAtt(){

    ucContador1++;
    ucContador2++;
    ucD7Flag = 1;


}


/* **************************************************************************** */
/* Nome do metodo:          checkTime                                           */
/* Descricao:               Atualiza os contadores de tempo de execucao do      */
/*                          programa                                            */
/*                                                                              */
/* Parametros de entrada:   n/a                                                 */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
void checkTime(){

    /*+1 a cada 100ms*/
    if(25 <= ucContador2){
        ucContador2 = 0;
        ucContadorCtrl++;
    }

    /*+1 a cada 10s*/
    if(2500 <= ucContador1){
        ucLCDFlag ++;

    }
    //zera o contador de controle de dados da uart

}


/* **************************************************************************** */
/* Nome do metodo:          boardInit                                           */
/* Descricao:               Inicializa os perifericos necessarios para o        */
/*                          projeto                                             */
/*                                                                              */
/* Parametros de entrada:   n/a                                                 */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
void boardInit()
{

    /*Inicializa o primeiro LED e os 3 ultimos botoes*/
    /*Botao 2 => "-"; Botao 3 => "+"; Botao 4 => "OK/Reset"*/
	ledSwi_init(1, 0, 0, 0);

    /*Inicializa o Display de 7 segmentos*/
    /*O D7S sera usado para exibir a temperatura atual*/
    display7seg_init();

    /*Inicializa o display LCD*/
    lcd_initLcd();

    /*Inicializa um timer com tick de 4ms para atualizacao dos displays*/
    /*e controle de tempo interno do sistema*/
    tc_installLptmr0(TICK_4MS, timerAtt);

    /*Inicializa o controlador PID para atuar sobre o aquecedor*/ 
    pid_init();
    pid_setKi(FKI);
    pid_setKp(FKP);
    pid_setKd(FKD);

    /*Inicializa a comunicação UART*/ 
    UART0_init(); 

    /*Inicializa o PWM, o ventilador e o aquecedor*/
    PWM_init();
    coolerfan_init(); 
    heater_init();

    /*Iniciar o sensTemp*/

    sensTemp_init();
}

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

void showLCDdisp(unsigned char ucFrame){
    char iAux = 0;

    switch(ucFrame){
        case 0:
            /*Nada*/
            break;

        case 1: // Exibe a temperatura atual, a temperatura alvo e o duty cycle do heater
            lcd_setCursor(LINE0,0);
            lcd_writeString("Temp  C Alvo   C");
            lcd_setCursor(LINE1,0);
            lcd_writeString("DCH  ");

            //Insere temperatura Atual

            lcd_setCursor(LINE0,(5));
            lcd_writeData(ucDezTempAtual+48);
            lcd_setCursor(LINE0,(6));
            lcd_writeData(ucUnTempAtual+48);

            //Insere temperatura Alvo
            lcd_setCursor(LINE0,(14));
            lcd_writeData(ucDezTempAlvo+48);
            lcd_setCursor(LINE0,(15));
            lcd_writeData(ucUnTempAlvo+48);

            //Insere o Duty Cycle do Heater
            unsigned char dch_digits[5];
            sprintf(dch_digits, "%g", fKp);

            for(iAux=0; 5 >= iAux; iAux++){
                lcd_setCursor(LINE1,(6+iAux));
                lcd_writeData(dch_digits[iAux]);
            }


            break;

         case 2: // Exibe os ganhos programados para KP, KI e KD
            lcd_setCursor(LINE0,0);
            lcd_writeString("Kp      Kd      ");
            lcd_setCursor(LINE1,0);
            lcd_writeString("Ki      ");

            // Converte o valor atual de ganho do controlador de float para char
            unsigned char Kp_digits[5];
            sprintf(Kp_digits, "%g", fKp);
            for(iAux=0; 5 >= iAux; iAux++){
                lcd_setCursor(LINE0,(3+iAux));
                lcd_writeData(Kp_digits[iAux]);
            }

            unsigned char Kd_digits[5];
            sprintf(Kd_digits, "%g", fKd);
            for(iAux=0; 5 >= iAux; iAux++){
                lcd_setCursor(LINE0,(11+iAux));
                lcd_writeData(Kd_digits[iAux]);
            }
            
            unsigned char Ki_digits[5];
            sprintf(Ki_digits, "%g", fKi);
            for(iAux=0; 5 >= iAux; iAux++){
                lcd_setCursor(LINE1,(3+iAux));
                lcd_writeData(Ki_digits[iAux]);
            }
            break;

         default:
            break;
    }

}



/* **************************************************************************** */
/* Nome do metodo:          main                                                */
/* Descricao:               Executa o loop principal do programa                */
/*                                                                              */
/*                                                                              */
/* Parametros de entrada:   n/a                                                 */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
int main(void){


    boardInit();

    while(1){

        //iAux será usada para garantir que será enviados dados por 5s, este temp poderá ser alterado
        //Caso perceba-se que não é adequado para obter a curva desejada de resposta.
        int iAux = 1250;

        //Exibe as telas do LCD a cada 10s
        if(ucLCDFlag != 0){ 
            showLCDdisp(ucLCDFlag);
            if(ucLCDFlag >= 2){ 
                ucLCDFlag = 0;
            }
        }



        //Aguarda-se a solcitação de ajuste pela UART do controlador
        if(1 == readSwitch(4)){

            util_genDelay100ms();
        //Vamos inicialmente manter o aquecedor com um duty cyle proximo a zero para
        //observarmos a saída quando subirmos para seu valor máximo permitido de 50% 
            heater_PWMDuty(0.05); 
            //E aguardar um tempo de estabilização 
            for(iAux = 0; 5 > iAux; iAux++){
                util_genDelay100ms();
                util_genDelay100ms();
            }
        

            while(0 != iAux) { // Envia 1250 dados de temperatura pela UART

                    readTemp();
                    //Envia dados para a UART 
                    processByteCommUART('#');
                    util_genDelay1ms();
                    processByteCommUART('g');
                    util_genDelay1ms();
                    processByteCommUART('t');
                    util_genDelay1ms();
                    processByteCommUART(';');
                    util_genDelay1ms();

                    iAux--; //Diminui o número de vezes que enviará os dados

            }
        }

    	checkTime(); 
    	if(0 != ucContadorCtrl){ 
    		readTemp();
    		fDutyCycle_Heater = pidUpdateData(ucTempAtual, ucTempAlvo, fDutyCycle_Heater);
            heater_PWMDuty(fDutyCycle_Heater);
            ucContadorCtrl = 0;
    	}
    }
}

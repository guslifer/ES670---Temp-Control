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
#include "lcdTemp.h"
#include "ledSwi.h"
#include "pid.h"
#include "display7seg.h"
#include "uart.h"


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
ucTempAlvo        = TEMP_DEFAULT;
ucTempAtual       = 0;
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


/* **************************************************************************** */
/* Nome do metodo:          readTemp                                            */
/* Descricao:               Le o ADC conectado ao sensor de temperatura e       */
/*                          converte o valor pela lookup table em graus Celsius */
/*                                                                              */
/* Parametros de entrada:   n/a                                                 */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
void readTemp(){ 

    adc_initConvertion();
    while(0 == adc_isAdcDone())
    {
        util_genDelay250us();
    } 

    iRawTempAtual   = adc_getConvertionValue();
    ucTempAtual     = tabela_temp[iRawTempAtual];
    ucDezTempAtual  = ucTempAtual/10;
    ucUnTempAtual   = ucTempAtual%10;
}



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
    ledSwit_init(1, 0, 0, 0);

    /*Inicializa o Display de 7 segmentos*/
    /*O D7S sera usado para exibir a temperatura atual*/
    display7seg_init();

    /*Inicializa o display LCD*/
    lcdTemp_init();

    /*Inicializa um timer com tick de 4ms para atualizacao dos displays*/
    /*e controle de tempo interno do sistema*/
    tc_installLptmr0(TICK_4MS, timerAtt);

    /*Inicializa o controlador PID para atuar sobre o aquecedor*/ 
    pid_init();
    pid_setKi(FKI);
    pid_setKp(FKP);
    pid_setKD(FKD);

    /*Inicializa a comunicação UART*/ 
    UART0_init(); 

    /*Inicializa o PWM, o ventilador e o aquecedor*/
    PWM_init();
    coolerfan_init(); 
    heater_init();
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

    	checkTime(); 
    	if(0 != ucContadorCtrl){ 

            fDutyCycleHeater = pidUpdateDate(ucTempAtual, ucTempAlvo, fDutyCycleHeater); 
            heater_PWMDuty(fDutyCycleHeater)


    	}


 
	}
}
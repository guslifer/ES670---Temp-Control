/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        main.c                                                 */
/*                                                                                  */
/*   Descricao:             Projeto final do controlador de temperatura com         */
/*                          interface                                               */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo A. Dollevedo                    */
/*   Criado em:              27/07/2020                                             */
/*   Ultima revisao em:      27/07/2020                                             */
/* ******************************************************************************** */

/* Incluindo bibliotecas */
#include "board.h"  
#include "util.h"
#include "adc.h"
#include "lut_adc_3v3.h"
#include "lptmr.h"
#include "lcd.h"
#include "ledSwi.h"


/********************************************************************************/
/********************           DECLARANDO CONSTANTES       *********************/

/*Temperatura padrao*/
#define TEMP_DEFAULT 30;

/*Tick base do timer*/
#define TICK_4MS     4000;

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

/********************           FIM DAS CONSTANTES          *********************/
/********************************************************************************/

/*Variaveis para operacao do sistema*/
unsigned char ucEstado      = 0;
unsigned char ucSubestado1  = 0;
unsigned char ucSubestado2  = 0;

/*Variaveis referentes a temperatura*/
unsigned char ucTempAlvo    = TEMP_DEFAULT;
unsigned char ucTempAtual   = 0;
unsigned char ucDezTempAlvo = 0;
unsigned char ucUnTempAlvo  = 0;


/*Variaveis para manter controle do tempo durante execucao*/
unsigned char ucContador1   = 0;
unsigned char ucSegundos    = 0;
unsigned char ucMinutos     = 0;
unsigned char ucIdleTime    = 0;

/*Variaveis relacionadas aos displays*/
unsigned char ucD7Flag      = 0;
unsigned char ucLCDFrame    = 0;

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
    if(25 <= ucContador1){
        ucContador1 = 0;
        ucSegundos++;
    }

    if(60 <= ucSegundos){
        ucSegundos = 0;
        ucMinutos++;
    
        if(CONFIG == ucEstado){
            ucIdleTime++;
        }
    }



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

    switch

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
    display7seg_init()

    /*Inicia um timer com tick de 4ms para atualizacao dos displays*/
    /*e controle de tempo interno do sistema*/
    tc_installLptmr0(TICK_4MS, timerAtt);
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


    ucEstado        = CONFIG;
    ucSubestado1    = DEZENA;
    ucSubestado2    = STATE_0;

    /*Tem que ser feita a atualizacao dos displays (LCD e D7S)*/

    while(1){


        checkTime();

        if(0 != ucD7Flag){
            /*TBD: EXIBE TEMPERATURA ATUAL*/
        }

        /*Atualiza o LCD com o frame correto*/
        /*TBD!!!*/
        showLCDdisp(ucLCDFrame);

        /*Se o sistema fica inoperado por 2 minutos, uma temperatura padrao eh*/
        /*setada, e o sistema passa para o estado de CONTROLE*/
        if(2 == ucIdleTime){
            ucIdleTime = 0;
            ucTempAlvo = TEMP_DEFAULT;
            ucDezTempAlvo = ucTempAlvo/10;
            ucUnTempAlvo  = ucTempAlvo%10;
            ucEstado = CONTROLE;
            ucSubestado1 = DEZENA;
            ucSubestado2 = STATE_0;
        }

        /*INICIA A MAQUINA DE ESTADOS DO SISTEMA*/
        switch (ucEstado){

        /*ESTADO DE CONFIGURACAO DA TEMPERATURA ALVO*/
        case CONFIG:
            switch(ucSubestado1){

            /*ESTADO PARA CONFIGURACAO DO DIGITO DA DEZENA*/
            case DEZENA:
                switch(ucSubestado2){
                /*ESTADO PARA DIGITO == 0*/
                case STATE_0:
                    /*Caso "OK" pressionado*/
                    if(1 == readSwitch(4)){
                        /*TBD: Armazenar a dezena atual e passar para o estado da unidade*/
                        /*TBD: ATUALIZAR LCD*/
                        util_genDelay100ms();
                        ucSubestado1 = UNIDADE;
                        ucSubestado2 = STATE_0;
                        break;
                    }

                    /*Caso "+" pressionado*/
                    else if(1 == readSwitch(3)){
                        util_genDelay100ms();
                        ucDezTempAlvo++;
                        ucSubestado2 = STATE_N;
                        break;  
                    }

                    /*Caso "-" pressionado*/
                    else if(1 == readSwitch(2)){
                        /*TBD: Altera para o estado 0*/
                        /*TBD: Atualizar display e valor da temperatura*/
                        util_genDelay100ms();
                        ucSubestado2 = STATE_0;
                        break;
                    }

                /*ESTADO PARA 0 < DIGITO < 9*/
                case STATE_N:
                    /*Caso "OK" pressionado*/
                    if(1 == readSwitch(4)){
                        /*TBD: Armazenar a dezena atual e passar para o estado da unidade*/
                        /*TBD: ATUALIZAR LCD*/
                        util_genDelay100ms();
                        ucSubestado1 = UNIDADE;
                        ucSubestado2 = STATE_0;
                        break;
                    }

                    /*Caso "+" pressionado*/
                    else if(1 == readSwitch(3)){
                        util_genDelay100ms();
                        if(8 == ucDezTempAlvo){
                            ucDezTempAlvo++;
                            ucSubestado2 = STATE_9;
                        }

                        else{
                            ucDezTempAlvo++;
                            ucSubestado2 = STATE_N;
                        }
                        break;
                    }
                    
                    /*Caso "-" pressionado*/
                    else if(1 == readSwitch(2)){
                        /*TBD: Altera para o estado N*/
                        /*TBD: Atualizar display e valor da temperatura*/
                        util_genDelay100ms();

                        if(1 == ucUnTempAlvo){
                            ucDezTempAlvo--;
                            ucSubestado2 = STATE_0;
                        }

                        else{
                            ucDezTempAlvo--;
                            ucSubestado2 = STATE_N;
                        }
                        break;
                    }

                /*ESTADO PARA DIGITO == 9*/
                case STATE_9:
                    /*Caso "OK" pressionado*/
                    if(1 == readSwitch(4)){
                        /*TBD: Armazenar a dezena atual e passar para o estado UNIDADE e para STATE_0*/
                        /*TBD: ATUALIZAR LCD*/
                        util_genDelay100ms();
                        ucSubestado1 = UNIDADE;
                        ucSubestado2 = STATE_0;
                        break;
                    }

                    /*Caso "+" pressionado*/
                    else if(1 == readSwitch(3)){
                        /*Nada acontece*/
                        util_genDelay100ms();
                        ucSubestado2 = STATE_9;
                        break;
                    }
                    
                    /*Caso "-" pressionado*/
                    else if(1 == readSwitch(2)){
                        /*TBD: Altera para o estado N*/
                        /*TBD: Atualizar display e valor da temperatura*/
                        util_genDelay100ms();
                        ucDezTempAlvo--;
                        ucSubestado2 = STATE_N;
                        break;
                    }
                }

            /*ESTADO PARA CONFIGURACAO DO DIGITO DA UNIDADE*/
            case UNIDADE:
                switch(ucSubestado2){
                /*ESTADO PARA DIGITO == 0*/
                case STATE_0:
                    /*Caso "OK" pressionado*/
                    if(1 == readSwitch(4)){
                        /*TBD: Armazenar a unidade atual e passar para o controle*/
                        /*TBD: ATUALIZAR LCD*/
                        util_genDelay100ms();
                        ucSubestado1 = DEZENA;
                        ucSubestado2 = STATE_0;
                        ucEstado     = CONTROLE;
                        ucTempAlvo = ((10*ucDezTempAlvo)+ucUnTempAlvo);
                        break;
                    }

                    /*Caso "+" pressionado*/
                    else if(1 == readSwitch(3)){
                        util_genDelay100ms();
                        ucUnTempAlvo++;
                        ucSubestado2 = STATE_N;
                        break;  
                    }

                    /*Caso "-" pressionado*/
                    else if(1 == readSwitch(2)){
                        /*TBD: Altera para o estado 0*/
                        /*TBD: Atualizar display e valor da temperatura*/
                        util_genDelay100ms();
                        ucSubestado2 = STATE_0;
                        break;
                    }

                /*ESTADO PARA 0 < DIGITO < 9*/
                case STATE_N:
                    /*Caso "OK" pressionado*/
                    if(1 == readSwitch(4)){
                        /*TBD: Armazenar a dezena atual e passar para o estado da unidade*/
                        /*TBD: ATUALIZAR LCD*/
                        util_genDelay100ms();
                        ucSubestado1 = DEZENA;
                        ucSubestado2 = STATE_0;
                        ucEstado     = CONTROLE;
                        ucTempAlvo = ((10*ucDezTempAlvo)+ucUnTempAlvo);
                        break;
                    }

                    /*Caso "+" pressionado*/
                    else if(1 == readSwitch(3)){
                        util_genDelay100ms();
                        if(8 == ucUnTempAlvo){
                            ucUnTempAlvo++;
                            ucSubestado2 = STATE_9;
                        }

                        else{
                            ucUnTempAlvo++;
                            ucSubestado2 = STATE_N;
                        }
                        break;
                    }
                    
                    /*Caso "-" pressionado*/
                    else if(1 == readSwitch(2)){
                        /*TBD: Altera para o estado N*/
                        /*TBD: Atualizar display e valor da temperatura*/
                        util_genDelay100ms();

                        if(1 == ucUnTempAlvo){
                            ucUnTempAlvo--;
                            ucSubestado2 = STATE_0;
                        }

                        else{
                            ucUnTempAlvo--;
                            ucSubestado2 = STATE_N;
                        }
                        break;
                    }

                /*ESTADO PARA DIGITO == 9*/
                case STATE_9:
                    /*Caso "OK" pressionado*/
                    if(1 == readSwitch(4)){
                        /*TBD: Armazenar a dezena atual e passar para o estado UNIDADE e para STATE_0*/
                        /*TBD: ATUALIZAR LCD*/
                        util_genDelay100ms();
                        ucSubestado1 = DEZENA;
                        ucSubestado2 = STATE_0;
                        ucEstado     = CONTROLE;
                        ucTempAlvo = ((10*ucDezTempAlvo)+ucUnTempAlvo);
                        break;
                    }

                    /*Caso "+" pressionado*/
                    else if(1 == readSwitch(3)){
                        /*Nada acontece*/
                        util_genDelay100ms();
                        ucSubestado2 = STATE_9;
                        break;
                    }
                    
                    /*Caso "-" pressionado*/
                    else if(1 == readSwitch(2)){
                        /*TBD: Altera para o estado N*/
                        /*TBD: Atualizar display e valor da temperatura*/
                        util_genDelay100ms();
                        ucUnTempAlvo--;
                        ucSubestado2 = STATE_N;
                        break;
                    }
                }
            }
            break;

        /*ESTADO DE CONTROLE DE TEMPERATURA*/
        case CONTROLE:
            break;

                //Numa mão ta o copção com whisky e red bull
                // Na outra o lança perfume 
                //encomendei mais um
        }
    }
}

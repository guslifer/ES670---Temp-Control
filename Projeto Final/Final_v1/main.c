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
#include "pid.h"


/********************************************************************************/
/********************           DECLARANDO CONSTANTES       *********************/

/*Temperatura*/
#define TEMP_DEFAULT 30;
extern const unsigned char tabela_temp[256];

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
unsigned char ucTempAlvo    = TEMP_DEFAULT;
unsigned char ucTempAtual   = 0;
unsigned char ucDezTempAlvo = 0;
unsigned char ucUnTempAlvo  = 0;
int           iRawTempAtual = 0;


/*Variaveis para manter controle do tempo durante execucao*/
unsigned char ucContador1       = 0;
unsigned char ucContadorCtrl    = 0;
unsigned char ucSegundos        = 0;
unsigned char ucMinutos         = 0;
unsigned char ucIdleTime        = 0;

/*Variaveis relacionadas aos displays*/
unsigned char ucD7Flag      = 0;
unsigned char ucLCDFrame    = 1;


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
void readTemp(){ 

    adc_initConvertion();
    while(0 == adc_isAdcDone())
    {
        util_genDelay250us();
    } 

    iRawTempAtual = adc_getConvertionValue();
    ucTempAtual   = tabela_temp[iRawTempAtual];
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

    if(25 <= ucContador1){ //A cada 100ms
        ucContador1 = 0;
        ucContadorCtrl++;
    }


    if(250 <= ucContador1){ //Acho que ta errado aqui
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

    switch(ucFrame){
    case 0:
        /*Nada*/
        break;

    case 1:
        lcd_setCursor(LINE0,0);
        lcd_writeString("Configure a Temp");
        lcd_setCursor(LINE1,0);
        lcd_writeString("Temp Alvo: 00C");
        break;

     case 2:
        lcd_setCursor(LINE0,0);
        lcd_writeString("UART HABILITADO");
        lcd_setCursor(LINE1,0);
        lcd_writeString("Temp Alvo:   C");
        lcd_setCursor(LINE1,11);
        lcd_writeData(ucDezTempAlvo);
        lcd_setCursor(LINE1,12);
        lcd_writeData(ucUnTempAlvo);
        break;

     default:
         break;
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
    lcd_initLcd();

    /*Inicia um timer com tick de 4ms para atualizacao dos displays*/
    /*e controle de tempo interno do sistema*/
    tc_installLptmr0(TICK_4MS, timerAtt);

    /*Inicia o controlador PID*/ 
    pid_init();
    pid_setKi(FKI);
    pid_setKp(FKP);
    pid_setKD(FKD);

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
        /*1 -> CONFIG; 2 -> CONTROLE*/
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
            turnOnLED(1);
            ucLCDFrame = 0;

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
                        lcd_setCursor(LINE1,11);
                        lcd_writeData(ucDezTempAlvo+48);
                        ucSubestado2 = STATE_N;
                        break;  
                    }

                    /*Caso "-" pressionado*/
                    else if(1 == readSwitch(2)){
                        /*TBD: Altera para o estado 0*/
                        /*TBD: Atualizar display e valor da temperatura*/
                        util_genDelay100ms();
                        lcd_setCursor(LINE1,11);
                        lcd_writeData(ucDezTempAlvo+48);
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
                            lcd_setCursor(LINE1,11);
                            lcd_writeData(ucDezTempAlvo+48);
                            ucSubestado2 = STATE_9;
                        }

                        else{
                            ucDezTempAlvo++;
                            lcd_setCursor(LINE1,11);
                            lcd_writeData(ucDezTempAlvo+48);
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
                            lcd_setCursor(LINE1,11);
                            lcd_writeData(ucDezTempAlvo+48);
                            ucSubestado2 = STATE_0;
                        }

                        else{
                            ucDezTempAlvo--;
                            lcd_setCursor(LINE1,11);
                            lcd_writeData(ucDezTempAlvo+48);
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
                        lcd_setCursor(LINE1,11);
                        lcd_writeData(ucDezTempAlvo+48);
                        ucSubestado2 = STATE_9;
                        break;
                    }
                    
                    /*Caso "-" pressionado*/
                    else if(1 == readSwitch(2)){
                        /*TBD: Altera para o estado N*/
                        /*TBD: Atualizar display e valor da temperatura*/
                        util_genDelay100ms();
                        ucDezTempAlvo--;
                        lcd_setCursor(LINE1,11);
                        lcd_writeData(ucDezTempAlvo+48);
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
                        ucLCDFrame = 2;
                        ledSwit_init(1, 1, 1, 0);                        
                        break;
                    }

                    /*Caso "+" pressionado*/
                    else if(1 == readSwitch(3)){
                        util_genDelay100ms();
                        ucUnTempAlvo++;
                        lcd_setCursor(LINE1,12);
                        lcd_writeData(ucUnTempAlvo+48);
                        ucSubestado2 = STATE_N;
                        break;  
                    }

                    /*Caso "-" pressionado*/
                    else if(1 == readSwitch(2)){
                        /*TBD: Altera para o estado 0*/
                        /*TBD: Atualizar display e valor da temperatura*/
                        util_genDelay100ms();
                        lcd_setCursor(LINE1,12);
                        lcd_writeData(ucUnTempAlvo+48);
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
                        ucLCDFrame = 2;
                        ledSwit_init(1, 1, 1, 0);                        
                        break;
                    }

                    /*Caso "+" pressionado*/
                    else if(1 == readSwitch(3)){
                        util_genDelay100ms();
                        if(8 == ucUnTempAlvo){
                            ucUnTempAlvo++;
                            lcd_setCursor(LINE1,12);
                            lcd_writeData(ucUnTempAlvo+48);
                            ucSubestado2 = STATE_9;
                        }

                        else{
                            ucUnTempAlvo++;
                            lcd_setCursor(LINE1,12);
                            lcd_writeData(ucUnTempAlvo+48);
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
                            lcd_setCursor(LINE1,12);
                            lcd_writeData(ucUnTempAlvo+48);
                            ucSubestado2 = STATE_0;
                        }

                        else{
                            ucUnTempAlvo--;
                            lcd_setCursor(LINE1,12);
                            lcd_writeData(ucUnTempAlvo+48);
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
                        ledSwit_init(1, 1, 1, 0);
                        ucLCDFrame = 2;
                        break;
                    }

                    /*Caso "+" pressionado*/
                    else if(1 == readSwitch(3)){
                        /*Nada acontece*/
                        util_genDelay100ms();
                        lcd_setCursor(LINE1,12);
                        lcd_writeData(ucUnTempAlvo+48);
                        ucSubestado2 = STATE_9;
                        break;
                    }
                    
                    /*Caso "-" pressionado*/
                    else if(1 == readSwitch(2)){
                        /*TBD: Altera para o estado N*/
                        /*TBD: Atualizar display e valor da temperatura*/
                        util_genDelay100ms();
                        ucUnTempAlvo--;
                        lcd_setCursor(LINE1,12);
                        lcd_writeData(ucUnTempAlvo+48);
                        ucSubestado2 = STATE_N;
                        break;
                    }
                }
            }
            break;

        /*ESTADO DE CONTROLE DE TEMPERATURA*/
        case CONTROLE:
            ucLCDFrame = 2;
            /*Inicializa os 3 primeiros LEDs e o ultimo botao*/
            /*Botao 4 => "/Reset"*/
            turnOffLED(1);

            /*NOVA ATUALIZAÇÃO DE CONTROLE NECESSÁRIA*/
            if(0 != ucContadorCtrl) { 

                fDutyCycleHeater = pidUpdateDate(ucTempAtual, ucTempAlvo, fDutyCycleHeater); 
                heater_PWMDuty(fDutyCycleHeater)
            }
            /*DEVE INDICAR SE A TEMPERATURA ESTA ACIMA OU ABAIXO DO ALVO*/
            if(ucTempAtual > ucTempAlvo){ 
                turnOffLED(2);
                turnOffLED(3);  
                turnOnLED(3);
            }

            else if(ucTempAtual < ucTempAlvo){  
                turnOffLED(2);
                turnOffLED(3);  
                turnOnLED(2)
            }
            /*DEVE RETORNAR PARA O MENU DE CONFIGURACAO CASO O BOTAO OK SEJA PRESSIOANDO*/
            if(1 == readSwitch(4)){
                util_genDelay100ms();
                ucSubestado1 = UNIDADE;
                ucSubestado2 = STATE_0;
                ucEstado = CONFIG;
                ledSwit_init(1, 0, 0, 0);
                break;
            }

        
            break;
        }
    }
}

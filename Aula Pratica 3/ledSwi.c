/* #######################################
    Nome do arquivo:        ledSwi.c 
    Descrição:              As funções de atuação do 
                            micro-controlador com os periféricos
                            de chave e leds.
    Autores:                Gustavo Lino e Giácomo Dollevedo
    Criado em:              29/03/2020 
#########################################*/

#include "ledSwi.h"


#include "fsl_clock_manager.h"
#include "fsl_port_hal.h"
#include "fsl_gpio_hal.h"


#define uiPort1MaskEnable       0x02
#define uiPort1MaskDisable      0xFFFD
#define uiPort2MaskEnable       0x04
#define uiPort2MaskDisable      0xFFFB
#define uiPort4MaskEnable       0x010
#define uiPort4MaskDisable      0xFFEF
#define uiPort5MaskEnable       0x020
#define uiPort5MaskDisable      0xFFDF


/*A função ledSwi_init recebe os valores configuraveis para cada porta, 
para o usiario determinar quais serão os pinos de 1 a 4:
para led (1) ou para chave (0) 
As portas, de acordo com o arquivo KL25Z_ADAPTER_MCLAB2 serão
PTA1, PTA2, PTA4, PTA5 */

void ledSwi_init(bool led1, bool led2, bool led3, bool led4) { 
/* ativar o clock para a porta A*/ 
    SIM_SCGC5 |= 0x0200; 

/*Configura os pinos das portas para GPIO*/

    PORTA_PCR1 |= 0x100; 
    PORTA_PCR2 |= 0x100; 
    PORTA_PCR4 |= 0x100; 
    PORTA_PCR5 |= 0x100; 

/*Define se os pinos serao entrada (chave) ou saida (led)*/ 

    if(led1 == 1){
        GPIOA_PDDR |= uiPort1MaskEnable
    }
    else{ 
        GPIOA_PDDR &= uiPort1MaskDisable
    } 

    if(led2 == 1){
        GPIOA_PDDR |= uiPort2MaskEnable
    }
    else{ 
        GPIOA_PDDR &= uiPort2MaskDisable
    } 

    if(led3== 1){
        GPIOA_PDDR |= uiPort4MaskEnable
    }
    else{ 
        GPIOA_PDDR &= uiPort4MaskDisable
    } 

    if(led4 == 1){
        GPIOA_PDDR |= uiPort5MaskEnable
    }
    else{ 
        GPIOA_PDDR &= uiPort5MaskDisable
    } 

}



/* **************************************************************************/
/* Nome do metodo:          readSwitch                  
/* Descrição:               Le o status de um switch para saber se o mesmo
/*                          está pressionado ou não
/*
/* Parametros de entrada:   Um inteiro (0<n<5) que indica qual botão será lido
/*                          inicializado como entrada (botao) ou saida (LED)
/*                          0 -> Leitura PTA1; 1 -> Leitura PTA2, 
/*                          2 -> Leitura PTA4; 3 -> Leitura PTA5;
/*
/* Parametros de saida:     Um booleano indicando se o botao lido está sendo
/*                          pressionado (true), se não está ou se é inválido
/*                          (false)                          
/* **************************************************************************/
bool readSwitch(int n){ 

    switch(n){
        case 1: 
            if (uiPort1MaskEnable == GPIOA_PDIR & uiPort1MaskEnable){ 
                return true
            }
            else {
                return false
            }
        break;

        case 2: 
            if (uiPort2Mask == GPIOA_PDIR & uiPort2MaskEnable){ 
                return true
            }
            else {
                return false
            }
        break;

        case 3: 
        if (uiPort4Mask == GPIOA_PDIR & uiPort4MaskEnable){ 
            return true
        }
        else {
            return false
        }
        break;

        case 4: 
            if (uiPort5Mask == GPIOA_PDIR & uiPort5MaskEnable){ 
                return true
            }
            else {
                return false
            }
        break;

        }

    }



/* **************************************************************************/
/* Nome do metodo:          writeLED                  
/* Descrição:               Liga ou desliga o LED selecionado conforme as
/*                          entradas
/*
/* Parametros de entrada:   Um inteiro (0<n<5) indicando sobre qual LED sera
/*                          efetuado o comando;
/*                          Um booleano (status) indicando se o LED sera
/*                          aceso (true) ou apagado (false)
/*
/* Parametros de saida:     n/a                          
/* **************************************************************************/
void writeLED(int n, bool status){

    switch(n){
        case 1: 
            if (status){ 
                GPIOA_PDOR |= uiPort1MaskEnable
            }
            else {
                GPIOA_PDOR |= uiPort1MaskDisable
            }
        break;

        case 2: 
            if (status){ 
                GPIOA_PDOR |= uiPort2MaskEnable
            }
            else {
                GPIOA_PDOR |= uiPort2MaskDisable
            }
        break;

        case 3: 
            if (status){ 
                GPIOA_PDOR |= uiPort4MaskEnable
        }
            else {
                GPIOA_PDOR |= uiPort4MaskDisable
        }
        break;

        case 4: 
            if (status){ 
                GPIOA_PDOR |= uiPort5MaskEnable
            }
            else {
                GPIOA_PDOR |= uiPort5MaskDisable
            }
        break;

    }

}


/* **************************************************************************/
/* Nome do metodo:          turnOnLED                  
/* Descrição:               Liga um LED especificado pela entrada
/*
/* Parametros de entrada:   Um inteiro (0<n<5) indicando qual LED sera aceso
/*
/* Parametros de saida:     n/a                          
/* **************************************************************************/
void turnOnLED(int n);


    switch(n){
        case 1:  
            GPIOA_PSOR |= uiPort1MaskEnable
        break;

        case 2: 
            
            GPIOA_PSOR |= uiPort2MaskEnable

        break;

        case 3: 

            GPIOA_PSOR |= uiPort4MaskEnable

        break;

        case 4: 

            GPIOA_PSOR |= uiPort5MaskEnable

        break;

    }



/* **************************************************************************/
/* Nome do metodo:          turnOffLED                  
/* Descrição:               Desliga um LED especificado pela entrada
/*
/* Parametros de entrada:   Um inteiro (0<n<5) indicando qual LED sera apagado
/*
/* Parametros de saida:     n/a                          
/* **************************************************************************/
void turnOffLED(int n){ 



    switch(n){
        case 1:  
            GPIOA_PCOR |= uiPort1MaskDisable
        break;

        case 2: 
            
            GPIOA_PCOR |= uiPort2MaskDisable

        break;

        case 3: 

            GPIOA_PCOR |= uiPort4MaskDisable

        break;

        case 4: 

            GPIOA_PCOR |= uiPort5MaskDisable

        break;

    }
}



/* **************************************************************************/
/* Nome do metodo:          toggleLED                  
/* Descrição:               Inverte o status atual de um LED especificado pela
/*                          entrada
/*
/* Parametros de entrada:   Um inteiro (0<n<5) indicando qual LED tera seu
/*                          status invertido
/*
/* Parametros de saida:     n/a                          
/* **************************************************************************/
void toggleLED(int n){

    switch(n){
        case 1:  
            GPIOA_PTOR |= uiPort1MaskEnable
        break;

        case 2: 
            
            GPIOA_PTOR |= uiPort2MaskEnable

        break;

        case 3: 

            GPIOA_PTOR |= uiPort4MaskEnable

        break;

        case 4: 

            GPIOA_PTOR |= uiPort5MaskEnable

        break;

    }


}
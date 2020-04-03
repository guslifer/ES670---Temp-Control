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


/*A função ledSwi_init recebe os valores configuraveis para cada porta, 
para o usiario determinar quais serão os pinos de 1 a 4:
para led (1) ou para chave (0) 
As portas, de acordo com o arquivo KL25Z_ADAPTER_MCLAB2 serão
PTA1, PTA2, PTA4, PTA5 */

bool ledSwi1 = 0, ledSwi2 = 0, ledSwi3 = 0, ledSwi4 = 0;

void ledSwi_init(bool led1, bool led2, bool led3, bool led4) { 
/* ativar o clock para a porta A*/ 
    SIM_SCGC5 |= uiSetClockPort; 

/*Configura os pinos das portas para GPIO*/

    PORTA_PCR1 |= uiSetPinAsGPIO; 
    PORTA_PCR2 |= uiSetPinAsGPIO; 
    PORTA_PCR4 |= uiSetPinAsGPIO; 
    PORTA_PCR5 |= uiSetPinAsGPIO; 

/*Define se os pinos serao entrada (chave) ou saida (led)*/ 

    if(led1 == 1){
        GPIOA_PDDR |= uiPin1MaskEnable;
        ledSwi1 = true;
    }
    else{ 
        GPIOA_PDDR &= uiPin1MaskDisable;
        ledSwi1 = false;
    } 

    if(led2 == 1){
        GPIOA_PDDR |= uiPin2MaskEnable;
        ledSwi2 = true;
    }
    else{ 
        GPIOA_PDDR &= uiPin2MaskDisable;
        ledSwi2 = false;
    } 

    if(led3== 1){
        GPIOA_PDDR |= uiPin4MaskEnable;
        ledSwi3 = true;
    }
    else{ 
        GPIOA_PDDR &= uiPin4MaskDisable;
        ledSwi3 = false;
    } 

    if(led4 == 1){
        GPIOA_PDDR |= uiPin5MaskEnable;
        ledSwi4 = true;
    }
    else{ 
        GPIOA_PDDR &= uiPin5MaskDisable;
        ledSwi4 = false;
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
        	if(false == ledSwi1){
	            if (uiPin1MaskEnable == GPIOA_PDIR & uiPin1MaskEnable){ 
	                return true;
	            }
	            else {
	                return false;
	            }
        	}
        	else{
        		printf("Erro 2");
        	}
        break;

        case 2:
        	if(false == ledSwi2){ 
	            if (uiPin2Mask == GPIOA_PDIR & uiPin2MaskEnable){ 
	                return true;
	            }
	            else {
	                return false;
	            }
        	}
        	else{ 
        		printf("Erro 2");
        	}
        break;

        case 3: 
        	if(false == ledSwi3){
		        if (uiPin4Mask == GPIOA_PDIR & uiPin4MaskEnable){ 
		            return true;
		        }
		        else {
		            return false;
		        }
		    }
		    else{ 
        		printf("Erro 2");
        	}
		break;

        case 4: 
        	if(false == ledSwi4){
	            if (uiPin5Mask == GPIOA_PDIR & uiPin5MaskEnable){ 
	                return true;
	            }
	            else {
	                return false;
	            }
	        }
	    else{ 
        		printf("Erro 2");
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
        	if(true == ledSwi1){ 
	            if (status){ 
	                GPIOA_PDOR |= uiPin1MaskEnable;
	            }
	            else {
	                GPIOA_PDOR |= uiPin1MaskDisable;
	            }
        	}
        	else{ 
        		printf("Erro 3");
        	}
        break;

        case 2: 
        	if(true == ledSwi2){
	            if (status){ 
	                GPIOA_PDOR |= uiPin2MaskEnable;
	            }
	            else {
	                GPIOA_PDOR |= uiPin2MaskDisable;
	            }
	        }
	        else{ 
        		printf("Erro 3");
        	}

        break;

        case 3: 
        	if(true == ledSwi3){
	            if (status){ 
	                GPIOA_PDOR |= uiPin4MaskEnable;
	        	}
	            else {
	                GPIOA_PDOR |= uiPin4MaskDisable;
	        	}
	        }
	        else{ 
        		printf("Erro 3");
        	}
        break;

        case 4: 
        	if(true == ledSwi4){
	            if (status){ 
	                GPIOA_PDOR |= uiPin5MaskEnable;
	            }
	            else {
	                GPIOA_PDOR |= uiPin5MaskDisable;
	            }
	        } 
		    else{ 
	        		printf("Erro 3");
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
void turnOnLED(int n){ 


    switch(n){

        case 1:  
        	if(true == ledSwi1){
            	GPIOA_PSOR |= uiPin1MaskEnable;
            } 
            else{ 
	        		printf("Erro 3");
	        	}
        break;

        case 2: 
            if(true == ledSwi2){
            	GPIOA_PSOR |= uiPin2MaskEnable;
            } 
            else{ 
	        		printf("Erro 3");
	        	}

        break;

        case 3: 
        	if(true == ledSwi3){
            	GPIOA_PSOR |= uiPin4MaskEnable;
            }
            else{ 
            	printf("Erro 3");
            }		
        break;

        case 4: 
        	if(true == ledSwi4){
            	GPIOA_PSOR |= uiPin5MaskEnable;
            }
            else{ 
            	printf("Erro 3");
            }	
        break;

    }
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
        	if(true == ledSwi1){
            	GPIOA_PCOR |= uiPin1MaskDisable;
            } 
            else{ 
	        		printf("Erro 3");
	        	}
        break;

        case 2: 
            if(true == ledSwi2){
            	GPIOA_PCOR |= uiPin2MaskDisable;
            } 
            else{ 
	        		printf("Erro 3");
	        	}

        break;

        case 3: 
        	if(true == ledSwi3){
            	GPIOA_PCOR |= uiPin4MaskDisable;
            }
            else{ 
            	printf("Erro 3");
            }		
        break;

        case 4: 
        	if(true == ledSwi4){
            	GPIOA_PCOR |= uiPin5MaskDisable;
            }
            else{ 
            	printf("Erro 3");
            }	
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
        	if(true == ledSwi1){
            	GPIOA_PTOR |= uiPin1MaskEnable;
            } 
            else{ 
	        		printf("Erro 3");
	        	}
        break;

        case 2: 
            if(true == ledSwi2){
            	GPIOA_PTOR |= uiPin2MaskEnable;
            } 
            else{ 
	        		printf("Erro 3");
	        	}

        break;

        case 3: 
        	if(true == ledSwi3){
            	GPIOA_PTOR |= uiPin4MaskEnable;
            }
            else{ 
            	printf("Erro 3");
            }		
        break;

        case 4: 
        	if(true == ledSwi4){
            	GPIOA_PTOR |= uiPin5MaskEnable;
            }
            else{ 
            	printf("Erro 3");
            }	
        break;

    } 
}
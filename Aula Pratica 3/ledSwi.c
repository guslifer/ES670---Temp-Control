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
        GPIOA_PDDR |= uiPort1MaskEnable
        ledSwi1 = true;
    }
    else{ 
        GPIOA_PDDR &= uiPort1MaskDisable
        ledSwi1 = false;
    } 

    if(led2 == 1){
        GPIOA_PDDR |= uiPort2MaskEnable
        ledSwi2 = true;
    }
    else{ 
        GPIOA_PDDR &= uiPort2MaskDisable
        ledSwi2 = false;
    } 

    if(led3== 1){
        GPIOA_PDDR |= uiPort4MaskEnable
        ledSwi3 = true;
    }
    else{ 
        GPIOA_PDDR &= uiPort4MaskDisable
        ledSwi3 = false;
    } 

    if(led4 == 1){
        GPIOA_PDDR |= uiPort5MaskEnable
        ledSwi4 = true;
    }
    else{ 
        GPIOA_PDDR &= uiPort5MaskDisable
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
        	if(ledSwi1 = false){
	            if (uiPort1MaskEnable == GPIOA_PDIR & uiPort1MaskEnable){ 
	                return true
	            }
	            else {
	                return false
	            }
        	}
        	else{
        		printf("Erro 2")
        	}
        break;

        case 2:
        	if(ledSwi2 = false){ 
	            if (uiPort2Mask == GPIOA_PDIR & uiPort2MaskEnable){ 
	                return true
	            }
	            else {
	                return false
	            }
        	}
        	else{ 
        		printf("Erro 2")
        	}
        break;

        case 3: 
        	if(ledSwi3 = false){
		        if (uiPort4Mask == GPIOA_PDIR & uiPort4MaskEnable){ 
		            return true
		        }
		        else {
		            return false
		        }
		    }
		    else{ 
        		printf("Erro 2")
        	}
		break;

        case 4: 
        	if(ledSwi4 = false){
	            if (uiPort5Mask == GPIOA_PDIR & uiPort5MaskEnable){ 
	                return true
	            }
	            else {
	                return false
	            }
	        }
	    else{ 
        		printf("Erro 2")
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
        	if(ledSwi1 = true){ 
	            if (status){ 
	                GPIOA_PDOR |= uiPort1MaskEnable
	            }
	            else {
	                GPIOA_PDOR |= uiPort1MaskDisable
	            }
        	}
        	else{ 
        		printf("Erro 3")
        	}
        break;

        case 2: 
        	if(ledSwi2 = true){
	            if (status){ 
	                GPIOA_PDOR |= uiPort2MaskEnable
	            }
	            else {
	                GPIOA_PDOR |= uiPort2MaskDisable
	            }
	        }
	        else{ 
        		printf("Erro 3")
        	}

        break;

        case 3: 
        	if(ledSwi3 = true){
	            if (status){ 
	                GPIOA_PDOR |= uiPort4MaskEnable
	        	}
	            else {
	                GPIOA_PDOR |= uiPort4MaskDisable
	        	}
	        }
	        else{ 
        		printf("Erro 3")
        	}
        break;

        case 4: 
        	if(ledSwi4 = true){
	            if (status){ 
	                GPIOA_PDOR |= uiPort5MaskEnable
	            }
	            else {
	                GPIOA_PDOR |= uiPort5MaskDisable
	            }
	        } 
		    else{ 
	        		printf("Erro 3")
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
        	if(ledSwi1 = true){
            	GPIOA_PSOR |= uiPort1MaskEnable
            } 
            else{ 
	        		printf("Erro 3")
	        	}
        break;

        case 2: 
            if(ledSwi2 = true){
            	GPIOA_PSOR |= uiPort2MaskEnable
            } 
            else{ 
	        		printf("Erro 3")
	        	}

        break;

        case 3: 
        	if(ledSwi3 = true){
            	GPIOA_PSOR |= uiPort4MaskEnable
            }
            else{ 
            	printf("Erro 3")
            }		
        break;

        case 4: 
        	if(ledSwi3 = true){
            	GPIOA_PSOR |= uiPort5MaskEnable
            }
            else{ 
            	printf("Erro 3")
            }	
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
        	if(ledSwi1 = true){
            	GPIOA_PCOR |= uiPort1MaskDisable
            } 
            else{ 
	        		printf("Erro 3")
	        	}
        break;

        case 2: 
            if(ledSwi2 = true){
            	GPIOA_PCOR |= uiPort2MaskDisable
            } 
            else{ 
	        		printf("Erro 3")
	        	}

        break;

        case 3: 
        	if(ledSwi3 = true){
            	GPIOA_PCOR |= uiPort4MaskDisable
            }
            else{ 
            	printf("Erro 3")
            }		
        break;

        case 4: 
        	if(ledSwi3 = true){
            	GPIOA_PCOR |= uiPort5MaskDisable
            }
            else{ 
            	printf("Erro 3")
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
        	if(ledSwi1 = true){
            	GPIOA_PTOR |= uiPort1MaskEnable
            } 
            else{ 
	        		printf("Erro 3")
	        	}
        break;

        case 2: 
            if(ledSwi2 = true){
            	GPIOA_PTOR |= uiPort2MaskEnable
            } 
            else{ 
	        		printf("Erro 3")
	        	}

        break;

        case 3: 
        	if(ledSwi3 = true){
            	GPIOA_PTOR |= uiPort4MaskEnable
            }
            else{ 
            	printf("Erro 3")
            }		
        break;

        case 4: 
        	if(ledSwi3 = true){
            	GPIOA_PTOR |= uiPort5MaskEnable
            }
            else{ 
            	printf("Erro 3")
            }	
        break;

    } 
}
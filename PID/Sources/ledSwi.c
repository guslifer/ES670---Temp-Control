/* **************************************************************************** */
/*                                                                              */
/*   Nome do arquivo:        ledSwi.c                                           */
/*                                                                              */
/*   Descrição:              Arquivo contendo as funcoes que lidam com          */
/*                           a atuacao do microcontrolador com os LEDs e        */
/*                           botoes do kit                                      */
/*                                                                              */
/*   Autores:                Gustavo Lino e Giácomo Dollevedo                   */
/*   Criado em:              31/03/2020                                         */
/*   Ultima revisão em:      27/07/2020                                         */
/* **************************************************************************** */


/*Adequações realizadas: Não deve ser considerada as variaveis tipo booleanas, para isso foram trocadas por tipo char  
outra adequação implementada foi o testar se os parametros passados estão dentro do padrão esperado*/


#include "ledSwi.h"
#include "board.h"


/* ******************************************************************************** */
/* Nome do metodo:          ledSwi_init                                             */
/* Descrição:               Inicializa os clocks e pinos necessarios para utilizar	*/
/*							a interface de botoes/leds do kit                       */
/*                                                                                  */
/* Parametros de entrada:   5 char (0 ou 1) que indica se o pino sera configurado  	*/
/*							como led ou como botao							        */
/*                          0 -> botao; 	1 -> led                   				*/
/*                                                                                  */
/* Parametros de saida:     n/a                                                 	*/
/* ******************************************************************************** */
char cLedSwi1 = 0, cLedSwi2 = 0, cLedSwi3 = 0, cLedSwi4 = 0;
unsigned char ucError = 0;

void ledSwi_init(char led1, char led2, char led3, char led4) { 



/* ativar o clock para a porta A*/ 
    SIM_SCGC5 |= uiSetClockPort; 

/*Configura os pinos das portas para GPIO*/

    PORTA_PCR1 |= uiSetPinAsGPIO; 
    PORTA_PCR2 |= uiSetPinAsGPIO; 
    PORTA_PCR4 |= uiSetPinAsGPIO; 
    PORTA_PCR5 |= uiSetPinAsGPIO; 

 	// testa se os parametros foram passado corretamente, se nao foram ativa todas as portas como led

	if((led1 != 0 && led1 != 1) && (led2 != 0 && led2 != 1) && (led3 != 0 && led3 != 1) && (led4 != 0 && led4 != 1)) {
		GPIOA_PDDR |= uiPin1MaskEnable;
        cLedSwi1 = 1;
        GPIOA_PDDR |= uiPin2MaskEnable;
        cLedSwi2 = 1;
        GPIOA_PDDR |= uiPin3MaskEnable;
        cLedSwi3 = 1;
        GPIOA_PDDR |= uiPin4MaskEnable;
        cLedSwi4 = 1;
	}

/*Define se os pinos serao entrada (chave) ou saida (led)*/ 

    if(led1 == 1){
        GPIOA_PDDR |= uiPin1MaskEnable;
        cLedSwi1 = 1;
    }
    else{ 
        GPIOA_PDDR &= uiPin1MaskDisable;
        cLedSwi1 = 0;
    } 

    if(led2 == 1){
        GPIOA_PDDR |= uiPin2MaskEnable;
        cLedSwi2 = 1;
    }
    else{ 
        GPIOA_PDDR &= uiPin2MaskDisable;
        cLedSwi2 = 0;
    } 

    if(led3== 1){
        GPIOA_PDDR |= uiPin4MaskEnable;
        cLedSwi3 = 1;
    }
    else{ 
        GPIOA_PDDR &= uiPin4MaskDisable;
        cLedSwi3 = 0;
    } 

    if(led4 == 1){
        GPIOA_PDDR |= uiPin5MaskEnable;
        cLedSwi4 = 1;
    }
    else{ 
        GPIOA_PDDR &= uiPin5MaskDisable;
        cLedSwi4 = 0;
    } 

}


/* ******************************************************************************** */
/* Nome do metodo:          readSwitch                                              */
/* Descrição:               Le o status de um switch para saber se o mesmo          */
/*                          está pressionado ou não                                 */
/*                                                                                  */
/* Parametros de entrada:   Um inteiro (0<n<5) que indica qual botão será lido      */
/*                          inicializado como entrada (botao) ou saida (LED)        */
/*                          0 -> Leitura PTA1; 1 -> Leitura PTA2,                   */
/*                          2 -> Leitura PTA4; 3 -> Leitura PTA5;                   */
/*                                                                                  */
/* Parametros de saida:     Um char indicando se o botao lido está sendo       		*/
/*                          pressionado (1), se não está ou se é inválido       	*/
/*                          (0)                                                 	*/
/* ******************************************************************************** */
char readSwitch(int n){ 
//testa se houve erro na passagem dos parametros
	if(n > 5){ 
		ucError = 1;
	}

	else{
		ucError = 0;
	}

// se não houver erro na entrada
	if(0 == ucError){


	    switch(n){
	        case 1: 
	            if(0 == cLedSwi1){
	                if (uiPin1MaskEnable == (GPIOA_PDIR & uiPin1MaskEnable)){
	                    return 1;
	                }
	                else {
	                    return 0;
	                }
	            }
	            else{
	                return 0;
	            }
	        break;

	        case 2:
	            if(0 == cLedSwi2){ 
	                if (uiPin2MaskEnable == (GPIOA_PDIR & uiPin2MaskEnable)){
	                    return 1;
	                }
	                else {
	                    return 0;
	                }
	            }
	            else{ 
	                return 0;
	            }
	        break;

	        case 3: 
	            if(0 == cLedSwi3){
	                if (uiPin4MaskEnable == (GPIOA_PDIR & uiPin4MaskEnable)){
	                    return 1;
	                }
	                else {
	                    return 0;
	                }
	            }
	            else{ 
	                return 0;
	            }
	        break;

	        case 4: 
	            if(0 == cLedSwi4){
	                if (uiPin5MaskEnable == (GPIOA_PDIR & uiPin5MaskEnable)){
	                    return 1;
	                }
	                else {
	                    return 0;
	                }
	            }
	        else{ 
	                return 0;
	            }
	        break;
	        }
	    }
		return 0;
    }



/* ******************************************************************************** */
/* Nome do metodo:          writeLED                                                */
/* Descrição:               Liga ou desliga o LED selecionado conforme as           */
/*                          entradas                                                */
/*                                                                                  */
/* Parametros de entrada:   Um inteiro (0<n<5) indicando sobre qual LED sera        */
/*                          efetuado o comando;                                     */
/*                          Um char (status) indicando se o LED sera            	*/
/*                          aceso (1) ou apagado (0)                        		*/
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void writeLED(int n, char status){

//testa se houve erro na passagem dos parametros

	if((status != 0 && status != 1) && (n < 5) ){ 
		ucError = 1;
	}

	else{
		ucError = 0;
	}

// se não houver erro na entrada
	if (0 == ucError){

	    switch(n){

	        case 1: 
	            if(1 == cLedSwi1){ 
	                if (status){ 
	                    GPIOA_PDOR |= uiPin1MaskEnable;
	                }
	                else {
	                    GPIOA_PDOR |= uiPin1MaskDisable;
	                }
	            }

	        break;

	        case 2: 
	            if(1 == cLedSwi2){
	                if (status){ 
	                    GPIOA_PDOR |= uiPin2MaskEnable;
	                }
	                else {
	                    GPIOA_PDOR |= uiPin2MaskDisable;
	                }
	            }

	        break;

	        case 3: 
	            if(1 == cLedSwi3){
	                if (status){ 
	                    GPIOA_PDOR |= uiPin4MaskEnable;
	                }
	                else {
	                    GPIOA_PDOR |= uiPin4MaskDisable;
	                }
	            }

	        break;

	        case 4: 
	            if(1 == cLedSwi4){
	                if (status){ 
	                    GPIOA_PDOR |= uiPin5MaskEnable;
	                }
	                else {
	                    GPIOA_PDOR |= uiPin5MaskDisable;
	                }
	            } 

	        break;
	    }
    }
}


/* ******************************************************************************** */
/* Nome do metodo:          turnOnLED                                               */
/* Descrição:               Liga um LED especificado pela entrada                   */
/*                                                                                  */
/* Parametros de entrada:   Um inteiro (0<n<5) indicando qual LED sera aceso        */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void turnOnLED(int n){ 
//testa se houve erro na passagem dos parametros
	if(n > 5){ 
		ucError = 1;
	}

	else{
		ucError = 0;
	}

// se não houver erro na entrada
	if(0 == ucError){
	    switch(n){

	        case 1:  
	            if(1 == cLedSwi1){
	                GPIOA_PSOR |= uiPin1MaskEnable;
	            } 
	        break;

	        case 2: 
	            if(1 == cLedSwi2){
	                GPIOA_PSOR |= uiPin2MaskEnable;
	            } 
	        break;

	        case 3: 
	            if(1 == cLedSwi3){
	                GPIOA_PSOR |= uiPin4MaskEnable;
	            }   
	        break;

	        case 4: 
	            if(1 == cLedSwi4){
	                GPIOA_PSOR |= uiPin5MaskEnable;
	            }
	        break;
	    }

    }
}



/* ******************************************************************************** */
/* Nome do metodo:          turnOffLED                                              */
/* Descrição:               Desliga um LED especificado pela entrada                */
/*                                                                                  */
/* Parametros de entrada:   Um inteiro (0<n<5) indicando qual LED sera apagado      */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void turnOffLED(int n){ 
//testa se houve erro na passagem dos parametros
	if(n > 5){ 
		ucError = 1;
	}

	else{
		ucError = 0;
	}

// se não houver erro na entrada
	if(0 == ucError){

	    switch(n){

	        case 1:  
	            if(1 == cLedSwi1){
	                GPIOA_PCOR |= uiPin1MaskDisable;
	            } 
	        break;

	        case 2: 
	            if(1 == cLedSwi2){
	                GPIOA_PCOR |= uiPin2MaskDisable;
	            } 
	        break;

	        case 3: 
	            if(1 == cLedSwi3){
	                GPIOA_PCOR |= uiPin4MaskDisable;
	            }       
	        break;

	        case 4: 
	            if(1 == cLedSwi4){
	                GPIOA_PCOR |= uiPin5MaskDisable;
	            }
	        break;
	    }

    }  
}



/* ******************************************************************************** */
/* Nome do metodo:          toggleLED                                               */
/* Descrição:               Inverte o status atual de um LED especificado pela      */
/*                          entrada                                                 */
/*                                                                                  */
/* Parametros de entrada:   Um inteiro (0<n<5) indicando qual LED tera seu          */
/*                          status invertido                                        */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void toggleLED(int n){
//testa se houve erro na passagem dos parametros
	if(n > 5){ 
		ucError = 1;
	}

	else{
		ucError = 0;
	}

// se não houver erro na entrada
	if(0 == ucError){

	    switch(n){

	        case 1:  
	            if(1 == cLedSwi1){
	                GPIOA_PTOR |= uiPin1MaskEnable;
	            } 
	        break;

	        case 2: 
	            if(1 == cLedSwi2){
	                GPIOA_PTOR |= uiPin2MaskEnable;
	            } 
	        break;

	        case 3: 
	            if(1 == cLedSwi3){
	                GPIOA_PTOR |= uiPin4MaskEnable;
	            }     
	        break;

	        case 4: 
	            if(1 == cLedSwi4){
	                GPIOA_PTOR |= uiPin5MaskEnable;
	            }
	        break;
	    }

    } 
}

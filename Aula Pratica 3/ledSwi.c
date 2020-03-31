/* #######################################
	Nome do arquivo: 		ledSwi.c 

	Descrição: 				As funções de atuação do 
							micro-controlador com os periféricos
							de chave e leds.

	Autores:				Gustavo Lino e Giácomo Dollevedo
	Criado em: 				29/03/2020 

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
		GPIOA_PDDR |= 0x02
	}
	else{ 
		GPIOA_PDDR &= 0x111D
	} 

	if(led2 == 1){
		GPIOA_PDDR |= 0x04
	}
	else{ 
		GPIOA_PDDR |= 0x111B
	} 

	if(led3== 1){
		GPIOA_PDDR |= 0x010
	}
	else{ 
		GPIOA_PDDR |= 0x11E1
	} 

	if(led4 == 1){
		GPIOA_PDDR |= 0x020
	}
	else{ 
		GPIOA_PDDR |= 0x11D1
	} 

}

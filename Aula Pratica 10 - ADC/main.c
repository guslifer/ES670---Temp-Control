/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        main.c                                                 */
/*                                                                                  */
/*   Descricao:             Arquivo main para teste das funcoes implementadas       */
/*                           para o microcontrolador utilizar o protocolo UART      */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo A. Dollevedo                	*/
/*   Criado em:              23/05/2020                                             */
/*   Ultima revisao em:   	 23/05/2020                                             */
/* ******************************************************************************** */

/* Incluindo bibliotecas */
#include "board.h"  
#include "UART.h"
#include "print_scan.h"
#include "communicationStateMachine.h"
#include "util.h"
#include "adc.h"
#include "lut_adc3v3.h" 
#include "tacometro.h"
#include "aquecedorECooler.h"
#include "lptmr.h"
#include "lcd.h"
#include "ledSwi.h"





/*  
 *  Rotina de interrupcao executada pelo timer LPTMR0
 *      - Retorna a rotacao (RPM) em uiRotacao
 *      - Flipa uma flag para escrever no LCD
*/
void main_cyclicExecuteIsr(void){

    uiRotacao = tachometer_readSensor(ui250ms);
    ucFlag = 1;

}

/* Instalando a rotina com um periodo de 250ms no timer */
void tc_installLptmr0(ui250ms, main_cyclicExecuteIsr);

/* **************************************************************************** */
/* Nome do metodo:          boardInit                                           */
/* Descricao:               Inicializa os parametros necessarios para o         */
/*                          teste                                               */
/*                                                                              */
/* Parametros de entrada:   n/a                                                 */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
void boardInit()
{

	ledSwi_init(false, false, false, true);
	PWM_init();
    coolerfan_init();
    tachometer_init();
    heater_init();
    lcd_initLcd();
    UART0_init();
    UART0_enableIRQ();
    voidadc_initADCModule();
 
}
// Função para leitura do sensor de temperatura, futuramente será chamada com um frequencia pré determinada.
// Só retorna após garantir que o a conversão foi finalizada
void readTempSensor(){

	voidadc_initConvertion(); 
	while(0 != charadc_isAdcDone())
	{
		util_genDelay250us();
	} 
	return dc_getConvertionValue(); 

}

/* **************************************************************************** */
/* Nome do metodo:          main                                                */
/* Descricao:               Testa GET e SET da maquina de estados 				*/
/*                                                                              */
/*                                                                              */
/* Parametros de entrada:   n/a                                                 */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
int main(void){

    boardInit();

    char *digitos = malloc( sizeof(char) * (4) );
    char cTempText[4];
    
    while(1){ 

    	util_genDelay250us();
	    //Coleta o valor inteiro retornado apos a conversao do sinal
		unsigned char uLutPos = readTempSensor();
		//Analisa na LUT qual a temperatura equivalente
		unsigned char ucActualTemp = tabela_temp[uLutPos];
		//limpa o que estiver no lcd 
		lcd_sendCommand(CMD_CLEAR);
		//Extrai os digitos a serem escritos no LCD
		extrai_digito(unsigned int numero, unsigned char* digitos);
		cTempText[0] = digitos[0];
		cTempText[1] = digitos[1];
		cTempText[2] = ".";
		cTempText[3] = "C";
		//imprime o valor lido de temperatura
		lcd_writeString(cTempText);


	}


}   

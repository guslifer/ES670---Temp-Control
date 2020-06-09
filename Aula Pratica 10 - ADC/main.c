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
#include "lut_adc_3v3.h"
#include "tacometro.h"
#include "aquecedorECooler.h"
#include "lptmr.h"
#include "lcd.h"
#include "ledSwi.h"

int iTemp_Atual = 0;
unsigned int uiTemp_convertida = 0;

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
    adc_initADCModule();
 
}
// Função para leitura do sensor de temperatura, futuramente será chamada com um frequencia pré determinada.
// Só retorna após garantir que o a conversão foi finalizada
void readTempSensor(){

	adc_initConvertion();
	while(0 != adc_isAdcDone())
	{
		util_genDelay250us();
	} 

	iTemp_Atual = adc_getConvertionValue();

	return;
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

    unsigned char digitos[5] = "0000";
    char cTempText[4] = "000";
    
    while(1){ 

    	util_genDelay250us();
	    readTempSensor();
	    uiTemp_convertida = tabela_temp[iTemp_Atual];
		//limpa o que estiver no lcd 
		lcd_sendCommand(CMD_CLEAR);
		//Extrai os digitos a serem escritos no LCD
		extrai_digito(uiTemp_convertida, digitos);
		cTempText[0] = digitos[0];
		cTempText[1] = digitos[1];
		cTempText[2] = '.';
		cTempText[3] = 'C';
		//imprime o valor lido de temperatura
		lcd_writeString(cTempText);


	}


}   

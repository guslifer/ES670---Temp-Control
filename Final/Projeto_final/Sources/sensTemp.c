/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:       sensTemp.c                                              */
/*                                                                                  */
/*   Descricao:             Funcoes para operar o sensor de temperatura, apenas     */
/*                          no contexto do projeto                                  */
/*                                                                                  */
/*   Autores:               Gustavo Lino e Giacomo A. Dollevedo                     */
/*   Criado em:             29/07/2020                                              */
/*   Ultima revisao em:     31/07/2020                                              */
/* ******************************************************************************** */

/* Incluindo bibliotecas */
#include "adc.h"
#include "variaveis_globais.h"
#include "lut_adc_3v3.h"
#include "util.h"

/* ******************************************************************************** */
/* Nome do metodo:          sensTemp_init                                           */ 
/* Descricao:               Inicializa as funcoes do ADC para sensor de temperatura */
/*                                                                                  */
/* Parametros de entrada:   n/a                                                     */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void sensTemp_init(void){

	adc_initADCModule();

}


/* **************************************************************************** */
/* Nome do metodo:          readTemp                                            */
/* Descricao:               Le o ADC conectado ao sensor de temperatura e       */
/*                          converte o valor pela lookup table em graus Celsius */
/*                                                                              */
/* Parametros de entrada:   n/a                                                 */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
void readTemp(void){ 

    int iRawTempAtual = 0;

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



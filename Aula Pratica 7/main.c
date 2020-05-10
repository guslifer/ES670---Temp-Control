/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        main.c                                                 */
/*                                                                                  */
/*   Descricao:             Arquivo main para teste das funcoes implementadas       */
/*                           para o microcontrolador utilizar um tacometro          */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo A. Dollevedo                	*/
/*   Criado em:              08/05/2020                                             */
/*   Ultima revisao em:   	 10/05/2020                                             */
/* ******************************************************************************** */

/* Incluindo bibliotecas */
#include "board.h"  
#include "tacometro.h"
#include "aquecedorECooler.h"
#include "lptmr.h"
#include "lcd.h"


unsigned int ui250ms    = 250000;
unsigned int uiRotacao  = 0;

unsigned char ucFlag = 0;

unsigned char digitos[4] = "0"; 


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
/* ADICIONAR A BIBLIOTECA DO LCD ASAP!                                          */
/* Nome do metodo:          extrai_digito                                       */
/* Descricao:               Extrai os digitos de um inteiro e os armazena em    */
/*                          um vetor de unsigned char                           */
/*                                                                              */
/* Parametros de entrada:   numero -> inteiro o qual os digitos serao extraidos */                                               
/*                          digitos -> array para armazenar digitos             */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
void extrai_digito(unsigned int numero, unsigned char* digitos){
    
    unsigned char i = 0;
    unsigned int x = 1;
    unsigned int sobra = 0;
    
    /*Ja inicializa cada digito com "0" (tabela ASCII)*/
    digitos[0] = 48;
    digitos[1] = 48;
    digitos[2] = 48;
    digitos[3] = 48;

    /*Checar quantos digitos tem no numero*/
    while(numero > x){
        x *= 10;
        i++;
    }
    
    x /= 10;
    
    /*Divide por uma potencia de 10 para sobrar um digito so*/
    /*Extrai o digito e armazena no vetor +48 (ASCII)       */
    while(i > 0){
        sobra = numero/x;
        digitos[4-i] = (sobra + 48);
        
        numero -= (sobra*x);
        x /= 10;
        
        
        
        i--;
        
    }

    return;
    
}

/* **************************************************************************** */
/* Nome do metodo:          boardInit                                           */
/* Descricao:               Inicializa os parametros necessarios para o         */
/*                          teste                                               */
/*                                                                              */
/* Parametros de entrada:   n/a                                                 */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
void boardInit(void)
{
    boardInit();
    /* executando rotina de inicializacao:   
        * Placa do microcontrolador 
        * Configuração da modulação PWM 
        * Inicialização do cooler 
        * Inicialização do tacometro 
        * Inicialização do lcd
    */
    PWM_init();
    coolerfan_init();
    tachometer_init();
    lcd_initLcd();
}



/* **************************************************************************** */
/* Nome do metodo:          main                                                */
/* Descricao:               Inicializa o aquecedor e o cooler com 50% da tensão */
/*                                                                              */
/*                                                                              */
/* Parametros de entrada:   n/a                                                 */
/*                                                                              */
/* Parametros de saida:     n/a                                                 */
/* **************************************************************************** */
int main(void){

    boardInit();

    while(1){

        /*Sempre que ocorrer uma interrupcao, a condicao eh cumprida*/
        if(1 == ucFlag){ 

            /* Armazena os dois bytes em um array e escreve no LCD (em formato hexadecimal)
            *  o valor da velocidade RPM */
            extrai_digito(uiRotacao, digitos);
            ucFlag = 0;
            lcd_writeString(digitos);
        }

    }


}   

/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        display7seg.c                                          */
/*                                                                                  */
/*   Descricao:              Arquivo contendo a implementacao                       */
/*                           das funcoes de interface do microcontrolador           */
/*                           com o display de 7 segmentos do kit                    */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giacomo Dollevedo                       */
/*   Criado em:              13/04/2020                                             */
/*   Ultima revisao em:      13/04/2020                                             */
/* ******************************************************************************** */

#include "board.h"
#include "display7seg.h"
         

/* ******************************************************************************** */
/* Nome do metodo:          display7Seg_init                                        */ 
/* Descricao:               Inicializa os registradores para funcionamento do D7S   */
/*                                                                                  */
/* Parametros de entrada:    n/a                                                    */
/*                                                                                  */
/* Parametros de saida:      n/a                                                    */
/* ******************************************************************************** */
void display7seg_init(void){


    /* Liberando o Clock para porta C*/
    SIM_SCGC5 |= uiSetClockPortC;

    /* Declarando os pinos como GPIO */
    PORTC_PCR0 |= uiSetPinAsGPIO;   //Segmento A
    PORTC_PCR1 |= uiSetPinAsGPIO;   //Segmento B
    PORTC_PCR2 |= uiSetPinAsGPIO;   //Segmento C
    PORTC_PCR3 |= uiSetPinAsGPIO;   //Segmento D
    PORTC_PCR4 |= uiSetPinAsGPIO;   //Segmento E
    PORTC_PCR5 |= uiSetPinAsGPIO;   //Segmento F
    PORTC_PCR6 |= uiSetPinAsGPIO;   //Segmento G
    PORTC_PCR7 |= uiSetPinAsGPIO;   //Segmento DP

    PORTC_PCR13 |= uiSetPinAsGPIO;  //Display 1
    PORTC_PCR11 |= uiSetPinAsGPIO;  //Display 2
    PORTC_PCR12 |= uiSetPinAsGPIO;  //Display 3
    PORTC_PCR10 |= uiSetPinAsGPIO;  //Display 4

    /* Declarando os pinos como Saida*/
    GPIOC_PDDR |= D7S_GPIO_CONFIG;


}


/* ******************************************************************************** */
/* Nome do metodo:          display7seg_writeSymbol                                 */ 
/* Descricao:               Escreve um caracter em um D7S                           */
/*                                                                                  */
/* Parametros de entrada:   ucDisplay -> indica o D7S no qual sera escrito (1 a 4)  */
/*                          ucValue -> valor indicando o caracter que sera escrito  */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void display7seg_writeSymbol(unsigned char ucDisplay,  unsigned char ucValue){

    selectDisp(ucDisplay);

    /*CLEAR no display*/
    /* A mascara mantem o estado dos outros pinos */

    GPIOC_PDOR &= DISP_CLEAR;

    if(ucValue < 20){
        switch(ucValue%10){
            case 0:
                GPIOC_PDOR |= DISP_0;
                break;

            case 1:
                GPIOC_PDOR |= DISP_1;
                break;

            case 2:
                GPIOC_PDOR |= DISP_2;
                break;

            case 3:
                GPIOC_PDOR |= DISP_3;
                break;

            case 4:
                GPIOC_PDOR |= DISP_4;
                break;

            case 5:
                GPIOC_PDOR |= DISP_5;
                break;

            case 6:
                GPIOC_PDOR |= DISP_6;
                break;

            case 7:
                GPIOC_PDOR |= DISP_7;
                break;

            case 8:
                GPIOC_PDOR |= DISP_8;
                break;

            case 9:
                GPIOC_PDOR |= DISP_9;
                break;
        }

    }

    /* Acendendo o ponto decimal */
    if(ucValue >= 10 && ucValue <= 20){
        GPIOC_PDOR |= DISP_DP;

    }

    /* Caso CLEAR do display */
    else if(ucValue == 21){
        GPIOC_PDOR &= DISP_CLEAR;
    }

    /* Caso acenda todos os segmentos do display */
    else if(ucValue == 22){
        GPIOC_PDOR |= DISP_ALL;
    }
}

/* ******************************************************************************** */
/* Nome do metodo:          selectDisp                                              */ 
/* Descricao:               Seleciona o D7S que sera escrito                        */
/*                                                                                  */
/* Parametros de entrada:   ucDisplay -> indica o D7S no qual sera escrito (1 a 4)  */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void selectDisp(unsigned char ucDisplay){

    /* CLEAR, zerando pinos de 10 a 13 (1111 1111 1111 1111 1111 0000 1111 1111) */
    /* A mascara mantem o estado dos outros pinos */
    GPIOC_PDOR &= 0xFFFFF0FF;

    switch(ucDisplay){
        /* Display 1, pino 13*/
        case 1:
            GPIOC_PDOR |= 0x000C;
            break;

        /* Display 2, pino 11*/
        case 2:
            GPIOC_PDOR |= 0x000A;
            break;

        /* Display 3, pino 12*/
        case 3:
            GPIOC_PDOR |= 0x000B;

            break;

        /* Display 4, pino 10*/
        case 4:
            GPIOC_PDOR |= 0x0009;
            break;

        default:
            break;
    }

}

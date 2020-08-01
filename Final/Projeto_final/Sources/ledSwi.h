/* ******************************************************************************** */
/*                                                                                  */
/*   Nome do arquivo:        ledSwi.h                                               */
/*                                                                                  */
/*   Descrição:              Arquivo Header contendo a declaração                   */
/*                           das funções de atuação do microcontrolador             */
/*                           sobre os LEDs e chaves do kit                          */
/*                                                                                  */
/*   Autores:                Gustavo Lino e Giácomo Dollevedo                       */
/*   Criado em:              29/03/2020                                             */
/*   Ultima revisão em:      03/04/2020                                             */
/* ******************************************************************************** */
#ifndef SOURCES_LEDSWI_

#define SOURCES_LEDSWI_

/* ******************************************************************************** */
/* Nome do metodo:          ledSwi_init                                             */ 
/* Descrição:               Inicializa os GPIO como entrada (botao) ou saida        */
/*                          (LED)                                                   */
/*                                                                                  */
/* Parametros de entrada:   Quatro variaveis chareanas que indicam se sera          */
/*                          inicializado como entrada (false) ou saida (true)       */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void ledSwi_init(char led1, char led2, char led3, char led4);




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
/* Parametros de saida:     Um chareano indicando se o botao lido está sendo        */
/*                          pressionado (true), se não está ou se é inválido        */
/*                          (false)                                                 */
/* ******************************************************************************** */
char readSwitch(int n);



/* ******************************************************************************** */
/* Nome do metodo:          writeLED                                                */
/* Descrição:               Liga ou desliga o LED selecionado conforme as           */
/*                          entradas                                                */
/*                                                                                  */
/* Parametros de entrada:   Um inteiro (0<n<5) indicando sobre qual LED sera        */
/*                          efetuado o comando;                                     */
/*                          Um chareano (status) indicando se o LED sera            */
/*                          aceso (true) ou apagado (false)                         */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void writeLED(int n, char status);



/* ******************************************************************************** */
/* Nome do metodo:          turnOnLED                                               */
/* Descrição:               Liga um LED especificado pela entrada                   */
/*                                                                                  */
/* Parametros de entrada:   Um inteiro (0<n<5) indicando qual LED sera aceso        */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void turnOnLED(int n);




/* ******************************************************************************** */
/* Nome do metodo:          turnOffLED                                              */
/* Descrição:               Desliga um LED especificado pela entrada                */
/*                                                                                  */
/* Parametros de entrada:   Um inteiro (0<n<5) indicando qual LED sera apagado      */
/*                                                                                  */
/* Parametros de saida:     n/a                                                     */
/* ******************************************************************************** */
void turnOffLED(int n);



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
void toggleLED(int n);



#endif

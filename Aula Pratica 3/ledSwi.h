/* **********************************************************************/
/*
/*   Nome do arquivo:        ledSwi.h
/*
/*   Descrição:              Arquivo Header contendo a declaração
/*                           das funções de atuação do microcontrolador
/*                           sobre os LEDs e chaves do kit
/*
/*   Autores:                Gustavo Lino e Giácomo Dollevedo
/*   Criado em:              29/03/2020 
/*   Ultima revisão em:      31/03/2020
/* **********************************************************************/
#ifndef ledSwi.h
#define ledSwi.h


/* **************************************************************************/
/* Nome do metodo:          ledSwi_init                  
/* Descrição:               Inicializa os GPIO como entrada (botao) ou saida
/*                          (LED)
/*
/* Parametros de entrada:   Quatro variaveis booleanas que indicam se sera
/*                          inicializado como entrada (false) ou saida (true)
/*
/* Parametros de saida:     n/a                          
/* **************************************************************************/
void ledSwi_init(bool led1, bool led2, bool led3, bool led4);



/* **************************************************************************/
/* Nome do metodo:          readSwitch                  
/* Descrição:               Le o status de um switch para saber se o mesmo
/*                          está pressionado ou não
/*
/* Parametros de entrada:   Um inteiro (0<n<5) que indica qual botão será lido
/*                          inicializado como entrada (botao) ou saida (LED)
/*
/* Parametros de saida:     Um booleano indicando se o botao lido está sendo
/*                          pressionado (true), se não está ou se é inválido
/*                          (false)                          
/* **************************************************************************/
bool readSwitch(int n);



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
void writeLED(int n, bool status);



/* **************************************************************************/
/* Nome do metodo:          turnOnLED                  
/* Descrição:               Liga um LED especificado pela entrada
/*
/* Parametros de entrada:   Um inteiro (0<n<5) indicando qual LED sera aceso
/*
/* Parametros de saida:     n/a                          
/* **************************************************************************/
void turnOnLED(int n);



/* **************************************************************************/
/* Nome do metodo:          turnOffLED                  
/* Descrição:               Desliga um LED especificado pela entrada
/*
/* Parametros de entrada:   Um inteiro (0<n<5) indicando qual LED sera apagado
/*
/* Parametros de saida:     n/a                          
/* **************************************************************************/
void turnOffLED(int n);



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
void toggleLED(int n);



#endif /* ledSwi.h */
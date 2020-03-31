/* **********************************************************************/
/*
/*   Nome do arquivo:        main.c
/*
/*   Descrição:              Arquivo de teste das funcoes criadas para
/*                           lidar com entradas e saidas atraves dos
/*                           LEDs e botoes do kit presente no laboratorio
/*
/*   Autores:                Gustavo Lino e Giácomo Dollevedo
/*   Criado em:              31/03/2020 
/*   Ultima revisão em:      31/03/2020
/* **********************************************************************/


/* bibliotecas incluidas */
#include "board.h"
#include "ledSwi.h"


/* variaveis globais */
static bool bConfig[4] = {false, false, false, true};


/* **************************************************************************/
/* Nome do metodo:          boardInit                  
/* Descrição:               Inicializa os parametros necessarios para o
/*							teste
/*
/* Parametros de entrada:   Quatro booleanos, entradas da inicializacao dos
/*							LEDs e botoes
/*
/* Parametros de saida:     n/a                          
/* **************************************************************************/
void boardInit(bool led1, bool led2, bool led3, bool led4)
{

	ledSwi_init(led1, led2, led3, led4);

}



/* **************************************************************************/
/* Nome do metodo:          main                  
/* Descrição:               Executa um teste de cada funcao implementada em
/*							ledSwi combinando as entradas de botoes e LEDs
/*
/* Parametros de entrada:   n/a
/*
/* Parametros de saida:     n/a                          
/* **************************************************************************/
int main(void)
{
	/* inicialização dos registradores */
	boardInit(bConfig[0], bConfig[1], bConfig[2], bConfig[3]);


	/*	Acende o LED 4 do kit. Em seguida, aguarda a entrada de cada um
	/*	dos botoes (em sequencia, do primeiro ao terceiro), alternando
	/*	o estado do LED, ligando e desligando o LED*/

	while(1){

		writeLED(4, true);

		if(readSwitch(1) == true){
	    
			toggleLED(4);

	    }

	  
	    if(readSwitch(2) == true){

	    	turnOnLED(4);

	    }

	    if (readSwitch(3) == true){
	    
	    	turnOffLED(4);

	    }
	}
}
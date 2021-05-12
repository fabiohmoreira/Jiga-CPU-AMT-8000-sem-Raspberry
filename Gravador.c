/****************************************************************/
/* Intelbras S/A												*/
/* Nome do arquivo - Gravador.c 								*/
/* Jiga Universal -	Placa Principal								*/
/* Fun��o: Fun��es para controle da placa Gravador  			*/
/* Autor: Jo�o Antonio dos Santos Filho							*/
/* Data de Cria��o - 01/12/2010									*/
/****************************************************************/
#include "define.h"
#include "global_vars.h"

/************************************************************************/
/*	void SetProcessador(char Placa, char Processador)					*/
/*	Fun��o: Seta o tipo do processador a ser gravado					*/
/*	Par�metros:															*/
/*		Placa: A placa Gravador que receber� a mensagem.	  			*/
/*			Obs. Utilizar os valores pre-definidos						*/
/*		Processador : O tipo do processador a ser gravado 				*/
/*			Obs. Utilizar os valores pre-definidos						*/
/*	Retorno:															*/
/*	nenhum																*/
/************************************************************************/
void SetProcessador(char Placa, char Processador)
{
	bus_tx_buffer[0]=Processador;	
	bus_tx_buffer[1]=0x00;
	BusSendMessage(Placa,SetMicro,1);
}
/************************************************************************/
/*	int InitProg(char Placa, char prog)									*/
/*	Fun��o: Inicia a programa��o do processador								*/
/*	Par�metros:															*/
/*		Placa: A placa gravodora que ser� utilizada			.  			*/
/*			Obs. Utilizar os valores pre-definidos						*/
/*		Prog: O programa que ser� gravado. (1, 2 ou 3)				 	*/
/*	Retorno:															*/
/*	nenhum																*/
/************************************************************************/
void InitProg(char Placa, unsigned char Prog)
{
	bus_tx_buffer[0]=Prog;
	bus_tx_buffer[1]=0x00;
	BusSendMessage(Placa,StartGr,1);
}
/************************************************************************/
/*	char GrReadStatus(char Placa)										*/
/*	Fun��o: Le o status do gravador										*/
/*	Par�metro:															*/
/*		Placa:  A placa gravodora que ser� lida.			  			*/
/*			Obs. Utilizar os valores pre-definidos						*/
/*	Retorno: Seta a variavel global StatusGr com o status				*/
/*			0x00 = Idle													*/
/*			0x01 = Apagando												*/
/*			0x02 = Grava��o em andamento								*/
/*			0x03 = Verificando grava��o									*/
/*			0x04 = Grava��o OK											*/
/*			0xf1 = Erro no apagamento									*/
/*			0xf3 = Erro na grava��o da memoria de programa				*/
/*			0xf4 = Erro na grava��o da configura��o						*/
/*			0xf5 = N�o foi setado o processador							*/
/*			0xf6 = Falha na tens�o de alimenta��o (VDD)					*/
/*			0xf7 = Falha na tens�o de grava��o (VPP)					*/
/*			0xff = ERRO n�o especificado								*/
/************************************************************************/
void GrReadStatus(char Placa)
{
	BusSendMessage(Placa,GrStatus,1);
	if(BUS_ACK)
		StatusGr[Placa-PlacaGravador_0]=bus_rx_buffer[0];
	else
		StatusGr[Placa-PlacaGravador_0]=0xff;
}
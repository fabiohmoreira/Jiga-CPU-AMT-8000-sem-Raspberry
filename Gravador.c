/****************************************************************/
/* Intelbras S/A												*/
/* Nome do arquivo - Gravador.c 								*/
/* Jiga Universal -	Placa Principal								*/
/* Função: Funções para controle da placa Gravador  			*/
/* Autor: João Antonio dos Santos Filho							*/
/* Data de Criação - 01/12/2010									*/
/****************************************************************/
#include "define.h"
#include "global_vars.h"

/************************************************************************/
/*	void SetProcessador(char Placa, char Processador)					*/
/*	Função: Seta o tipo do processador a ser gravado					*/
/*	Parâmetros:															*/
/*		Placa: A placa Gravador que receberá a mensagem.	  			*/
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
/*	Função: Inicia a programação do processador								*/
/*	Parâmetros:															*/
/*		Placa: A placa gravodora que será utilizada			.  			*/
/*			Obs. Utilizar os valores pre-definidos						*/
/*		Prog: O programa que será gravado. (1, 2 ou 3)				 	*/
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
/*	Função: Le o status do gravador										*/
/*	Parâmetro:															*/
/*		Placa:  A placa gravodora que será lida.			  			*/
/*			Obs. Utilizar os valores pre-definidos						*/
/*	Retorno: Seta a variavel global StatusGr com o status				*/
/*			0x00 = Idle													*/
/*			0x01 = Apagando												*/
/*			0x02 = Gravação em andamento								*/
/*			0x03 = Verificando gravação									*/
/*			0x04 = Gravação OK											*/
/*			0xf1 = Erro no apagamento									*/
/*			0xf3 = Erro na gravação da memoria de programa				*/
/*			0xf4 = Erro na gravação da configuração						*/
/*			0xf5 = Não foi setado o processador							*/
/*			0xf6 = Falha na tensão de alimentação (VDD)					*/
/*			0xf7 = Falha na tensão de gravação (VPP)					*/
/*			0xff = ERRO não especificado								*/
/************************************************************************/
void GrReadStatus(char Placa)
{
	BusSendMessage(Placa,GrStatus,1);
	if(BUS_ACK)
		StatusGr[Placa-PlacaGravador_0]=bus_rx_buffer[0];
	else
		StatusGr[Placa-PlacaGravador_0]=0xff;
}
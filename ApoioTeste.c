/********************************************************************/
/* Nome do arquivo: ApoioTeste.c									*/
/* 																	*/
/* Versão:	1.0.0 													*/
/*            Intelbras S/A.										*/
/*                                                           		*/
/* Autor:	Augusto Cezar Medeiros dos Santos						*/
/*                                                                  */
/* Função:Rotinas de apoio para execução do teste					*/
/*          		                                             	*/
/********************************************************************/
#include "define.h"
#include "global_vars.h"

static char OnOffRelayBoard;
static char OnOffRelayChannel;
static int OnOffRelayTime;
static int ExecuteOnOffRelayStage;

void SetOnOffRelay_ms(char Board, char Channel, int Time)
{
	OnOffRelayBoard=Board;
	OnOffRelayChannel=Channel;
	OnOffRelayTime=Time;
	ExecuteOnOffRelayStage=0;
	OnOffRelay_msDelay=0;
	OnOffRelayFlag=1;
}

void ExecuteOnOffRelay_ms(void)
{
	if((OnOffRelayFlag)&&(OnOffRelay_msDelay==0))
	{
		switch(ExecuteOnOffRelayStage)
		{
			case 0:
				AlteraEstadoReles(OnOffRelayBoard,OnOffRelayChannel, OnOffRelayChannel);		// Liga o relê selecionado
				OnOffRelay_msDelay=OnOffRelayTime;
				ExecuteOnOffRelayStage++;
			break;
			case 1:
				AlteraEstadoReles(OnOffRelayBoard,OnOffRelayChannel, 0);		// desliga o relê selecionado
				OnOffRelayFlag=0;
				ExecuteOnOffRelayStage=0;
			break;
		}
	}
	
}

static char OffOnRelayBoard;
static char OffOnRelayChannel;
static int OffOnRelayTime;
static int ExecuteOffOnRelayStage;

void SetOffOnRelay_ms(char Board, char Channel, int Time)
{
	OffOnRelayBoard=Board;
	OffOnRelayChannel=Channel;
	OffOnRelayTime=Time;
	OffOnRelay_msDelay=0;
	OffOnRelayFlag=1;
}

void ExecuteOffOnRelay_ms(void)
{
	if((OffOnRelayFlag)&&(OffOnRelay_msDelay==0))
	{
		switch(ExecuteOffOnRelayStage)
		{
			case 0:
				AlteraEstadoReles(OffOnRelayBoard,OffOnRelayChannel, 0);		// Desliga o relê selecionado
				OffOnRelay_msDelay=OffOnRelayTime;
				ExecuteOffOnRelayStage++;
			break;
			case 1:
				AlteraEstadoReles(OffOnRelayBoard,OffOnRelayChannel, OffOnRelayChannel);		// Liga o relê selecionado
				OffOnRelayFlag=0;
				ExecuteOffOnRelayStage=0;
			break;
		}
	}
	
}


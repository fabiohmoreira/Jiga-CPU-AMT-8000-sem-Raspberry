/****************************************************************/
/* Intelbras S/A												*/
/* Nome do arquivo - Reles.c									*/
/* Jiga Universal -	Placa Principal								*/
/* Função: Funções para controle da placa de Reles				*/
/* Autor: Augusto Cezar Medeiros dos Santos						*/
/* Data de Criação - 01/06/2010									*/
/****************************************************************/
#include "define.h"
#include "global_vars.h"

/********************************************************************/
/*	void AlteraEstadoReles(char Placa,char Reles, char Estado)		*/
/*	Função: Envia mensagem para alterar o estado dos Reles 			*/
/*	selecionados													*/
/*	Parâmetros:														*/
/*		Placa: A placa de Reles que receberá a mensagem.  			*/
/*			Obs. Utilizar os valores pre-definidos					*/
/*		Reles: cada bit representa um dos 8 reles da placa 			*/
/*			1= Estado do rele vai ser alterado						*/
/*			0= Estado do rele permanece o mesmo						*/
/*		Estado: cada bit representa um dos 8 reles da placa 		*/
/*			1= O rele será ligado									*/
/*			0= O rele será desligado								*/
/*	Retorno:														*/
/*	nenhum															*/
/********************************************************************/
void AlteraEstadoReles(char Placa,char Reles, char Estado)
{
	bus_tx_buffer[0]=Reles;						// relação dos reles que terão o estado alterado
	bus_tx_buffer[1]=Estado;					// estado dos reles selecionados
	BusSendMessage(Placa,R_ChangeRelaysState,2);	// envia a mensagem para a placa de rele
}
/********************************************************************/
/*	void DesligaReles(char Placa)									*/
/*	Função: Desliga todos os reles da placa selecionada 			*/
/*	Parâmetros:														*/
/*		Placa: A placa de Reles que receberá a mensagem.  			*/
/*			Obs. Utilizar os valores pre-definidos					*/
/*	Retorno:														*/
/*	nenhum															*/
/********************************************************************/
void DesligaReles(char Placa)
{
	BusSendMessage(Placa,R_TurnAllRelaysOff,0);	// envia a mensagem para a placa de rele
}
/********************************************************************/
/*	void TestaReles(char Placa)										*/
/*	Função: Desliga todos os reles da placa selecionada 			*/
/*	Parâmetros:														*/
/*		Placa: A placa de Reles que será testada.  					*/
/*			Obs. Utilizar os valores pre-definidos					*/
/*	Retorno:														*/
/*	nenhum															*/
/********************************************************************/
/*void TestaReles(char Placa)
{
	static int TestState;
	if(DelayTesteReles>0)
		DelayTesteReles--;

	if((IniciaTesteReles)&&(!ErroTesteReles))
	{
		switch(TestState)
		{
			case 0:
				BusSendMessage(Placa,R_RelayAutoTest,0);			// envia a mensagem para a placa de rele
				if(BUS_ACK)
				{
					DelayTesteReles=20000;
					TestState++;
				}
				else
				{
					TestState=0;
					ErroTesteReles=1;
				}
			break;
			case 1:
				if(DelayTesteReles==0)
				{
					BusSendMessage(Placa,R_RelayAutoTestAnswer,0);	// envia a mensagem para a placa de rele
					if(BUS_ACK)
					{
					}
					else
						ErroTesteReles=1;
					TestState=0;
				}
			break;
			
		}
//		if(ErroTesteReles)
			
	}
}*/

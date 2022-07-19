/****************************************************************/
/* Intelbras S/A												*/
/* Nome do arquivo - ConversorAD.c								*/
/* Jiga Universal -	Placa Principal								*/
/* Função: Funções para controle da placa Conversor A/D			*/
/* Autor: Augusto Cezar Medeiros dos Santos						*/
/* Data de Criação - 14/06/2010									*/
/****************************************************************/
#include "define.h"
#include "global_vars.h"

unsigned int LarguraPulsoAlto,LarguraPulsoBaixo;
unsigned int LarguraPulsoAltoInst,LarguraPulsoBaixoInst;


/************************************************************************/
/*	void SetAverageVoltage(char Placa, char Channel,int Value)			*/
/*	Função: Seta o valor médio de tensão para a medição de período		*/
/*	no canal selecionado												*/
/*	Parâmetros:															*/
/*		Placa: A placa Comversor A/D que receberá a mensagem.  			*/
/*			Obs. Utilizar os valores pre-definidos						*/
/*		Channel: o canal que vai ler o período						 	*/
/*		Value: o valor médio que será setado para o canal selecionado 	*/
/*			este valor de ser dado no formato do valor lido pelo 		*/
/*			conversor A/D de 0 a 1024									*/
/*	Retorno:															*/
/*	nenhum																*/
/************************************************************************/
void SetAverageVoltage(char Placa, char Channel,int Value)
{
	bus_tx_buffer[0]=Channel;		// mensagem
	bus_tx_buffer[1]=Value>>8;
	bus_tx_buffer[2]=Value&0x0F;
	BusSendMessage(Placa,A_AverageVoltage,3);
}
/************************************************************************/
/*	void ADChannelEnabled(char Placa, char ChannelEnabled)				*/
/*	Função: Define quais canais de AD estão habilitados na placa		*/
/*	selecionada															*/
/*	Parâmetros:															*/
/*		Placa: A placa Comversor A/D que receberá a mensagem.  			*/
/*			Obs. Utilizar os valores pre-definidos						*/
/*		ChannelEnabled: Canais habilitados. 							*/
/*			Bits em 1 = ativado											*/
/*			Bits em 0 = desativado										*/
/*	Retorno:															*/
/*	nenhum																*/
/************************************************************************/
/*void ADChannelEnabled(char Placa, char ChannelEnabled)
{
	bus_tx_buffer[0]=ChannelEnabled;
	BusSendMessage(Placa,A_ChannelEnabled,1);
}*/
/************************************************************************/
/*	int ADReadVoltage(char Placa, char Channel)							*/
/*	Função: Define quais canais de AD estão habilitados					*/
/*	no canal selecionado												*/
/*	Parâmetros:															*/
/*		Placa: A placa Comversor A/D que receberá a mensagem.  			*/
/*			Obs. Utilizar os valores pre-definidos						*/
/*		Channel: o canal que vai ser lido							 	*/
/*	Retorno:															*/
/*		Valor lido pelo canal selecionado. Se valor = 0xFFFF = ERRO		*/
/************************************************************************/
int ADReadVoltage(char Placa, char Channel)
{
    unsigned int media ,valortotal = 0;
    int i = 0;
   
    for(i = 0; i < 10; i++){
    
        bus_tx_buffer[0]=Channel;
        BusSendMessage(Placa,A_ReadVoltage,1);
        if((BUS_ACK)&&(rx_count==2))
        {
            valortotal += ((bus_rx_buffer[0]<<8)|bus_rx_buffer[1]);
        }
        else
        {
            valortotal += (0xFFFF);
        }
    }
    
    media = valortotal/10;
    
    return media;
}
/************************************************************************/
/*	int ADReadPeriod(char Placa, char Channel)							*/
/*	Função: Define quais canais de AD estão habilitados					*/
/*	no canal selecionado												*/
/*	Parâmetros:															*/
/*		Placa: A placa Comversor A/D que receberá a mensagem.  			*/
/*			Obs. Utilizar os valores pre-definidos						*/
/*		Channel: o canal que vai ser lido							 	*/
/*	Retorno:															*/
/*		Periodo lido pelo canal selecionado. Se valor = 0xFFFF = ERRO	*/
/*			Periodo = Valor_recebido * 200us							*/
/************************************************************************/
void ADReadPeriod(char Placa, char Channel)
{
	bus_tx_buffer[0]=Channel;
	BusSendMessage(Placa,A_ReadPeriod,1);
	if((BUS_ACK)&&(rx_count==4))
	{
		LarguraPulsoAlto=(bus_rx_buffer[0]<<8)|bus_rx_buffer[1];
		LarguraPulsoBaixo=(bus_rx_buffer[2]<<8)|bus_rx_buffer[3];
	}
	else
	{
		LarguraPulsoAlto=0xFFFF;
		LarguraPulsoBaixo=0xFFFF;
	}
}
/************************************************************************/
/*	int ADReadPeriod(char Placa, char Channel)							*/
/*	Função: Define quais canais de AD estão habilitados					*/
/*	no canal selecionado												*/
/*	Parâmetros:															*/
/*		Placa: A placa Comversor A/D que receberá a mensagem.  			*/
/*			Obs. Utilizar os valores pre-definidos						*/
/*		Channel: o canal que vai ser lido							 	*/
/*	Retorno:															*/
/*		Periodo lido pelo canal selecionado. Se valor = 0xFFFF = ERRO	*/
/*			Periodo = Valor_recebido * 200us							*/
/************************************************************************/
void ADReadInstantPeriod(char Placa, char Channel)
{
	bus_tx_buffer[0]=Channel;
	BusSendMessage(Placa,A_ReadInstantPeriod,1);
	if((BUS_ACK)&&(rx_count==4))
	{
		LarguraPulsoAltoInst=(bus_rx_buffer[0]<<8)|bus_rx_buffer[1];
		LarguraPulsoBaixoInst=(bus_rx_buffer[2]<<8)|bus_rx_buffer[3];
	}
	else
	{
		LarguraPulsoAltoInst=0xFFFF;
		LarguraPulsoBaixoInst=0xFFFF;
	}
}


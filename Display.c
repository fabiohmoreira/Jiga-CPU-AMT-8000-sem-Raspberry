#include "p24fj48ga004.h"
#include "define.h"
#include "global_vars.h"
#include "Mensagens.h"
#include "MensagensFixas.h"

/************************************************************************************/
/*	void LimpaDisplay(void)															*/
/*	Função: Limpa todo o display													*/
/*	Parâmetros:																		*/
/*		nenhum																		*/
/*	Retorno:																		*/
/*		nenhum																		*/
/************************************************************************************/
void LimpaDisplay(void)
{
	BusSendMessage(PlacaDisplay,D_CleanDisplay,0);	// envia a mensagem para a placa display
}	
/************************************************************************************/
/*	void SendTextMessage(char MessageIndex)											*/
/*	Função: Envia a mensagem selecionada para exibição no display					*/
/*	Parâmetros:																		*/
/*		Linha - linha do display onde a mensagem será exibida (1 a 4)				*/
/*		Coluna - coluna do display onde a mensagem será exibida	(0 a 24)			*/
/*		Tipo - tipo de mensagem														*/
/*		MessageIndex - número da mensagem											*/
/*	Retorno:																		*/
/*	nenhum																			*/
/************************************************************************************/
void SendTextMessage(unsigned char Linha,unsigned char Coluna,unsigned char MessageIndex)
{
	int Count;
	
	bus_tx_buffer[0]=Linha;
	bus_tx_buffer[1]=Coluna;
	
	if(MessageIndex<100)
	{
		for(Count=0;Count<24;Count++)
			bus_tx_buffer[Count+2]=MensagensGerais[MessageIndex][Count];
	}
	else
	{
		MessageIndex-=100;
		for(Count=0;Count<24;Count++)
			bus_tx_buffer[Count+2]=MensagensFixas[MessageIndex][Count];
	}
		
	BusSendMessage(PlacaDisplay,D_ShowMessage,26);
	
}
/************************************************************************************/
/*	void EmiteBipe(char bip,char qtd_bip)											*/
/*	Função: Emite o bipe correspondente pelo número de vezes selecionado			*/
/*	Parâmetros:																		*/
/*		bip - tipo de bipe															*/
/*			0x01 = Acionar o BIP de OK												*/
/*			0x02 = Acionar o BIP de ERRO											*/
/*			0x03 = Acionar o BIP a cada segundo										*/
/*			0x04 = Desabilitar o BIP de segundos									*/
/*			0x05 = Acionar 'n' BIPs curto (inicio de teste/final de teste ???)		*/
/*		qtd_bip - quantidade de bipes que serão emitidos							*/
/*	Retorno:																		*/
/*	nenhum																			*/
/************************************************************************************/
void EmiteBipe(char bip,char qtd_bip)
{
	bus_tx_buffer[0]=bip;		// mensagem
	bus_tx_buffer[1]=qtd_bip;
	BusSendMessage(PlacaDisplay,D_PlayBeep,2);
}
/************************************************************************************/
/*	void LimpaBufferTeclasDisplay(void)												*/
/*	Função: Limpa o buffer de teclas pressionadas									*/
/*	Parâmetros:																		*/
/*		nenhum																		*/
/*	Retorno:																		*/
/*		nenhum																		*/
/************************************************************************************/
void LimpaBufferTeclasDisplay(void)
{
	BusSendMessage(PlacaDisplay,D_CleanKeyBuffer,0);	// envia a mensagem para a placa de rele
}
/************************************************************************************/
/*	void LimpaBufferTeclasDisplay(void)												*/
/*	Função: Converte o valor lido pela placa conversor A/D em tensão(decimal) e 	*/
/*	e exibe o resultado no display na posição selecionada							*/
/*	Parâmetros:																		*/
/*		Linha - linha do display onde a mensagem será exibida (1 a 4)				*/
/*		Coluna - coluna do display onde a mensagem será exibida	(0 a 18)			*/
/*		ValorLido - valor lido pela placa conversor A/D (0 a 1024)					*/
/*		Linha - linha do display onde a mensagem será exibida (1 a 4)				*/
/*		Escala - Fundo de escala utilizado para ler o valor							*/
/*			1 - para fundo de escala de 5 V											*/
/*			2 - para fundo de escala de 20 V										*/
/*	Retorno:																		*/
/*		nenhum																		*/
/************************************************************************************/
void ExibeTensaoLida(char Linha, char Coluna, int ValorLido, char Escala)
{
	bus_tx_buffer[0]=Linha;
	bus_tx_buffer[1]=Coluna;
	bus_tx_buffer[2]=ValorLido>>8;
	bus_tx_buffer[3]=ValorLido&0x0F;
	bus_tx_buffer[4]=Escala;

	BusSendMessage(PlacaDisplay,D_ShowVoltage,5);	// envia a mensagem para a placa de rele
}
/************************************************************************************/
/*	char EstadoTeclas(void)															*/
/*	Função: Verifica o estado das teclas da placa Display						 	*/
/*	Parâmetros:																		*/
/*		nenhum																		*/
/*	Retorno:																		*/
/*		1 byte onde os bits de 0 a 5 representam o estado das teclas				*/
/*			bit em 0 - tecla em repouso												*/
/*			bit em 1 - tecla pressionada											*/
/*		Se valor = 0xFF = ERRO														*/
/************************************************************************************/
/*
		Retorno :
			D + 0 + N.Bytes + x (chave x foi pressionada, onde x 1 a 6), Dados ou comando
*/
char EstadoTeclas(void)
{
	char teclas;
	BusSendMessage(PlacaDisplay,D_KeyStatus,0);	// envia a mensagem para a placa display
	if((BUS_ACK)&&(rx_count==1)) 
	{
		teclas=bus_rx_buffer[0];
		return(teclas);
	}
	else
	{
		return(0xFF);
	}
}

/************************************************************************************/
/*	void SendProductName(void)														*/
/*	Função: Envia o nome do produto que será testado pela Jiga,					 	*/
/*			dependendo também se será a versão Mexico ou Brasil						*/
/*	Retorno:																		*/
/*		nenhum																		*/
/************************************************************************************/
void SendProductName(void)
{
	SendTextMessage(1, 0, MsgNomeProduto);
}

void ExibeContador(void)
{
    unsigned int Count;
 
	bus_tx_buffer[0] = 1;   // Linha 1
    bus_tx_buffer[1] = 20;  // Coluna 20

    bus_tx_buffer[2] = (Counter/1000) + 48;       //milhar
    bus_tx_buffer[3] = ((Counter % 1000)/100) + 48;       //centena
    bus_tx_buffer[4] = (((Counter % 1000) % 100) / 10) + 48;       //dezena
    bus_tx_buffer[5] = (((Counter % 1000) % 100) % 10)  + 48;   //unidade

    BusSendMessage(PlacaDisplay, D_ShowMessage, 6);
    
	bus_tx_buffer[0]=2;     // Linha 2
	bus_tx_buffer[1]=0;     // Coluna 0
	
	for(Count=0;Count<24;Count++)
		bus_tx_buffer[Count+2]=' ';
	
	BusSendMessage(PlacaDisplay,D_ShowMessage,26);
}

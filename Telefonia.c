/****************************************************************/
/* Intelbras S/A												*/
/* Nome do arquivo - Telefonia.c								*/
/* Jiga Universal -	Placa Principal								*/
/* Fun��o: Emula��o de linha telefonica, reconhecimento e gera-	*/
/* ��o de DTMF,	Gera��o de Ring									*/
/* Autor: Augusto Cezar Medeiros dos Santos						*/
/* Data de Cria��o - 17/07/2010									*/
/****************************************************************/
#include "define.h"
#include "global_vars.h"


/********************************** Placa de telefonia ************************************

	0x01 = Resultado do teste Ring+Discagem
		T + Endere�o + 0x01 + N.Bytes=0 + '\0'
		Fun��o - Verifica o resultado dos testes realizados
		Retorno :
			T + Endere�o + N.Bytes=1 + Resultado + CS
			Resultado esperado - 1 byte - 0x11
				bit 0 setado - a central reconheceu o RING e atendeu a chamada
				bit 4 setado - a central desligou a chamada
	0x02 = Resultado do teste Contact-ID
		T + Endere�o + 0x02 + N.Bytes=0 + '\0'
		Fun��o - Verifica o resultado dos testes realizados
		Retorno :
			T + Endere�o + N.Bytes=1 + Resultado + CS
			Resultado esperado - 1 byte - 0x0F
				bit 0 setado - a central ocupou a linha
				bit 1 setado - a placa reconheceu a discagem do telefone esperado 
				bit 2 setado - a placa reconheceu a sequencia Contact-ID e gerou o KissOff
				bit 3 setado - a central desligou a chamada
			
*********************************************************************************************/
#define		T_ResultRingDial		0x01	// resultado do teste de gera��o do ring e discagem
#define		T_ResultContact_ID      0x02	// resultado do teste Contact ID


/************************************************************************/
/*	void ResetPhoneResults(void)										*/
/*	Fun��o: Reseta o resultado dos testes executados anteriormente.		*/
/*	Deve ser executada sempre no inicio do teste						*/
/*	Par�metros:															*/
/*		nenhum															*/
/*	Retorno:															*/
/*		nenhum															*/
/************************************************************************/
void ResetPhoneResults(void)
{
	BusSendMessage(PlacaTelefonia,T_PhoneReset,0);	// envia a mensagem para a placa de telefonia
}
/************************************************************************/
/*	void StartRing(void)												*/
/*	Fun��o: Inicia a gera��o de Ring para testar  circuito de detec��o 	*/
/*	do produto 															*/
/*	Par�metros:															*/
/*		nenhum															*/
/*	Retorno:															*/
/*		nenhum															*/
/************************************************************************/
void StartRing(void)
{
	BusSendMessage(PlacaTelefonia,T_StartRing,0);	// envia a mensagem para a placa de telefonia
}
/************************************************************************/
/*	void StartDial(void)												*/
/*	Fun��o: Inicia a gera��o de DTMF, para testar o circuito de detec��o*/
/*	do produto 															*/
/*	OBS:- � necess�rio ligar o Rele de alimenta��o da linha antes de	*/
/*	executar este comando												*/
/*	Par�metros:															*/
/*		nenhum															*/
/*	Retorno:															*/
/*		nenhum															*/
/************************************************************************/
void StartDial(void)
{
	BusSendMessage(PlacaTelefonia,T_StartDTMF,0);	// envia a mensagem para a placa de telefonia
}
/************************************************************************************/
/*	char ResultRingAndDial(void)													*/
/*	Fun��o: Solicita o resultado dos testes de Ring e DTMF			 				*/
/*		O reconhecimento de DTMF deve ser veirficado no produto em teste			*/
/*	Par�metros:																		*/
/*		nenhum																		*/
/*	Retorno:																		*/
/*	Resultado esperado - 1 byte - 0x11												*/
/*		bit 0 setado - a central ocupou a linha										*/
/*		bit 4 setado - a central desocupou a linha									*/
/*		Se n�o obteve uma resposta v�lida retorna 0xFF								*/
/************************************************************************************/
char ResultRingAndDial(void)
{
	BusSendMessage(PlacaTelefonia,T_ResultRingDial,0);	// envia a mensagem para a placa de telefonia
	if((BUS_ACK)&&(rx_count==1))
		return(bus_rx_buffer[0]);
	else
		return(0xFF);
}
/************************************************************************************/
/*	char ResultContactID(void)														*/
/*	Fun��o: Solicita o resultado do reconhecimento de um evento contact-ID			*/
/*	Par�metros:																		*/
/*		nenhum																		*/
/*	Retorno:																		*/
/*	Resultado esperado - 1 byte - 0x0F												*/
/*		bit 0 setado - a central ocupou a linha										*/
/*		bit 1 setado - a placa reconheceu a discagem do telefone esperado			*/ 
/*		bit 2 setado - a placa reconheceu a sequencia Contact-ID e gerou o KissOff	*/
/*		bit 3 setado - a central desligou a chamada									*/
/*		Se n�o obteve uma resposta v�lida retorna 0xFF								*/
/************************************************************************************/
char ResultContactID(void)
{
	BusSendMessage(PlacaTelefonia,T_ResultContact_ID,0);	// envia a mensagem para a placa de telefonia
	if((BUS_ACK)&&(rx_count==1))
		return(bus_rx_buffer[0]);
	else
		return(0xFF);
}



/****************************************************************/
/* Intelbras S/A												*/
/* Nome do arquivo - Telefonia.c								*/
/* Jiga Universal -	Placa Principal								*/
/* Função: Emulação de linha telefonica, reconhecimento e gera-	*/
/* ção de DTMF,	Geração de Ring									*/
/* Autor: Augusto Cezar Medeiros dos Santos						*/
/* Data de Criação - 17/07/2010									*/
/****************************************************************/
#include "define.h"
#include "global_vars.h"


/********************************** Placa de telefonia ************************************

	0x01 = Resultado do teste Ring+Discagem
		T + Endereço + 0x01 + N.Bytes=0 + '\0'
		Função - Verifica o resultado dos testes realizados
		Retorno :
			T + Endereço + N.Bytes=1 + Resultado + CS
			Resultado esperado - 1 byte - 0x11
				bit 0 setado - a central reconheceu o RING e atendeu a chamada
				bit 4 setado - a central desligou a chamada
	0x02 = Resultado do teste Contact-ID
		T + Endereço + 0x02 + N.Bytes=0 + '\0'
		Função - Verifica o resultado dos testes realizados
		Retorno :
			T + Endereço + N.Bytes=1 + Resultado + CS
			Resultado esperado - 1 byte - 0x0F
				bit 0 setado - a central ocupou a linha
				bit 1 setado - a placa reconheceu a discagem do telefone esperado 
				bit 2 setado - a placa reconheceu a sequencia Contact-ID e gerou o KissOff
				bit 3 setado - a central desligou a chamada
			
*********************************************************************************************/
#define		T_ResultRingDial		0x01	// resultado do teste de geração do ring e discagem
#define		T_ResultContact_ID      0x02	// resultado do teste Contact ID


/************************************************************************/
/*	void ResetPhoneResults(void)										*/
/*	Função: Reseta o resultado dos testes executados anteriormente.		*/
/*	Deve ser executada sempre no inicio do teste						*/
/*	Parâmetros:															*/
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
/*	Função: Inicia a geração de Ring para testar  circuito de detecção 	*/
/*	do produto 															*/
/*	Parâmetros:															*/
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
/*	Função: Inicia a geração de DTMF, para testar o circuito de detecção*/
/*	do produto 															*/
/*	OBS:- É necessário ligar o Rele de alimentação da linha antes de	*/
/*	executar este comando												*/
/*	Parâmetros:															*/
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
/*	Função: Solicita o resultado dos testes de Ring e DTMF			 				*/
/*		O reconhecimento de DTMF deve ser veirficado no produto em teste			*/
/*	Parâmetros:																		*/
/*		nenhum																		*/
/*	Retorno:																		*/
/*	Resultado esperado - 1 byte - 0x11												*/
/*		bit 0 setado - a central ocupou a linha										*/
/*		bit 4 setado - a central desocupou a linha									*/
/*		Se não obteve uma resposta válida retorna 0xFF								*/
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
/*	Função: Solicita o resultado do reconhecimento de um evento contact-ID			*/
/*	Parâmetros:																		*/
/*		nenhum																		*/
/*	Retorno:																		*/
/*	Resultado esperado - 1 byte - 0x0F												*/
/*		bit 0 setado - a central ocupou a linha										*/
/*		bit 1 setado - a placa reconheceu a discagem do telefone esperado			*/ 
/*		bit 2 setado - a placa reconheceu a sequencia Contact-ID e gerou o KissOff	*/
/*		bit 3 setado - a central desligou a chamada									*/
/*		Se não obteve uma resposta válida retorna 0xFF								*/
/************************************************************************************/
char ResultContactID(void)
{
	BusSendMessage(PlacaTelefonia,T_ResultContact_ID,0);	// envia a mensagem para a placa de telefonia
	if((BUS_ACK)&&(rx_count==1))
		return(bus_rx_buffer[0]);
	else
		return(0xFF);
}



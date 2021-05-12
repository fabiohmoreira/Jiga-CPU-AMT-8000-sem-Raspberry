/****************************************************************/
/* Intelbras S/A												*/
/* Nome do arquivo - Barramento.c								*/
/* Jiga Universal -	Placa Principal								*/
/* Fun��o: Envio de mensagems atrav�s do barramento da central	*/
/* de alarme													*/
/* Autor: Augusto Cezar Medeiros dos Santos						*/
/* Data de Cria��o - 14/06/2010									*/
/****************************************************************/
#include "define.h"
#include "global_vars.h"

/************************************************************************/
/*	char BarramentoEnviaMSGResposta(char Command, char NumBytes)		*/
/*	Fun��o: Envia mensagem para a placa barramento enviar para o		*/
/*	produto em teste													*/
/*	Par�metros:															*/
/*		Address:Endere�o da placa em teste. Normalmente=0x01, podendo	*/
/* 				variar de acordo com o produto testado					*/
/*		Command: Comando para placa em teste. Varia de acordo com o 	*/
/*				produto testado											*/
/*		NumBytes: N�mero de bytes da mensagem. Se n�o houver nenhum	 	*/
/*				par�metro adicional este valor deve ser "0"				*/
/*		Se houver algum par�metro extra os mesmos devem ser passados	*/
/*		utilizando a vari�vel bus_tx_buffer[x] a partir do �ndice [3]	*/
/*	Retorno:															*/
/*		1 se MSG ok e 0 se houve falha									*/
/*		se houver alguma resposta da placa em teste a mesma ser� dada	*/
/*		da seguinte forma:												*/
/*		bus_rx_buffer[1] =  n�mero de bytes								*/
/*		a resposta vir� a partir de bus_rx_buffer[2]					*/
/************************************************************************/
char BarramentoEnviaMSG(char Address,char Command, char NumBytes)
{
	bus_tx_buffer[0]=Address;
	bus_tx_buffer[1]=Command;
	bus_tx_buffer[2]=NumBytes;
	BusSendMessage(PlacaBarramento,B_Msg,bus_tx_buffer[2]+3);
	if((BUS_ACK)&&(rx_count==0))
	{
        if(Command==0x02)
			Delay_ms(100);
        else
			Delay_ms(55);
//		Delay_ms(55);
		BusSendMessage(PlacaBarramento,B_MsgAnswer,0);
		if((BUS_ACK)&&(bus_rx_buffer[0]==0xA5)&&(rx_count>0))
			return(1);
		else
			return(0);
	}
	else
		return(0);
}
/************************************************************************/
/*	char BarramentoEnviaMSGComResposta(char Command, char NumBytes)		*/
/*	Fun��o: Envia mensagem sem resposta para a placa barramento enviar	*/
/*	para o produto em teste												*/
/*	Par�metros:															*/
/*		Command: Comando para placa em teste. Varia de acordo com o 	*/
/*				produto testado											*/
/*		NumBytes: N�mero de bytes da mensagem. Se n�o houver nenhum	 	*/
/*				par�metro adicional este valor deve ser "0"				*/
/*		Se houver algum par�metro extra os mesmos devem ser passados	*/
/*		utilizando a vari�vel bus_tx_buffer[x] a partir do �ndice [2]	*/
/*	Retorno:															*/
/*		0 se houve falha												*/
/*		1 se MSG ok, neste caso a resposta deve ser lida na vari�vel 	*/
/*			bus_rx_buffer[x] e o n�mero de bytes recebidos � dado pela	*/
/*			vari�vel rx_count											*/
/************************************************************************/
/*char BarramentoEnviaMSGComResposta(char Command, char NumBytes)
{
	bus_tx_buffer[0]=Command;
	bus_tx_buffer[1]=NumBytes+2;
	BusSendMessage(PlacaBarramento,B_MsgNoAnswer,bus_tx_buffer[1]);
	if((BUS_ACK)&&(rx_count==2))
		return(1);
	else
		return(0);
}*/



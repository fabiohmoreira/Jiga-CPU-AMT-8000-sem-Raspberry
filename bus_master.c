
/****************************************************************************************/
/*	Protocolo :																			*/
/*																						*/
/*	Pergunta :																			*/
/*	tipo de placa + endereço + comando + num. bytes + dados + cs						*/
/*																						*/
/*	Resposta :																			*/
/*	tipo de placa + endereço + num. bytes + dados + cs									*/
/*																						*/
/*	Resposta sem conteúdo :	(quando o comando recebido não tem resposta a ser enviada)	*/
/*	tipo de placa + endereço															*/
/*																						*/
/****************************************************************************************/

#include "p24fj48ga004.h"
#include "define.h"
#include "global_vars.h"
#include "DispositivosPresentes.h"
int RecieveTimeout;

void BUS_Proc(void)
{
	if(!full_recieved)
	{
		switch(send_msg_state)
		{	
			case 0:
				BUS_timeout=3000;
				U1STAbits.OERR=0;
				if(U1STAbits.URXDA)
					addr_recieved=U1RXREG;		// somente para limpar buffer de recepção
				else
				{
					send_msg_state++;
					for(tx_count=0;tx_count<120;tx_count++)
						bus_rx_buffer[tx_count]=0;
					addr_recieved=0;
					rx_count=0;
				}
				U1STAbits.OERR=0;
			break;
			case 1:
				BUS_CRC=0;
				BUS_ACK=0;
				U1TXREG=board_type;				// trasnsmite tipo da placa
				BUS_CRC^=board_type;			// calula CRC
				U1TXREG=addr_slave;				// trasnsmite endereço do escravo
				BUS_CRC^=addr_slave;			// calula CRC
				U1TXREG=comand;					// transmite comando e sub-comando
				BUS_CRC^=comand;				// calcula CRC
				U1TXREG=num_bytes;				// transmite número de bytes do pacote
				BUS_CRC^=num_bytes;				// calcula CRC
				tx_count=0;
				send_msg_state++;
			break;
			case 2:
					if(U1STAbits.URXDA)	
						addr_recieved=U1RXREG;		// somente para limpar buffer de recepção
				if(num_bytes>0)					// se número de bytes >0 transmite dados contidos em bus_tx_buffer e calcula CRC
				{
					if(!U1STAbits.UTXBF)		// aguarda por posição livre no buffer de transmissão
					{
						U1TXREG=bus_tx_buffer[tx_count];
						BUS_CRC^=bus_tx_buffer[tx_count];
						tx_count++;
					}
				}
				if(tx_count>=num_bytes)
					send_msg_state++;
			break;
			case 3:
				if(!U1STAbits.UTXBF)			// aguarda posição livre no buffer de transmissão
				{
					BUS_CRC^=0xFF;				// se CRC =0 complementa
					U1TXREG=BUS_CRC;			// transmite CRC
					send_msg_state++;
				}
			break;
			case 4:
				if(U1STAbits.TRMT)				// aguarda até que todos os dados tenham sido transmitidos
				{
					U1STAbits.OERR=0;
					addr_recieved=U1RXREG;		// somente para limpar buffer de recepção
					addr_recieved=U1RXREG;		// somente para limpar buffer de recepção
					addr_recieved=U1RXREG;		// somente para limpar buffer de recepção
					addr_recieved=U1RXREG;		// somente para limpar buffer de recepção
					BUS_CRC=0;
					tx_count=0;
					send_msg_state++;
				}
			break;
			case 5:
				if(addr_slave!=broadcast)		// se não foi broadcast seta para recepção
				{
					{
						U1STAbits.UTXEN = FALSE;	// desabilita  transmissão
						RS485_DIR=false;			// Acerta direção para recepção
						send_msg_state++;
						BUS_timeout=20;			// timeout da recepção
					}
				}
				else
				{
					send_msg_state++;
					BUS_timeout=20;			// timeout da recepção
				}
			break;
			case 6:
				if(addr_slave!=broadcast)		// se não foi broadcast executa recepção do Ack ou da mensagem dependendo da solicitação
				{
					if((U1STAbits.URXDA)&&(!U1STAbits.OERR))			// se recebeu um byte
					{
						BUS_timeout=10;			// timeout da recepção
						if(tx_count==0)
						{	
							board_type_recieved=U1RXREG;
							BUS_CRC^=board_type_recieved;
						}
						else if(tx_count==1)
						{	
							addr_recieved=U1RXREG;
							BUS_CRC^=addr_recieved;
						}
						else if(tx_count==2)
						{
							rx_count=U1RXREG;
							BUS_CRC^=rx_count;
						}
						else 
						{
							bus_rx_buffer[tx_count-3]=U1RXREG;		// preenche buffer de recepção
							if(tx_count!=(rx_count+3))BUS_CRC^=bus_rx_buffer[tx_count-3];
						}
						tx_count++;									// incrementa uma posição
						if(comand>=0x20)							// se não for comando com resposta
						{
							if	(	
									(addr_recieved==addr_slave)&&(board_type_recieved==board_type)&&
									(tx_count==4)
								)
							{
								BUS_CRC^=0xFF;								// se CRC =0 complementa
								if(BUS_CRC==bus_rx_buffer[0])
									BUS_ACK=1;	// byte recebido=endereço transmitido, então reconhece ack
								full_recieved=1;
							}
						}
						else if((tx_count>3)&&(tx_count>(rx_count+3)))
						{
							full_recieved=1;
							BUS_CRC^=0xFF;								// se CRC =0 complementa
							if((BUS_CRC==bus_rx_buffer[rx_count])&&(addr_recieved==addr_slave)&&(board_type_recieved==board_type))
								BUS_ACK=1;									// se CRC ok valida recepção
						}
						else if(tx_count>120)
						{
							full_recieved=1;
						}
					}
					if(full_recieved||U1STAbits.OERR)
					{
						send_msg_state++;
						RS485_DIR=true;				// Acerta direção para transmissão
						U1STAbits.UTXEN = TRUE;		// habilita  transmissão
						send_msg_state=0;
						BUS_timeout=0;
					}
				}
				else
					send_msg_state++;
			break;
			default :
				RS485_DIR=true;				// Acerta direção para transmissão
				U1STAbits.UTXEN = TRUE;		// habilita  transmissão
				send_msg_state=0;
				full_recieved=1;
				BUS_timeout=0;
			break;
		}
	}
	if(BUS_timeout>0)
	{
		BUS_timeout--;
		if(BUS_timeout==0)
		{
			U1STAbits.UTXEN = FALSE;	// desabilita  transmissão/limpa buffer
			U1STAbits.OERR=0;
			RS485_DIR=true;				// Acerta direção para transmissão
			U1STAbits.UTXEN = TRUE;		// habilita  transmissão
			send_msg_state=0;
			BUS_timeout=0;
			BUS_CRC=0;
			BUS_ACK=0;
			full_recieved=1;
		}
	}
}

/************************************************************************************/
/*	void BusSendMessage(char BoardType, char Address, char Command, char NumBytes)	*/
/*	Função: Preenche as variáveis para envio da mensagem, se houve resposta 		*/
/*	BUS_ACK=1, caso contrário BUS_ACK=0. Se houver algum conteúdo além do coamando	*/
/*	bus_tx_buferr[] deve ser preenchido com os dados a serem enviados				*/
/*	Parâmetros:																		*/
/*	BoardType - Tipo da placa periférico que vai receber a mensagem					*/
/*	Address - Endereço da placa periférico que vai receber a mensagem				*/
/*	Command - comando a ser enviado													*/
/*	NumBytes - número de bytes do conteúdo											*/
/*	Retorno:																		*/
/*	nenhum																			*/
/************************************************************************************/
void BusSendMessage(char Board, char Command, char NumBytes)
{
	int CountErro=0;
	do
	{
		board_type=Type[Board];		// tipo da placa
		addr_slave=Address[Board];	// endereço do escravo
		comand=Command;				// comando e sub-comando
		num_bytes=NumBytes;			// número de bytes do pacote
		full_recieved=0;
		while(!full_recieved);
		Delay_ms(10); 
		CountErro++;
	}while((!BUS_ACK)&&(CountErro<3)&&(bus_fail_counter[Board]<4));
/*	if((!BUS_ACK)&&(CountErro==3)&&(bus_fail_counter[Board]<4))
	{
		bus_fail_counter[Board]=5;
		PutErrorMessageOnBuffer(Board+100);
	}*/
}

/************************************************************************************/
/*	void PutErrorMessageOnBuffer(char ErrorMessage)									*/
/*	Função: Preenche uma posição do buffer de mensagens de erro						*/
/*	Parâmetros:																		*/
/*		ErrorMessage - mensagem de erro que vai ser armazenada						*/
/*	Retorno:																		*/
/*	nenhum																			*/
/************************************************************************************/
void PutErrorMessageOnBuffer(char ErrorMessage)
{
	MsgToShowBuffer[MsgToShowPtr_WR]=ErrorMessage;
	MsgToShowPtr_WR++;
	MsgToShowPtr_WR&=0x7F;
}

/************************************************************************************/
/*	void VerifyPresentBusDevices(void)												*/
/*	Função: Consulta os dispositivos definidos em DispositivosPresentes.h, em caso	*/
/*	de falha exibe uma mensagem de erro no display									*/
/*	Parâmetros:																		*/
/*	nenhum																			*/
/*	Retorno:																		*/
/*	nenhum																			*/
/************************************************************************************/
void VerifyPresentBusDevices(void)
{
	static char Count;
    
	if(VerifyPresentBusDevicesFlag==0)
	{
        if (VerifyPresentBusDevicesFlag == 0) 
        {
        VerifyPresentBusDevicesFlag = 1;
        if (PresentDevices[Count] != 0) 
        {
            if (!(((Count >= 11)&&(Count <= 18)) && (StatusGr != 0))) 
            {
                BusSendMessage(Count, PlacaPresente, 0);   
			if(BUS_ACK)
			{			}
			else if(bus_fail_counter[Count]<4)
			{
				bus_fail_counter[Count]++; 
				if(bus_fail_counter[Count]==4)
				{
                    PutErrorMessageOnBuffer(Count+100);
                    EmiteBipe(2,1);
                    bus_fail_counter[Count]=5;
                    if((EmTeste)||(IniciaTesteState))
                    {
                        FinalizaTesteFlag=1;
                        IniciaTesteFlag=0;
                    }
				}
			}
			LED_LD1^=1;
		}
        }    
		Count++;
		if(Count>=19)
		{
			Count=0;
		}
	}
}
}    

/************************************************************************************/
/*	void ShowErrorMessages(void)													*/
/*	Função: Exibe as mensagens de erro geradas pelo teste ou por dispositivos 		*/
/*	ausentes. As mensagens são exibidas em sequencia quando o processo de teste não	*/
/*	estiver em execução																*/
/*	Parâmetros:																		*/
/*		A variável MsgToShowBuffer[] deve ser prenchida com o índice da menssagem 	*/
/*		de erro correspondente definidas no arquivo Mensagens.h. As mensagens de	*/
/*		erro referentes ao teste do produto devem ser prenchidas a partir da posição*/
/*		100 da variável MensagensGerais[]											*/
/*	Retorno:																		*/
/*	nenhum																			*/
/************************************************************************************/
void ShowErrorMessages(void)
{
	static char Messages[3];
/*	if(MsgToShowDelay==0)
	{
		MsgToShowDelay=1;
		LimpaDisplay();
	}*/
	if((MsgToShowPtr_WR>0)&&(MsgToShowDelay==0)&&(!EmTeste))
	{
		MsgToShowDelay=1;
		if(MsgToShowPtr_RD==0)
		{
			Messages[0]=0;
			Messages[1]=0;
			Messages[2]=0;
		}
		
		Messages[0]=Messages[1];
		Messages[1]=Messages[2];
		Messages[2]=MsgToShowBuffer[MsgToShowPtr_RD];
			
		SendTextMessage(2, 0, Messages[0]);
		SendTextMessage(3, 0, Messages[1]);
		SendTextMessage(4, 0, Messages[2]);
		
		MsgToShowPtr_RD++;
		if(MsgToShowPtr_RD>=MsgToShowPtr_WR)
			MsgToShowPtr_RD=0;
	}
}


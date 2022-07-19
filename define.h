//Arquivo de definições Placa Principal versão 1.0.0

#include "p24fj48ga004.h"


#ifndef _DEFINE_H
	#define _DEFINE_H
	
	#define broadcast	0xff
	#define chave_NA	0x00
	#define chave_NF	0x3f
	#define FALSE 0x00
	#define TRUE  0x01
	#define false 0x00
	#define true  0x01

	#define	RESET_MAC
	
	/***********************************************************************
	  ----------------------------- Portas --------------------------------
	 **********************************************************************/
	
	/************************ Porta A *****************************/
	#define	TECLA_S1		_RA8				// I
	#define	TECLA_S3		_RA9				// I
	#define	LED_LD2			_LATA10				// O
	
	#define	TRISA_init		0XFBFF

	/************************ Porta B *****************************/
	#define	LED_LD3			_LATB11				// 0
	#define	TECLA_S2		_RB12				// I
	
	#define	TRISB_init		0XF7FF

	/************************ Porta C *****************************/

	#define	RX				_LATC4				// 0 
	#define	RS485_DIR		_LATC6				// 0 
	#define	LED_LD1			_LATC7				// O

	#define	RX_TRIS			_TRISC4				// 0 
	#define	TRISC_init		0xFF3F
	
		//Referencias de tensão para carregador bateria a rede elétrica
		// (tensão de entrada *0,196298)/0,0029297
		#define ref_0_1V	7
		#define ref_0_5V	33
		#define ref_03V		201
		#define ref_07V		469
		#define ref_10V		670
		#define ref_11V		737
		#define ref_11_5V	770
		#define ref_12V		804
		#define ref_12_25V	820
		#define ref_12_5V	837
		#define ref_13V		871
		#define ref_13_8V	924
		#define ref_14_5V	971	
		
        ////////////níveis de tensão/////////////////
        #define Ref_1V_Escala5V			190		//	1V * 190,7397
        #define Ref_1_7_Escala5V        324     //  1,7V * 190,7397
        #define Ref_2V_Escala5V			380		//	2V * 190,7397
        #define Ref_2_5V_Escala5V		477		//	2,5V * 190,7397
        #define Ref_2_7V_Escala5V       515     //  2,7V * 190,7397
        #define Ref_3V_Escala5V			572		//	3V * 190,7397
        #define Ref_3_5V_Escala5V		667		//	3,5V * 190,7397
        #define Ref_4V_Escala5V         762     //  4V * 190,7397

		#define sir_500_ma	37	// corrente da sirene = 500 mA no resistor de 0.22R = 0,11V
		#define sir_1_a		75	// corrente da sirene = 1 A no resistor de 0.22R = 0,22V
		#define sir_10_a	770	// corrente da sirene = 10,22 A no resistor de 0.22R = 2,25V

	#define only_pass			0x00
	#define part_a_pass			0x01
	#define part_b_pass			0x02
	#define tsk_comm			0x00
	#define tsk_parser			0x01
	#define tsk_sectors			0x02

#endif

///////////////////////// Comandos do Barramento ///////////////////////////
#define		PlacaPresente		0xF0

// Índice interno das placas para envio de mensagens no barramento
#define		PlacaRele_0			0x00
#define		PlacaRele_1			0x01
#define		PlacaRele_2			0x02
#define		PlacaRele_3			0x03
#define		PlacaAD_0			0x04
#define		PlacaAD_1			0x05
#define		PlacaAD_2			0x06
#define		PlacaAD_3			0x07
#define		PlacaTelefonia		0x08
#define		PlacaBarramento		0x09
#define		PlacaDisplay		0x0A
#define		PlacaGravador_0		0x0B
#define		PlacaGravador_1		0x0C
#define		PlacaGravador_2		0x0D
#define		PlacaGravador_3		0x0E
#define		PlacaGravador_4		0x0F
#define		PlacaGravador_5		0x10
#define		PlacaGravador_6		0x11
#define		PlacaGravador_7		0x12

////////////////// Reles /////////////////////////
#define		SobeGaveta                      0x01
#define		LigaTrava                       0x02
#define		SobeTampa                       0x04
#define     RL_Comut_CargaBateria_Placa1    0x04
#define     RL_Comut_CargaBateria_Placa2    0x20

//#define RL_Aciona_Gravadores    0x40 //Relé em NF da placa 0

/********************************** Placa Conversor A/D ******************************************
A = Placa conversor AD
	Comandos :
	0xf0 = Teste de comunicação (Não executa nenhuma ação)
		A + Endereço + N.Bytes + 0xf0 + '\0'
		Retorno = A + Endereço + N.Bytes=0
	0xf1 = Setup do valor médio de tensão para medição de período
		A + Endereço + N.Bytes + 0xf1 + Numero do canal + (valor médio MSD) + (valor médio LSD) + '\0'
		Retorno = A + Endereço + N.Bytes=0
	0xf2 = Setup dos canais AD
		A + Endereço + N.Bytes + 0xf1 + canais + '\0'
			canais 	= 	Bits em 1 = ativado
						Bits em 0 = desativado
		Retorno = A + Endereço + N.Bytes=0
	0x01 = Ler resultado de medição DC em um canal selecionado
		A + Endereço + N.Bytes + 0xf1 + Numero do canal + '\0'
		Retorno = A + Endereço + N.Bytes + (Valor MSD) + (Valor LSD) + '\0'
	0x02 = Ler resultado de medição de periodo
		A + Endereço + N.Bytes + 0xf1 + Numero do canal + '\0'
		Retorno = A + Endereço + N.Bytes + (Valor+ MSD) + (Valor+ LSD) + (Valor- MSD) + (Valor- LSD) + '\0'
	0x03 = Ler periodo que esta sendo medido
*********************************************************************************************/
#define		A_AverageVoltage	0xF1	// Define o valor médio de tensão para ler o período de uma forma de onda 
#define		A_ChannelEnabled	0xF2	// Habilita/Desabilita o uso de canis de A/D
#define		A_ReadVoltage		0x01	// Lê o valor de tensão medido pelo canal selecionado
#define		A_ReadPeriod		0x02	// Lê o periodo medido pelo canal selecionado
#define		A_ReadInstantPeriod	0x03	// Lê o periodo que esta sendo medido pelo canal selecionado

/********************************** Placa Barramento ******************************************
B = Placa barramento
	Comandos :
	0xF0 = Teste de comunicação (Não executa nenhuma ação)
		B + Endereço + N.Bytes + 0xf0 + '\0'
		Retorno = B + Endereço + N.Bytes=0
	0xF1 = Envia mensagem sem resposta para a placa barramento
		B + Endereço + N.Bytes + 0xF1 + MSG + '\0'
		Retorno = B + Endereço + N.Bytes=0
	0xF2 = Altera o modo de operação a placa barramento (Mestre ou Escravo)
		B + Endereço + N.Bytes + 0xF2 + '\0'
		Retorno = B + Endereço + N.Bytes=0
	
	0x01 = Envia mensagem com resposta para a placa barramento
		B + Endereço + N.Bytes + 0x01 + MSG + '\0'
		Retorno = B + Endereço + N.Bytes + MSGResposta + '\0'
*********************************************************************************************/
#define		B_Msg			0xF1	// Envia mensagem sem resposta para a placa barramento
#define		B_ModoOperacao	0xF2	// Altera o modo de operação a placa barramento (Mestre ou Escravo)
#define		B_MsgAnswer		0x01	// Envia mensagem com resposta para a placa barramento
#define		Escravo			0x01
#define		Mestre			0x00

////////////////// Placa display ////////////////////////////////////////////
/********************************** Placa display ******************************************
D = Placa display
	Comandos :
	0xf1 = Limpar Display
		D + 0 + 0xf1 + N.Bytes + '\0'
		Retorno = D + 0
	0xf2 = Escrever string na posição selecionada
		D + 0 + 0xf2 + N.Bytes + Linha + Coluna + String + '\0'
		Retorno = D + 0
	0xf3 = Comando
		D + 0 + 0xf3 + N.Bytes + Comando + qtd bips + '\0'
		Comandos :	0x01 = Acionar o BIP de OK
					0x02 = Acionar o BIP de ERRO
					0x03 = Acionar o BIP a cada segundo
					0x04 = Desabilitar o BIP de segundos
					0x05 = Acionar tres BIPs curto (inicio de teste ???)
		Retorno = D + 0
	0xf4 = Limpar "buffer" das chaves da placa display
		D + 0 + N.Bytes + 0xf4 + '\0'
		Retorno = D + 0 + N.Bytes=0
	0xf5 = converte o valor lido pela placa A/D para tensão e exibe a informação na posição selecionada
		D + 0 + N.Bytes + 0xf5 + Linha + Coluna +  (Valor MSD) + (Valor LSD) + Escala + '\0'
		Escala :	1 = 5V
					2 = 20V
		Retorno = D + 0 + N.Bytes=0
	0x01 = Estado das teclas
		D + 0 + 0x01 + N.Bytes + '\0'
		Retorno :
			D + 0 + N.Bytes + x
			x - os bits de 0 a 5 representam o estado das chaves 1 a 6
                   bit em 0 = chave em repouso
                   bit em 1 = chave pressionada
*********************************************************************************************/
#define		D_CleanDisplay		0xF1	// Limpar Display
#define		D_ShowMessage		0xF2	// Exibe mensagem na linha e coluna selecionadas
#define		D_PlayBeep			0xF3	// Emite bipe na placa display
#define		D_CleanKeyBuffer	0xF4	// Limpa o buffer de leitura das teclas
#define		D_ShowVoltage		0xF5	// Converte o valor lido pela placa A/D para tensão e exibe a informação na posição selecionada
#define		D_KeyStatus			0x01	// Verifica o estado das chaves da placa display

/********************************** Placa reles *********************************************
R = Placa reles
	Comandos :
	0xf1 = Desativar todos os reles
		R + Endereço + 0xf1 + N.Bytes + '\0'
		Retorno = R + Endereço
	0xf2 = Ligar ou desligar os reles selecionados
		R + Endereço + N.Bytes + 0xf2 + Comando + '\0'
		Comando	: 	O nible MSD especifica o rele que deve ser acionado
					O nible LSD especifica se liga ou desliga o rele especificado
					1 = liga / 0 = desliga
		Retorno = R + Endereço
	0xF3 = Teste
		R + Endereço + 0x01 + N.Bytes + Comando + '\0'
		Comando	:	Especicifica qual/quais rele(s) deve(m) ser testado
					Os bits de 0 a 7 do comando, especifica o(s) rele(s) a ser(em) testado(s)
		Retorno :
			R + Endereço
	0x02 = Query
		R + Endereço + 0x02 + N.Bytes + '\0'
		Retorno :	R + Endereço + Resultado
					Os bits de 0 a 7 do Resultado, especifica o resultado do teste dos reles
					1 = Ok / 0 = Falha
			
*********************************************************************************************/
#define		R_TurnAllRelaysOff		0xF1	// desliga todos os reles da placa	
#define		R_ChangeRelaysState		0xF2	// altera o estado dos reles selecionados	
#define		R_RelayAutoTest			0xF3	// inicia o teste automático dos reles
#define		R_RelayAutoTestAnswer	0x02	// verifica a resposta do teste automático dos reles

/********************************** Placa de telefonia ************************************
T = Placa de telefonia
	Comandos :
	0xf1 = Reset da placa
		T + Endereço + 0xf1 + N.Bytes=0 + '\0'
		Retorno = T + Endereço
	0xf2 = Inicia Ring
		Função -Inicia a geração de RING
		T + Endereço + 0xf2 + N.Bytes=0 + '\0'
		Retorno = T + Endereço
	0xf3 = Inicia Discagem
		Função - Se a central atendeu gera os dígitos 1 e # em DTMF
				e aguarda que a chamada seja desligada
		T + Endereço + 0xf3 + N.Bytes=0 + '\0'
		Retorno = T + Endereço
	OBS: - é necessário ligar o Rele de alaimentação da linha antes de executar este comando


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
#define		T_PhoneReset			0xF1	// reseta os resultados dos testes
#define		T_StartRing				0xF2	// inicia a geração do ring 
#define		T_StartDTMF				0xF3	// inicia a discagem DTMF para o produto testado
#define		T_ResultRingDial		0x01	// resultado do teste de geração do ring e discagem
#define		T_ResultContact_ID      0x02	// resultado do teste Contact ID

/********************************** Placa gravador ******************************************
G = Placa gravador
	Comandos :
	0xf0 = Teste de comunicação (Não executa nenhuma ação)
		G + Endereço + N.Bytes + 0xf0 + '\0'
		Retorno = A + Endereço + N.Bytes=0
	0xf1 = Aborta Gravação
		G + Endereço + 0xf1 + N.Bytes=0 + '\0'
	0xf2 = Seta processador	
		(Obs.: Este procedimento deve ser executado antes de qualquer gravação)
		G + Endereço + 0xf2 + P + N.Bytes=1 + '\0'
			P = Processador a ser gravado
				PIC_16F506  = 0x01
				PIC_16F677  = 0x02
				PIC_16F685  = 0x03
				PIC_16F1828 = 0x04
				PIC_24FJ16  = 0x05
				PIC_24FJ32  = 0x06
				PIC_24FJ48  = 0x07
				PIC_24FJ64  = 0x08
				PIC_24FJ96  = 0x09
				PIC_24FJ128 = 0x0a
	0xf3 = Inicia gravação
		G + Endereço + 0xf3 + Pr + N.Bytes=1 + '\0'
		Pr = Programa a ser gravado ( 1, 2 ou 3 )
	0x01 = Query	Retorna Status do gravador
		G + Endereço + N.Bytes + 0x01 + '\0'
		Retorno :	G + Endereço + N.Bytes + Resultado
				Resultado  =>	0x00 = Idle
								0x01 = Apagando
								0x02 = Gravação em andamento
								0x03 = Verificando gravação
								0x04 = Gravação OK
								0xf1 = Erro no apagamento
								0xf3 = Erro na gravação da memoria de programa
								0xf4 = Erro na gravação da configuração
								0xf5 = Não foi setado o processador
								0xf6 = Falha na tensão de alimentação (VDD)
								0xf7 = Falha na tensão de gravação (VPP)
	0x02 = Nome	Retorna o nome do programa
		G + Endereço + N.Bytes + 0x02 + '\0'
		Retorno :	G + Endereço + N.Bytes + Resultado

*********************************************************************************************/
#define		AbortaGR				0xF1	// aborta a gravação
#define		SetMicro				0xF2	// seta o microprocessador a ser gravado
#define		StartGr					0xF3	// inicia a gravação
#define		GrStatus				0x01	// retorna o andamento da gravação

#define	PIC_16F506 			0x01
#define	PIC_16F677			0x02
#define	PIC_16F685			0x03
#define	PIC_16F1828			0x04
#define	PIC_24FJ16			0x05
#define	PIC_24FJ32			0x06
#define	PIC_24FJ48			0x07
#define	PIC_24FJ64			0x08
#define	PIC_24FJ96			0x09
#define	PIC_24FJ128			0x0A
#define PIC_16LF1828 		0x0B
#define PIC_24FJ128GA106 	0x0C
#define PIC_16F1829         0x0D
#define SAM4E               0x10
#define ATSAMD10D14AM       0x11
#define ATSAMD20G16         0x12
#define ATSAMD21E17         0x13
#define ATSAMD10D14AS       0x14
#define ATSAME53N20A        0x15
#define PIC_16F15344        0x0E
#define PIC_16F15345        0x0F
#define ATTINY412           0x17

#define	MsgEmBranco                     0	
#define	MsgNomeProduto                  1	
#define	MsgDefeitos_Placa1              2
#define	MsgPinoAudioOut_Placa1          3
#define	MsgPinoAudioIn_Placa1           4
#define	MsgPinoRL_Placa1                5
#define	MsgPinoCL_Placa1                6
#define	MsgPinoDL_Placa1                7
#define	MsgPinoDR_Placa1                8
#define	MsgPinoRD_Placa1                9
#define	MsgTimeoutTeste_Placa1          10      
#define	MsgFalhaGPRS_Placa1             11    
#define	MsgFalhaWiFi_Placa1             12
#define	MsgFalhaEthernet_Placa1         13
#define	MsgFalhaBateria_Placa1          14
#define	MsgFalhaRF_Placa1               15
#define	MsgFalhaEEPROM_Placa1           16
#define	MsgDefeitos_Placa2              17
#define	MsgPinoAudioOut_Placa2          18
#define	MsgPinoAudioIn_Placa2           19
#define	MsgPinoRL_Placa2                20
#define	MsgPinoCL_Placa2                21
#define	MsgPinoDL_Placa2                22
#define	MsgPinoDR_Placa2                23
#define	MsgPinoRD_Placa2                24
#define	MsgTimeoutTeste_Placa2          25
#define	MsgFalhaGPRS_Placa2             26    
#define	MsgFalhaWiFi_Placa2             27
#define	MsgFalhaEthernet_Placa2         28
#define	MsgFalhaBateria_Placa2          29
#define	MsgFalhaRF_Placa2               30
#define	MsgFalhaEEPROM_Placa2           31
#define MsgFalhaGravacaoFinal_Placa1    32
#define MsgFalhaGravacaoFinal_Placa2    33
#define MsgTimeoutGravacao_Placa1       34
#define MsgTimeoutGravacao_Placa2       35
#define MsgErroTimeoutProg              36
#define	MsgErroApagamento               37
#define	MsgErroGrMemoProg               38
#define	MsgErroGrConfig                 39
#define	MsgFalhaTensaoGrVdd             40
#define	MsgFalhaTensaoGrVpp             41
#define	MsgFalhaPlacaAusente            42
#define	Msg_ValidaIO                    49
#define MsgGravandoFW_Teste             50
#define MsgGravandoFW_Final             51
#define MsgInicializandoPlacas          52
#define MsgTestando_Tensoes             53
#define MsgValidandotestes              54
#define MsgPreparando_Gravacao_Final    55
#define MsgFimdostestes                 56
#define	Msg_resultado_dos_testes        57
#define	Msg_pressione_chave             58 
#define	Msg_para_visualizar             59
#define	Msg_os_defeitos_correspondentes 60  
#define Msg_chave_inicio                61 
#define MsgBugGravacao                  62
#define MsgExecutandoTestes             63
#define Msg_ValidandoPlacas             64
#define Msg_ValidandoGravacao           65
#define Msg_Validandoteste              66
#define MsgFalhaGravacaoFinalPlaca1     67
#define MsgFalhaGravacaoFinalPlaca2     68
#define MsgErro3V3Placa1                69
#define MsgErro3V3Placa2                70
#define MsgTestandoTensoes              71
#define MsgPreparando_Gravacao_Teste    72
#define	MsgRele0Ausente                 100	//		"Placa RELE 0 ausente    ",	// 100
#define	MsgRele1Ausente                 101	//		"Placa RELE 1 ausente    ",	// 101
#define	MsgRele2Ausente                 102	//		"Placa RELE 2 ausente    ",	// 102
#define	MsgRele3Ausente                 103	//		"Placa RELE 3 ausente    ",	// 103
#define	MsgAD0Ausente                   104	//		"Placa A/D 0 ausente     ",	// 104
#define	MsgAD1Ausente                   105	//		"Placa A/D 1 ausente     ",	// 105
#define	MsgAD2Ausente                   106	//		"Placa A/D 2 ausente     ",	// 106
#define	MsgAD3Ausente                   107	//		"Placa A/D 3 ausente     ",	// 107
#define	MsgTelefoniaAusente             108	//		"Placa telefonia ausente ",	// 108
#define	MsgBarramentoAusente            109 //		"Placa barramento ausente",	// 109
#define	MsgDisplayAusente               110	//		"Placa Display ausente   ",	// 110
#define	MsgGravador0Ausente             111	//		"Placa gravador 0 ausente", // 111
#define	MsgGravador1Ausente             112	//		"Placa gravador 1 ausente", // 112
#define	MsgGravador2Ausente             113	//		"Placa gravador 2 ausente", // 113
#define	MsgGravador3Ausente             114	//		"Placa gravador 3 ausente", // 114
#define	MsgGravador4Ausente             115	//		"Placa gravador 4 ausente", // 115
#define	MsgGravador5Ausente             116	//		"Placa gravador 5 ausente", // 116
#define	MsgGravador6Ausente             117	//		"Placa gravador 6 ausente", // 117
#define	MsgGravador7Ausente             118	//		"Placa gravador 7 ausente", // 118
#define	MsgEmTeste                      119			
#define	MsgTesteOK                      120			
#define	MsgTesteErro                    121		
#define	MsgTesteAbortado                122		
#define MsgGravacaoOK1                  123      
#define MsgGravacaoOK2                  124
#define MsgEnterIniciar                 125
#define MsgImportantelinha3             126
#define MsgTempoEsgotado                127
#define MsgRepitaoTeste                 128
#define MsgFavorAguarde                 129
#define MsgPressioneInicio              130
//==================================================================================
//						Referente à Flash
//==================================================================================

#define Memoria_Dados1	0x6000   //Grava 512 MAC's na Flash = 512
#define Memoria_Dados2  0x6400	 //Grava 512 MAC's na Flash = 1024
#define Memoria_Dados3  0x6800	 //Grava 512 MAC's na Flash = 1536
#define Memoria_Dados4  0x6C00	 //Grava 512 MAC's na Flash = 2048
#define Memoria_Dados5  0x7000	 //Grava 512 MAC's na Flash = 2560
#define Memoria_Dados6  0x7400	 //Grava 512 MAC's na Flash = 3072
#define Memoria_Dados7  0x7800	 //Grava 512 MAC's na Flash = 3584
#define Memoria_Dados8  0x7C00	 //Grava 512 MAC's na Flash = 4096

#define Controle_Memoria 0x5C00	 // Variaveis de controle da gravação do MAC

#define TheLastMACFirst     0xFF;
#define TheLastMACSecond    0xFF;
#define TheLastMACThird     0x32;



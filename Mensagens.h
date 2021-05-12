/********************************************************************/
/* Nome do arquivo: Mensagens.h										*/
/* 																	*/
/* Versão:	1.0.0 													*/
/*            Intelbras S/A.										*/
/*                                                           		*/
/* Autor:	Augusto Cezar Medeiros dos Santos						*/
/*                                                                  */
/* Função: Definição das mensagens de erro geradas pela Jiga		*/
/*          		                                             	*/
/********************************************************************/
const __attribute__((space(auto_psv)))
unsigned char MensagensGerais[100][24] =
{
		"                        ",	// 0
		"  Jiga AMT 8000  -      ", // 1
        "    Defeitos Placa 1    ",	// 2
		"Fal Pin FXO_AUDIO_OUT P1",	// 3
		"Fal Pin FXO_AUDIO_IN P1 ",	// 4
		"Falha Pino FXO_RL PCI 1 ",	// 5
		"Falha Pino FXO_CL PCI 1 ",	// 6
		"Falha Pino FXO_DL PCI 1 ",	// 7
		"Falha Pino FXO_DR PCI 1 ",	// 8
		"Falha Pino FXO_RD PCI 1 ",	// 9
		"Timeout do teste Placa1 ",	// 10
		"Falha GPRS Placa 1      ",	// 11
		"Falha WiFi Placa 1      ",	// 12
		"Falha Ethernet Placa 1  ",	// 13
		"Falha Bateria Placa 1   ",	// 14
		"Falha Comunic RF PLaca 1",	// 15
		"Falha EEPROM Placa 1    ",	// 16
		"    Defeitos Placa 2    ",	// 17
		"Fal Pin FXO_AUDIO_OUT P2",	// 18
		"Fal Pin FXO_AUDIO_IN P2 ",	// 19
		"Falha Pino FXO_RL PCI 2 ",	// 20
		"Falha Pino FXO_CL PCI 2 ",	// 21
		"Falha Pino FXO_DL PCI 2 ",	// 22
		"Falha Pino FXO_DR PCI 2 ",	// 23
		"Falha Pino FXO_RD PCI 2 ",	// 24
		"Timeout do teste Placa 2",	// 25
        "Falha GPRS Placa 2      ",	// 26
		"Falha WiFi Placa 2      ",	// 27
		"Falha Ethernet Placa 2  ",	// 28
		"Falha Bateria Placa 2   ",	// 29
		"Falha Comunic RF PLaca 2",	// 30
		"Falha EEPROM Placa      ",	// 31
		" Falha Gravacao Placa 1 ",	// 32
		" Falha Gravacao Placa 2 ",	// 33
		"Timeout Gravacao Placa 1",	// 34
		"Timeout Gravacao Placa 2",	// 35
		"Timeout Prog. Placa     ",	// 36
		"Falha no Apagamento PCI1",	// 37
		"Falha Grav. Memoria PCI1",	// 38
		"Falha Grav. Config PCI 1",	// 39
		"Falha Alim.(VDD) PCI 1  ",	// 40
		"Falha Tens.(VPP) PCI 1  ",	// 41
		" Falha Placa 1 Ausente  ",	// 42
        "Falha no Apagamento PCI2",	// 43
		"Falha Grav. Memoria PCI2",	// 44
		"Falha Grav. Config PCI 2",	// 45
		"Falha Alim.(VDD) PCI 2  ",	// 46
		"Falha Tens.(VPP) PCI 2  ",	// 47
		" Falha Placa 2 Ausente  ",	// 48
		"  Validando pinos IO    ",	// 49
		"Gravando FW de teste ...",	// 50
		"  Gravando FW final ... ",	// 51
		" Inicializando placas...",	// 52
		" Testando tensoes ...   ",	// 53
		"   Validando testes ... ",	// 54
		" Preparando FW Final ...",	// 55
        "    FIM DOS TESTES      ",	// 56
		"  RESULTADO DOS TESTES  ",	// 57
		"   PRESSIONE A CHAVE    ",	// 58
		"   PARA VISUALIZAR OS   ",	// 59
		"DEFEITOS CORRESPONDENTES",	// 60
		"         INICIO         ",	// 61
		"  Bug na gravacao!!!    ",	// 62
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 63
        "BBBBBBBBBBBBBBBBBBBBBBBB", // 64
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 65
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 66
        "BBBBBBBBBBBBBBBBBBBBBBBB", // 67
		"BBBBBBBBBBBBBBBBBBBBBBBB", // 68
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 69
        "BBBBBBBBBBBBBBBBBBBBBBBB", // 70
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 71
        "BBBBBBBBBBBBBBBBBBBBBBBB", // 72
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 73
        "BBBBBBBBBBBBBBBBBBBBBBBB", // 74
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 75
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 76
        "BBBBBBBBBBBBBBBBBBBBBBBB", // 77
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 78
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 79
        "BBBBBBBBBBBBBBBBBBBBBBBB", // 80
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 81
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 82
        "BBBBBBBBBBBBBBBBBBBBBBBB", // 83
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 84
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 85
        "BBBBBBBBBBBBBBBBBBBBBBBB", // 86
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 87
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 88
        "BBBBBBBBBBBBBBBBBBBBBBBB", // 89
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 90
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 91
        "BBBBBBBBBBBBBBBBBBBBBBBB", // 92
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 93
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 94
        "BBBBBBBBBBBBBBBBBBBBBBBB", // 95
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 96
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 97
        "BBBBBBBBBBBBBBBBBBBBBBBB", // 98
		"BBBBBBBBBBBBBBBBBBBBBBBB",	// 99
};

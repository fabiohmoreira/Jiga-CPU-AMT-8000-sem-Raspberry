/****************************************************************************************/
/*	Protocolo :																			*/
/*																						*/
/*	Pergunta :																			*/
/*	tipo de placa + endere�o + num. bytes + comando + dados + cs						*/
/*																						*/
/*	Resposta :																			*/
/*	tipo de placa + endere�o + num. bytes + dados + cs									*/
/*																						*/
/*	Resposta sem conte�do :	(quando o comando recebido n�o tem resposta a ser enviada)	*/
/*	tipo de placa + endere�o															*/
/*																						*/
/****************************************************************************************/
//defini��es dos tipos de placas, comandos e resposta
//
//
//Obs.: Caso alguma placa receba um comando invalido, ela retorna dois byte indicando o tipo da placa, F e o endere�o
//
//	Exemplo : R + F3	Onde 
//							R � o tipo da placa
//							F � a indica��o de erro
//							3 � o endere�o da placa
//
/********************************** Placa display ******************************************
A = Placa conversor AD
	Comandos :
	0xf0 = Teste de comunica��o (N�o executa nenhuma a��o)
		A + Endere�o + N.Bytes + 0xf0 + '\0'
		Retorno = A + Endere�o + N.Bytes=0
	0xf1 = Setup do valor m�dio de tens�o
		A + Endere�o + N.Bytes + 0xf1 + Numero do canal + (valor m�dio MSD) + (valor m�dio LSD) + '\0'
		Retorno = A + Endere�o + N.Bytes=0
	0xf2 = Setup dos canais AD
		A + Endere�o + N.Bytes + 0xf1 + canais + '\0'
			canais 	= 	Bits em 1 = ativado
						Bits em 0 = desativado
		Retorno = A + Endere�o + N.Bytes=0
	0x01 = Ler resultado de medi��o DC em um canal selecionado
		A + Endere�o + N.Bytes + 0xf1 + Numero do canal + '\0'
		Retorno = A + Endere�o + N.Bytes + (Valor MSD) + (Valor LSD) + '\0'
	0x02 = Ler resultado de medi��o de periodo
		A + Endere�o + N.Bytes + 0xf1 + Numero do canal + '\0'
		Retorno = A + Endere�o + N.Bytes + (Valor+ MSD) + (Valor+ LSD) + (Valor- MSD) + (Valor- LSD) + '\0'
*/
/*
B = Placa barramento
	Comandos :
	0xf0 = Teste de comunica��o (N�o executa nenhuma a��o)
		A + Endere�o + N.Bytes + 0xf0 + '\0'
		Retorno = A + Endere�o + N.Bytes=0
*/
/********************************** Placa display ******************************************
D = Placa display
	Comandos :
	0xf0 = Teste de comunica��o (N�o executa nenhuma a��o)
		A + 0 + N.Bytes + 0xf0 + '\0'
		Retorno = A + Endere�o + N.Bytes=0
	0xf1 = Limpar Display
		D + 0 + N.Bytes + 0xf1 + '\0'
		Retorno = D + 0 + N.Bytes=0
	0xf2 = Escrever string na posi��o selecionada
		D + 0 + N.Bytes + 0xf2 + Linha + Coluna + String + '\0'
		Retorno = D + 0 + N.Bytes=0
	0xf3 = Comando
		D + 0 + N.Bytes + 0xf3 + Comando + qtd bips + '\0'
		Comandos :	0x01 = Acionar o BIP de OK
					0x02 = Acionar o BIP de ERRO
					0x03 = Acionar o BIP a cada segundo
					0x04 = Desabilitar o BIP de segundos
					0x05 = Acionar 'n' BIPs curto (inicio de teste/final de teste ???)
		Retorno = D + 0 + N.Bytes=0
	0xf4 = Limpar "buffer" das chaves da placa display
		D + 0 + N.Bytes + 0xf4 + '\0'
		Retorno = D + 0 + N.Bytes=0
	0xf5 = Escrever inteiro  na posi��o selecionada
		D + 0 + N.Bytes + 0xf5 + Linha + Coluna +  (Valor MSD) + (Valor LSD) + Escala + '\0'
		Escala :	1 = 5V
					2 = 20V
		Retorno = D + 0 + N.Bytes=0
	0x01 = Query
		D + 0 + N.Bytes + 0x01 + xx + '\0'
		Retorno :
			D + 0 + N.Bytes + xx + x (chave x foi pressionada, onde x 1 a 6), Dados ou comando
			xx :	0x01 = Chave
					0x02 = Dados
					0x03 = Comando
*********************************************************************************************/
/********************************** Placa reles *********************************************
R = Placa reles
	Comandos :
	0xf0 = Teste de comunica��o (N�o executa nenhuma a��o)
		R + Endere�o + N.Bytes + 0xf0 + '\0'
		Retorno = A + Endere�o + N.Bytes=0
	0xf1 = Desativar todos os reles
		R + Endere�o + N.Bytes + 0xf1 + '\0'
		Retorno = R + Endere�o
	0xf2 = Ligar/Desligar rele selecionado
		R + Endere�o + N.Bytes + 0xf2 + Comando_A +Comando_B + '\0'
		Comando	: 	Os bits do comando_A especifica quais os reles devem ser ligados/desligados
					Os bits do comando_B especifica se deve ligar ou desliga o rele correspondente
					1 = ligar / 0 = desligar
		Retorno = R + Endere�o + N.Bytes=0
	0xf3 = Testa os reles da placa indicada
		R + Endere�o + N.Bytes + 0xf3 + '\0'
		Retorno :
			R + Endere�o + N.Bytes=0
		Obs : Considerar um tempo 500ms para execu��o deste comando
	0x01 = Query	Retorna o resultado do comando teste
		R + Endere�o + N.Bytes + 0x01 + '\0'
		Retorno :	R + Endere�o + N.Bytes + Resultado
					Os bits de 0 a 7 do Resultado, especifica o resultado do teste dos reles
					1 = Ok / 0 = Falha
			
*********************************************************************************************/
/*
G = Placa gravador
	Comandos :
	0xf0 = Teste de comunica��o (N�o executa nenhuma a��o)
		G + Endere�o + N.Bytes + 0xf0 + '\0'
		Retorno = A + Endere�o + N.Bytes=0
*/
/********************************** Placa de telefonia ************************************
T = Placa de telefonia
	Comandos :
	0xf0 = Teste de comunica��o (N�o executa nenhuma a��o)
		T + Endere�o + N.Bytes + 0xf0 + '\0'
		Retorno = A + Endere�o + N.Bytes=0
	0xf1 = Reset da placa
		T + Endere�o + 0xf1 + N.Bytes=0 + '\0'
		Retorno = T + Endere�o
	0xf2 = Inicia Ring + Discagem
		Fun��o -Inicia a gera��o de RING, se a central atender gera os d�gitos 1 e # em DTMF
				e aguarda que a chamada seja desligada
		T + Endere�o + 0xf2 + N.Bytes=0 + '\0'
		Retorno = T + Endere�o


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
	0x03 = Query
		R + Endere�o + 0x02 + N.Bytes + '\0'
		Retorno :	R + Endere�o + Resultado
					Os bits de 0 a 7 do Resultado, especifica o resultado do teste dos reles
					1 = Ok / 0 = Falha
			
*********************************************************************************************/
*/




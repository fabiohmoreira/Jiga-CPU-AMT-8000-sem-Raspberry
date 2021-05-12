/********************************************************************/
/* Nome do arquivo: RotinaTeste.c									*/
/* 																	*/
/* Versão:	1.0.0 													*/
/*            Intelbras S/A.										*/
/*                                                           		*/
/* Autor:	Elder da Fonseca Silvério       						*/
/*                                                                  */
/* Função: Execução da rotina de teste do produto					*/
/*                                                           		*/
/* Versão:	2.0.0 													*/
/*            Intelbras S/A.										*/
/*                                                           		*/
/* Autor:	Fábio Henrique Moreira          						*/
/*                                                                  */
/* Função: Melhorias na rotina de teste e adição do novo gravador   */
/*          		                                             	*/
/********************************************************************/
#include "define.h"
#include "global_vars.h"

////////// Definição dos Reles ///////////

//Placa Relé 0
#define RL_Alimenta_Placa1              0x01    //Alimenta a placa e dá start no FW de teste
#define RL_Comut_Bateria_Placa1         0x02
#define RL_Comut_CargaBateria_Placa1    0x04    //Relé em NF
#define RL_Alimenta_Placa2              0x08    //Alimenta a placa e dá start no FW de teste
#define RL_Comut_Bateria_Placa2         0x10
#define RL_Comut_CargaBateria_Placa2    0x20    //Relé em NF
#define RL_Alimenta_Roteador_Placa1     0x40
#define RL_Alimenta_Roteador_Placa2     0x80

#define RL_Alimenta_Roteadores          0xC0

//Placa Relé 1
#define RL_3V3_Gravacao_Placa1          0x01 //Fio 3V3 do Atmel ICE que grava a placa 1 - Relé em NA
#define RL_StartGrava_Placa1            0x02 //Fio 3V3 do Atmel ICE que grava a placa 2 - Relé em NA
#define RL_Reset_AtmelIce_Placa1        0x04 //Reset no Atmel ICE - Relé em NA
#define RL_CorteUSB_AtmelIce20          0x08 //Corta Alimentação USB do Atmel Ice 20 da placa 1 - Relé em NF
#define RL_Reset_AtmelIce_Placa2        0x10 //Reset no Atmel ICE - Relé em NA
#define RL_CorteUSB_AtmelIce21          0x20 //Corta Alimentação USB do Atmel Ice 20 da placa 2 - Relé em NF
#define RL_3V3_Gravacao_Placa2          0x40 //IO Raspberry de start da gravação da placa 1 - Relé em NA
#define RL_StartGrava_Placa2            0x80 //IO Raspberry de start da gravação da placa 2 - Relé em NA

////////// Definição dos canais de A/D ///////////

//Placa AD 0
#define AD_GPRS_Placa1          0x01 // Modem Audio Out - Pino FXO_AUDIO_OUT - Test Point J20
#define AD_WiFi_Placa1     		0x02 // Modem Audio In - Pino FXO_AUDIO_IN -    J23
#define AD_Ethernet_Placa1      0x03 // Sensor Corte Linha - Pino FXO_CL -      J24
#define AD_Bateria_Placa1       0x04 // Liga Sensor Linha - Pino FXO_DL -       J27
#define AD_RF_Placa1            0x05 // Modem Rele Bypass - Pino FXO_RL -       J22
#define AD_EEPROM_Placa1        0x06 // Detecta Ring - Pino FXO_DR -            J25
#define AD_FimTeste_Placa1      0x07 // Modem Ocupa Linha - Pino FXO_RD -       J28
#define AD_Led3_Placa1          0x08 // Mede Led LD3 no fim do teste    -       J3

//Placa AD 1
#define AD_GPRS_Placa2          0x01 // Modem Audio Out - Pino FXO_AUDIO_OUT - Test Point J20
#define AD_WiFi_Placa2     		0x02 // Modem Audio In - Pino FXO_AUDIO_IN -    J23
#define AD_Ethernet_Placa2      0x03 // Sensor Corte Linha - Pino FXO_CL -      J24
#define AD_Bateria_Placa2       0x04 // Liga Sensor Linha - Pino FXO_DL -       J27
#define AD_RF_Placa2            0x05 // Modem Rele Bypass - Pino FXO_RL -       J22
#define AD_EEPROM_Placa2        0x06 // Detecta Ring - Pino FXO_DR -            J25
#define AD_FimTeste_Placa2      0x07 // Modem Ocupa Linha - Pino FXO_RD -       J28
#define AD_Led3_Placa2          0x08 // Mede Led LD3 no fim do teste    -       J3

//Placa AD 2
#define AD_GravacaoOK_Placa1    0x01 // Sinalização de gravação OK da placa 1 pelo Raspberry
#define AD_GravacaoNOK_Placa1   0x02 // Sinalização de gravação NOK da placa 1 pelo Raspberry
#define AD_Gravando_Placa1      0x03 // Sinalização de gravação em andamento da placa 1 pelo Raspberry
#define AD_GravacaoOK_Placa2    0x04 // Sinalização de gravação OK da placa 2 pelo Raspberry
#define AD_GravacaoNOK_Placa2   0x05 // Sinalização de gravação NOK da placa 2 pelo Raspberry       
#define AD_Gravando_Placa2      0x06 // Sinalização de gravação em andamento da placa 2 pelo Raspberry
//#define AD_      0x07 // Não usado
//#define AD_      0x08 // Não usado

////////////níveis de tensão/////////////////
#define Ref_1V_Escala5V			190		//	1V * 190,7397
#define Ref_1_7_Escala5V        324     //  1,7V * 190,7397
#define Ref_2V_Escala5V			380		//	2V * 190,7397
#define Ref_2_5V_Escala5V		477		//	2,5V * 190,7397
#define Ref_2_7V_Escala5V       515     //  2,7V * 190,7397
#define Ref_3V_Escala5V			572		//	3V * 190,7397
#define Ref_3_5V_Escala5V		667		//	3,5V * 190,7397
#define Ref_4V_Escala5V         762     //  4V * 190,7397
#define Ref_4_5V_Escala5V		858		//	4,5V * 190,7397
#define Ref_4_8V_Escala5V       915     //  4,8V * 190,7397
#define Ref_5_2V_Escala5V		992		//	5,2V * 190,7397
#define Ref_5_5V_Escala5V       1049    //  5,5V * 190,7397

/////////EstagioTeste/////////////
#define Verifica_Gravacao_Final_Placa1      22
#define Verifica_Gravacao_Final_Placa2      23
#define FinalizaTeste                       25

typedef enum {
Inicio = 0,
Setup_FW_Teste,
VerificaFWTesteFinal,        
Executa_Gravacao,
ChecaGravacao,
Valida_Placas,
Estado_Inicial_IO_Placa1,        
Estado_Inicial_IO_Placa2,
Teste_Bateria,
Testes_Placa1,
Testes_Placa2,        
Verifica_Defeitos_Placa1,
Verifica_Defeitos_Placa2,
ValidaParaVersaoFinal,        
GravaVersaoFinal,            
FimTeste, 
ExibeResultado,
Mostra_por_tempo,   
Pressione_Teclas,        
Finaliza_Testes,        
} Pcv_Enum_t;


//***********declaração de variaveis e vetores***************************************************************
unsigned char Placa1[7];
unsigned char Placa2[7];
unsigned char PlacaOk[2];
unsigned char count=0, valor=0, ControleGrav=0;
unsigned int grava, VarErro;
unsigned char GRVerified[1], GRError[1];
unsigned char GravacaoOk[2]; //variável que indica quais testes serão feitos de acordo com os defeitos que podem apresentar durante o teste
unsigned char PosicaoPlaca1;
unsigned char PosicaoPlaca2;
unsigned char DefeitoPlaca1;  //Se =0 -> Não marcou nenhum defeito
unsigned char DefeitoPlaca2;  //Se =1 -> Marcou defeito durante o teste
                              //Se =2 -> Marcou defeito durante a gravação

void MostraResultado (void)
{
    EmiteBipe(5,4);
    SendTextMessage(1, 0, Msg_resultado_dos_testes);
    
	bus_tx_buffer[0]=2;
	bus_tx_buffer[1]=0;
	bus_tx_buffer[2]='P';
	bus_tx_buffer[3]='l';
	bus_tx_buffer[4]='a';
	bus_tx_buffer[5]='c';
	bus_tx_buffer[6]='a';
	bus_tx_buffer[7]=' ';
	bus_tx_buffer[8]='-';
	bus_tx_buffer[9]=' ';
	bus_tx_buffer[10]='1';
	bus_tx_buffer[11]=' ';
	bus_tx_buffer[12]='|';
	bus_tx_buffer[13]=' ';
	bus_tx_buffer[14]='P';
	bus_tx_buffer[15]='l';
	bus_tx_buffer[16]='a';
	bus_tx_buffer[17]='c';
	bus_tx_buffer[18]='a';
	bus_tx_buffer[19]=' ';
	bus_tx_buffer[20]='-';
	bus_tx_buffer[21]=' ';
	bus_tx_buffer[22]='2';
	bus_tx_buffer[23]=' ';
	bus_tx_buffer[24]=' ';
	bus_tx_buffer[25]=' ';
	
	BusSendMessage(PlacaDisplay,D_ShowMessage,26);
	
	bus_tx_buffer[0]=3;
	bus_tx_buffer[1]=0;
	bus_tx_buffer[2]=' ';
	
    if((Placa1[0]==1)&&(Placa1[1]==1)&&(Placa1[2]==1)&&(Placa1[3]==1)&&(Placa1[4]==1)&&(Placa1[5]==1)&&(Placa1[6]==1)&&(GravacaoOk[0] == 1)&&(DefeitoPlaca1 == 0)) //Se todos os testes OK
	{
        bus_tx_buffer[3]='T';
        bus_tx_buffer[4]='E';
		bus_tx_buffer[5]='S';
        bus_tx_buffer[6]='T';
        bus_tx_buffer[7]='E';
        bus_tx_buffer[8]=' ';
        bus_tx_buffer[9]='O'; 
        bus_tx_buffer[10]='K';
        count=0x00;
        PlacaOk[0]|=0x08; //Seta bit para indicação dos resultados nos Leds da jiga
	}
    
	else if ((Placa1[0]==0)||(Placa1[1]==0)||(Placa1[2]==0)||(Placa1[3]==0)||(Placa1[4]==0)||(Placa1[5]==0)||(Placa1[6]==0)||(GRError[0]==0)||(GravacaoOk[0] == 0) || (DefeitoPlaca1 == 2)) //Se algum teste deu Erro
	{
        bus_tx_buffer[3]=' ';
        bus_tx_buffer[4]=' ';
		bus_tx_buffer[5]='E';
        bus_tx_buffer[6]='R';
        bus_tx_buffer[7]='R';
        bus_tx_buffer[8]='O';
        bus_tx_buffer[9]=' '; 
        bus_tx_buffer[10]=' ';
	}

	bus_tx_buffer[11]=' ';
    bus_tx_buffer[12]='|';
    bus_tx_buffer[13]=' ';
    
	if((Placa2[0]==1)&&(Placa2[1]==1)&&(Placa2[2]==1)&&(Placa2[3]==1)&&(Placa2[4]==1)&&(Placa2[5]==1)&&(Placa2[6]==1)&&(GravacaoOk[1] == 1)&&(DefeitoPlaca2 == 0))
	{
        bus_tx_buffer[14]='T';
        bus_tx_buffer[15]='E';
        bus_tx_buffer[16]='S';
		bus_tx_buffer[17]='T';
        bus_tx_buffer[18]='E';
        bus_tx_buffer[19]=' ';
        bus_tx_buffer[20]='O';
        bus_tx_buffer[21]='K';
        count=0x08;
        PlacaOk[0]|=count<<1;
	}
    
	else if ((Placa2[0]==0)||(Placa2[1]==0)||(Placa2[2]==0)||(Placa2[3]==0)||(Placa2[4]==0)||(Placa2[5]==0)||(Placa2[6]==0)||(GRError[1]==0)||(GravacaoOk[1] == 0) || (DefeitoPlaca2 == 2))
	{
        bus_tx_buffer[14]=' ';
        bus_tx_buffer[15]=' ';
        bus_tx_buffer[16]=' ';
		bus_tx_buffer[17]='E';
        bus_tx_buffer[18]='R';
        bus_tx_buffer[19]='R';
        bus_tx_buffer[20]='O';
        bus_tx_buffer[21]=' ';
	}
    
	bus_tx_buffer[22]=' ';
	bus_tx_buffer[23]=' ';
	bus_tx_buffer[24]=' ';
	bus_tx_buffer[25]=' ';
	
	BusSendMessage(PlacaDisplay,D_ShowMessage,26);
	
	bus_tx_buffer[0]=4;
	bus_tx_buffer[1]=0;
	bus_tx_buffer[2]=' ';
	bus_tx_buffer[3]=' ';
	bus_tx_buffer[4]=' ';
	bus_tx_buffer[5]=' ';
	bus_tx_buffer[6]=' ';
	bus_tx_buffer[7]=' ';
	bus_tx_buffer[8]=' ';
	bus_tx_buffer[9]=' ';
	bus_tx_buffer[10]=' ';
	bus_tx_buffer[11]=' ';
	bus_tx_buffer[12]=' ';
	bus_tx_buffer[13]=' ';
	bus_tx_buffer[14]=' ';
	bus_tx_buffer[15]=' ';
	bus_tx_buffer[16]=' ';
	bus_tx_buffer[17]=' ';
	bus_tx_buffer[18]=' ';
	bus_tx_buffer[19]=' ';
	bus_tx_buffer[20]=' ';
	bus_tx_buffer[21]=' ';
	bus_tx_buffer[22]=' ';
	bus_tx_buffer[23]=' ';
	bus_tx_buffer[24]=' ';
	bus_tx_buffer[25]=' ';
	
	BusSendMessage(PlacaDisplay,D_ShowMessage,26);
}

void VerificaGravacao(char Gravador) //verifica a gravação da placa gravador 0 e 1
{
    int MsgIndex;

        GrReadStatus(PlacaGravador_0 + Gravador);
        if (StatusGr[Gravador] == 0x01 || StatusGr[Gravador] == 0x02 || StatusGr[Gravador] == 0x03 || StatusGr[Gravador] == 0xFB)
        {
            if (grava == 0)
            {
                SendTextMessage(2, 0, MsgGravandoFW_Teste); 
            }
                else if (grava == 1)
                {
                   SendTextMessage(2, 0, MsgGravandoFW_Final); 
                }   
                    else
                    {
                        UNUSED(1);/* Nao faz nada, usado para a última tratativa */
                    }
            StatusGr[Gravador] = 0;
            ContadorErro = 0;
        } 

        else if (StatusGr[Gravador]&0xf0)
            {
                MsgIndex = (6 * Gravador);

                if (StatusGr[Gravador] == 0xf1) 
                {
                    PutErrorMessageOnBuffer(MsgErroApagamento + MsgIndex);
                    TemErro = 1;
                }
                else if (StatusGr[Gravador] == 0xf3)
                {
                    PutErrorMessageOnBuffer(MsgErroGrMemoProg + MsgIndex);
                    TemErro = 1;
                }
                else if (StatusGr[Gravador] == 0xf4)
                {
                    PutErrorMessageOnBuffer(MsgErroGrConfig + MsgIndex);
                    TemErro = 1;
                }
                
                else if (StatusGr[Gravador] == 0xf6)
                {
                    PutErrorMessageOnBuffer(MsgFalhaTensaoGrVdd + MsgIndex);
                    TemErro = 1;
                }
                else if (StatusGr[Gravador] == 0xf7)
                {
                    PutErrorMessageOnBuffer(MsgFalhaTensaoGrVpp + MsgIndex);
                    TemErro = 1;
                }
                else if ((StatusGr[Gravador] == 0xf5) && (TestTimeout <= 18))
                {
                    PutErrorMessageOnBuffer(MsgFalhaPlacaAusente + MsgIndex);
                    TemErro = 1;
                }
                else if ((StatusGr[Gravador] == 0xFF) && (ContadorErro>40)) 
                {
                    PutErrorMessageOnBuffer(MsgBugGravacao + MsgIndex);
                    TemErro = 1;
                    
                }
                else if((StatusGr[Gravador] == 0xFF) && (ContadorErro<=40)) 
                {
                    ContadorErro++;
                }
                else
                {
                    UNUSED(1);/* Nao faz nada, usado para a última tratativa */
                } 
                
                if (TemErro)
                {
                    GRVerified[0] |= 1<<Gravador; // Indica que foi verificado

                    GRError[Gravador] |= 1<<Gravador; // Ativa a indicação de problemas
                    GravacaoOk[Gravador] = 0;  //Marca erro de gravação

                    StatusGr[Gravador] = 0;
                    TemErro = 0;
                    ContadorErro = 0;
                }
                
            } 
            else if (StatusGr[Gravador] == 0x04) 
            {
                TestDelay = 500;
                GRVerified[0] |= 1<<Gravador; // Indica que foi verificado
                GravacaoOk[Gravador] = 1;  //Marca gravação OK
                
                SendTextMessage(3, 0, MsgGravacaoOK1+Gravador);

                if(((grava==0)&&(TestTimeout > 20)) || ((grava==1)&&(TestTimeout > 30)))//Evitar dar gravação OK sem ter gravado corretamente ...bug da placa de gravação nova
                {
                    GravacaoOk[Gravador] = 0;  //marca erro na gravação
                    PutErrorMessageOnBuffer(MsgBugGravacao);
                }
                StatusGr[Gravador] = 0;
                ContadorErro =0;
            }
    }

void RotinaDeTeste(void)
{
	static int ValorLido, TestStageTimeout, TempoEmTesteAnt, Porcentagem;
    static char CountTimeOut = 0;
    int count;
	
	if((EmTeste)&&(TestDelay==0)&&(ApoioFlags==0))
	{
		switch(EstagioTeste)
		{
            case Inicio:  // Inicia o vetor com "1" que corresponde a teste OK
                
                SendTextMessage(2, 0, MsgInicializandoPlacas);
                SendTextMessage(3, 0, MsgEmBranco);
                
                Placa1[0]=1; //GPRS
                Placa1[1]=1; //WiFi
                Placa1[2]=1; //Ethernet
                Placa1[3]=1; //Bateria
                Placa1[4]=1; //RF
                Placa1[5]=1; //EEProm
                Placa1[6]=1; //Estado inicial dos IO
                DefeitoPlaca1=0; //Sinaliza ausência de defeito ou defeito no teste ou defeito na gravação
                GRError[0]=1;
                PosicaoPlaca1 = 1;
                                              
                Placa2[0]=1; //GPRS
                Placa2[1]=1; //WiFi
                Placa2[2]=1; //Ethernet
                Placa2[3]=1; //Bateria
                Placa2[4]=1; //RF
                Placa2[5]=1; //EEProm
                Placa2[6]=1; //Estado inicial dos IO
                DefeitoPlaca2=0; //Sinaliza ausência de defeito ou defeito no teste ou defeito na gravação
                GRError[1]=1;
                PosicaoPlaca2 = 1;
                
                AlteraEstadoReles(PlacaRele_1, RL_3V3_Gravacao_Placa1, RL_3V3_Gravacao_Placa1); //Desliga 3V3 da placa de gravação da placa 1
                AlteraEstadoReles(PlacaRele_1, RL_3V3_Gravacao_Placa2, RL_3V3_Gravacao_Placa2); //Desliga 3V3 da placa de gravação da placa 2
                
                GRVerified[0]=0;				// zera indicador de que as placas foram verificadas    
                EstagioTeste = Setup_FW_Teste;
                TimeOutDelay=500;
                               
                break;
                
            case Setup_FW_Teste: //Identifica placas na jiga e Grava firmware de teste
                if (TimeOutDelay == 0)
                {    
                    SetProcessador(PlacaGravador_0, SAM4E);               
                    InitProg(PlacaGravador_0, '1'); // Fw de teste
                
                    SetProcessador(PlacaGravador_1, SAM4E);
                    InitProg(PlacaGravador_1, '1'); // FW de teste

                grava = 0;
                TimeOutDelay = 500;
                EstagioTeste = VerificaFWTesteFinal;
                TestTimeout = 20;
                }
                break;
                
            case VerificaFWTesteFinal: // Verifica o firmware de teste
                if(TimeOutDelay==0)
                { 
                    for(count=0; count<=1; count++) //Verifica as duas placas em paralelo
                    {
                        StatusGr[count] = 0;
                        if(!(GRVerified[0]&(1<< count)))	// se placa ainda não foi verificada
                        {
                            VerificaGravacao(count);	// verifica status da gravação
                        }
                    }
                TestDelay = 1000;  
                EstagioTeste = Executa_Gravacao;
                }
                break;
                
            case Executa_Gravacao:
                               
          		if((GRVerified[0]==0b00000011)||(TestTimeout==0))	// se todas as placas foram verificadas ou ocorreu timeout na gravação
				{
					if(TestTimeout==0)// se ocorreu timeout na gravação
					{
						if(CountTimeOut==0)
						{
							CountTimeOut++;
                            for(count=0;count<64;count++)  //Zero buffer de Erro
                                MsgToShowBuffer[count]=0;
                                MsgToShowPtr_RD=0;
                                MsgToShowPtr_WR=0;
                            for(count=0;count<=19;count++) 
                                bus_fail_counter[count]=0;
                            if(grava == 0)
                            {
                                EstagioTeste=Setup_FW_Teste;
                            }
                            else if (grava == 1)
                            {
                                EstagioTeste=ValidaParaVersaoFinal; //Reinicia gravação
                            }
                                else
                            {
                                UNUSED(1);/* Nao faz nada, usado para a última tratativa do else if */
                            }
							TestDelay=700;
						}
						else
						{
							for(count=0;count<=1;count++)	// varre as placas a procura do timeout da gravação
							{
								if(!(GRVerified[0]&(1<<count)))
                                {
                                    if(count==0)
                                    {
                                        PutErrorMessageOnBuffer(MsgErroTimeoutProg+count); // marca erro somente na placa 1
                                    }
                                    if(count==1)
                                    {
                                       PutErrorMessageOnBuffer(MsgErroTimeoutProg+count); // marca erro somente na placa 2 
                                    }
                                    GravacaoOk[count]=0; //indica que deu erro nessa placa
                                    GRError[count]|=1<<count;
                                }
							}
							if(GRError[count]==0x03)			//se ocorreu erro nas duas placas
							{
                                DefeitoPlaca1 = 2;
                                DefeitoPlaca2 = 2;
                                EstagioTeste = FimTeste;      //Finaliza teste
							}
							else
							{
                                GRVerified[count] = 0;
                                if (!GravacaoOk[0])
                                {
                                    DefeitoPlaca1 = 2; //Marca defeito de gravacão placa 1
                                    GRError[0] = 0;
                                }    
                                if (!GravacaoOk[1])
                                {
                                    DefeitoPlaca2 = 2; //Marca defeito de gravacão placa 2
                                    GRError[1] = 0;
                                }    
                                CountTimeOut=0;
                                
                                if(grava == 0)
                                {
                                    AlteraEstadoReles(PlacaRele_1, RL_3V3_Gravacao_Placa1, 0); //Desliga 3V3 da placa de gravação da placa 1
                                    AlteraEstadoReles(PlacaRele_1, RL_3V3_Gravacao_Placa2, 0); //Desliga 3V3 da placa de gravação da placa 2
                                    EstagioTeste = ChecaGravacao;					// passa para o próximo estágio
                                }
                                else if (grava == 1)
                                {
                                    EstagioTeste = FimTeste;
                                }
                                else
                                {
                                    UNUSED(1);/* Nao faz nada, usado para a última tratativa do else if */
                                }
							}
						}
					}
					else if ((GRError[0]==0x03) ||(GRError[1]==0x03)) 			//se ocorreu erro nas duas placas (1 = NOK)
                    {
                        DefeitoPlaca1 = 2; //Marca defeito de gravacão placa 1
                        DefeitoPlaca2 = 2; //Marca defeito de gravacão placa 2
                        EstagioTeste = FimTeste;      //Finaliza teste
                    }
                    else   //se gravação OK em alguma placa
					{
                        GRVerified[0] = 0;
                        CountTimeOut=0;
                        
                        if (!GravacaoOk[0])
                        {
                            DefeitoPlaca1 = 2; //Marca defeito de gravacão placa 1
                        }
                        if (!GravacaoOk[1])
                        {
                            DefeitoPlaca2 = 2; //Marca defeito de gravacão placa 2
                        }
                        if(grava == 0)
                        {
                            AlteraEstadoReles(PlacaRele_1, RL_3V3_Gravacao_Placa1, 0); //Desliga 3V3 da placa de gravação da placa 1
                            AlteraEstadoReles(PlacaRele_1, RL_3V3_Gravacao_Placa2, 0); //Desliga 3V3 da placa de gravação da placa 2
                            EstagioTeste = ChecaGravacao;					// Passa para o próximo estágio
                        }
                        else if (grava == 1)
                        {
                            EstagioTeste = FimTeste;
                        }
                        else
                        {
                            UNUSED(1);/* Nao faz nada, usado para a última tratativa do else if */
                        }
					}
                    
                    TestDelay = 500;  
				}
                else
                {
                    EstagioTeste = VerificaFWTesteFinal;
                }
                break;
                
            case ChecaGravacao:
                if (GravacaoOk[0]) //Se placa 1 gravou OK
                {
                    AlteraEstadoReles(PlacaRele_0,RL_Alimenta_Placa1, RL_Alimenta_Placa1);		// Alimenta placa 1 em teste
                    AlteraEstadoReles(PlacaRele_0, RL_Comut_CargaBateria_Placa1, RL_Comut_CargaBateria_Placa1);		// Tira a carga da bateria 1 - contato NF 
                }
                else
                {
                   AlteraEstadoReles(PlacaRele_0,RL_Alimenta_Placa1, 0);		// Desliga Alimentação placa 1 em teste  
                }
                
                if (GravacaoOk[1]) //Se placa 2 gravou OK
                {
                    AlteraEstadoReles(PlacaRele_0,RL_Alimenta_Placa2, RL_Alimenta_Placa2);		// Alimenta placa 2 em teste
                    AlteraEstadoReles(PlacaRele_0, RL_Comut_CargaBateria_Placa2, RL_Comut_CargaBateria_Placa2);		// Tira a carga da bateria 2 - contato NF
                }
                else 
                {
                   AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa2, 0);		//Desliga Alimentação placa 2 em teste  
                }    
                
                SendTextMessage(2, 0, MsgEmTeste);
                SendTextMessage(3, 0, MsgTestando_Tensoes);
                AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Roteadores, RL_Alimenta_Roteadores);     //Alimenta roteadores
                EstagioTeste = Valida_Placas;
                TestDelay=1200;
                break;    
               
            case Valida_Placas:         //Verifica se existe placa nas posições de teste da jiga para continuar os testes
                EstagioTeste = ValidaParaVersaoFinal;
                //EstagioTeste = FimTeste;
//                ValorLido=ADReadVoltage(PlacaAD_0, AD_FimTeste_Placa1);
//                if((ValorLido==0xFFFF)||(ValorLido<Ref_3V_Escala5V)||(ValorLido>Ref_4V_Escala5V))
//                {
//                    Placa1[6]=0;
//                    PosicaoPlaca1=0; //Não existe placa na posição 1
//                    AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa1, 0);		// Desalimenta placa 1 em teste
//                }
//                else 
//                {
//                    PosicaoPlaca1=1; //Existe placa na posição 1
//                }
//                
//                ValorLido=ADReadVoltage(PlacaAD_1, AD_FimTeste_Placa2);
//                if((ValorLido==0xFFFF)||(ValorLido<Ref_3V_Escala5V)||(ValorLido>Ref_4V_Escala5V))
//                {
//                    Placa2[6]=0;
//                    GravacaoOk[1]=0; //Não existe placa na posição 2
//                    AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa2, 0);
//                }
//                else
//                {
//                    PosicaoPlaca2=1;
//                }    
//                
//                if((PosicaoPlaca1==0) && (PosicaoPlaca2==0))
//                {
//                    EstagioTeste = FinalizaTeste;
//                }    
//                else
//                {
//                    if(((PosicaoPlaca1==1) && (PosicaoPlaca2==0)) || ((PosicaoPlaca1==0) && (PosicaoPlaca2==1)))
//                    {
//                        for(count=0;count<64;count++)  //Zero buffer de Erro
//                            MsgToShowBuffer[count]=0;
//                            MsgToShowPtr_RD=0;
//                            MsgToShowPtr_WR=0;
//                    }
//                    EstagioTeste = Estado_Inicial_IO_Placa1;
//                }
                break;      
                
            case Estado_Inicial_IO_Placa1:                 //Confere estado inicial dos IO da placa 1 - Nível lógico 1
                 SendTextMessage(3, 0, Msg_ValidaIO);
                 
                if ((GravacaoOk[0]) && (PosicaoPlaca1)) 
                {
                    ValorLido=ADReadVoltage(PlacaAD_0, AD_GPRS_Placa1);
                    if((ValorLido==0xFFFF)||(ValorLido<Ref_3V_Escala5V)||(ValorLido>Ref_4V_Escala5V))
                    {
                        PutErrorMessageOnBuffer(MsgPinoAudioOut_Placa1);
                        Placa1[6]=0;
                        DefeitoPlaca1 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_0, AD_WiFi_Placa1);
                    if((ValorLido==0xFFFF)||(ValorLido<Ref_1_7_Escala5V)||(ValorLido>Ref_4V_Escala5V))
                    {
                        PutErrorMessageOnBuffer(MsgPinoAudioIn_Placa1);
                        Placa1[6]=0;
                        DefeitoPlaca1 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_0, AD_Ethernet_Placa1);
                    if((ValorLido==0xFFFF)||(ValorLido<Ref_3V_Escala5V)||(ValorLido>Ref_4V_Escala5V))
                    {
                        PutErrorMessageOnBuffer(MsgPinoCL_Placa1);
                        Placa1[6]=0;
                        DefeitoPlaca1 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_0, AD_Bateria_Placa1);
                    if((ValorLido==0xFFFF)||(ValorLido<Ref_3V_Escala5V)||(ValorLido>Ref_4V_Escala5V))
                    {
                        PutErrorMessageOnBuffer(MsgPinoDL_Placa1);
                        Placa1[6]=0;
                        DefeitoPlaca1 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_0, AD_RF_Placa1);
                    if((ValorLido==0xFFFF)||(ValorLido<Ref_3V_Escala5V)||(ValorLido>Ref_4V_Escala5V))
                    {
                        PutErrorMessageOnBuffer(MsgPinoRL_Placa1);
                        Placa1[6]=0;
                        DefeitoPlaca1 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_0, AD_EEPROM_Placa1);
                    if((ValorLido==0xFFFF)||(ValorLido<Ref_3V_Escala5V)||(ValorLido>Ref_4V_Escala5V))
                    {
                        PutErrorMessageOnBuffer(MsgPinoDR_Placa1);
                        Placa1[6]=0;
                        DefeitoPlaca1 = 1;
                    }
                }
                EstagioTeste = Estado_Inicial_IO_Placa2;
                break;
                
            case Estado_Inicial_IO_Placa2:                 //Confere estado inicial dos IO da placa 2 - Nível lógico 1
                if ((GravacaoOk[1]) && (PosicaoPlaca2)) //Se placa 2 gravou OK (se existe)
                {
                    ValorLido=ADReadVoltage(PlacaAD_1, AD_GPRS_Placa2);
                    if((ValorLido==0xFFFF)||(ValorLido<Ref_3V_Escala5V)||(ValorLido>Ref_4V_Escala5V))
                    {
                        PutErrorMessageOnBuffer(MsgPinoAudioOut_Placa2);
                        Placa2[6]=0;
                        DefeitoPlaca2 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_1, AD_WiFi_Placa2);
                    if((ValorLido==0xFFFF)||(ValorLido<Ref_1_7_Escala5V)||(ValorLido>Ref_4V_Escala5V))
                    {
                        PutErrorMessageOnBuffer(MsgPinoAudioIn_Placa2);
                        Placa2[6]=0;
                        DefeitoPlaca2 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_1, AD_Ethernet_Placa2);
                    if((ValorLido==0xFFFF)||(ValorLido<Ref_3V_Escala5V)||(ValorLido>Ref_4V_Escala5V))
                    {
                        PutErrorMessageOnBuffer(MsgPinoCL_Placa2);
                        Placa2[6]=0;
                        DefeitoPlaca2 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_1, AD_Bateria_Placa2);
                    if((ValorLido==0xFFFF)||(ValorLido<Ref_3V_Escala5V)||(ValorLido>Ref_4V_Escala5V))
                    {
                        PutErrorMessageOnBuffer(MsgPinoDL_Placa2);
                        Placa2[6]=0;;
                        DefeitoPlaca2 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_1, AD_RF_Placa2);
                    if((ValorLido==0xFFFF)||(ValorLido<Ref_3V_Escala5V)||(ValorLido>Ref_4V_Escala5V))
                    {
                        PutErrorMessageOnBuffer(MsgPinoRL_Placa2);
                        Placa2[6]=0;
                        DefeitoPlaca2 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_1, AD_EEPROM_Placa2);
                    if((ValorLido==0xFFFF)||(ValorLido<Ref_3V_Escala5V)||(ValorLido>Ref_4V_Escala5V))
                    {
                        PutErrorMessageOnBuffer(MsgPinoDR_Placa2);
                        Placa2[6]=0;
                        DefeitoPlaca2 = 1;
                    }
                }
                EstagioTeste = Teste_Bateria;
                TestTimeout=42; 
                break;
                
            case Teste_Bateria:
                if(TestTimeout==25) //10 segundos com bateria conectada e depois desconecta
                {
                    if ((GravacaoOk[0]) && (PosicaoPlaca1))
                    {
                        AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa1, RL_Comut_Bateria_Placa1); // Comuta bateria à fonte que alimenta a placa 1
                    }
                    
                    if ((GravacaoOk[1]) && (PosicaoPlaca2))
                    {
                        AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa2, RL_Comut_Bateria_Placa2); // Comuta bateria à fonte que alimenta a placa 2    
                    }
                }    
                EstagioTeste =  Testes_Placa1;  
                TestDelay=500;
                break;  
                
            case Testes_Placa1:
                if ((GravacaoOk[0]) && (PosicaoPlaca1))
                {   
                    if(TestTimeout < 3)
                    {
                        ValorLido=ADReadVoltage(PlacaAD_0, AD_FimTeste_Placa1);
                        if(ValorLido < Ref_1V_Escala5V)
                        {
                            AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa1, 0); // Tira a bateria da fonte que alimenta a placa 1; 
                        }
                        else if(!TestTimeout)
                        {
                            AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa1, 0); // Tira a bateria da fonte que alimenta a placa 1
                            PutErrorMessageOnBuffer(MsgTimeoutTeste_Placa1);
                            DefeitoPlaca1 = 1;
                        }
                    }
                }
                EstagioTeste = Testes_Placa2;
                TestDelay=500;
                break; 
                
            case Testes_Placa2:
                if ((GravacaoOk[1]) && (PosicaoPlaca2))
                {
                    if(TestTimeout < 3)
                    {
                        ValorLido=ADReadVoltage(PlacaAD_1, AD_FimTeste_Placa2);
                        if(ValorLido < Ref_1V_Escala5V)
                        {
                            AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa2, 0); // Tira a bateria da fonte que alimenta a placa 2
                            EstagioTeste = Verifica_Defeitos_Placa1; 
                        }
                        else if(!TestTimeout)
                        {
                            AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa2, 0); // Tira a bateria da fonte que alimenta a placa 2
                            PutErrorMessageOnBuffer(MsgTimeoutTeste_Placa2);
                            EstagioTeste = Verifica_Defeitos_Placa1; 
                            DefeitoPlaca2 = 1;
                        }
                    }
                }
                TestDelay=500;
                break; 
                
            case Verifica_Defeitos_Placa1:        //Verifica defeitos nos testes da placa 1
                 SendTextMessage(3, 0, MsgValidandotestes);
                 
                if ((GravacaoOk[0]) && (PosicaoPlaca1)) 
                {
                    ValorLido=ADReadVoltage(PlacaAD_0, AD_GPRS_Placa1);
                    if(ValorLido>Ref_1V_Escala5V)
                    {
                        PutErrorMessageOnBuffer(MsgFalhaGPRS_Placa1);
                        Placa1[0]=0; //Defeito GPRS
                        DefeitoPlaca1 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_0, AD_WiFi_Placa1);
                    if(ValorLido>Ref_1_7_Escala5V)
                    {
                        PutErrorMessageOnBuffer(MsgFalhaWiFi_Placa1);
                        Placa1[1]=0; //Defeito WiFi
                        DefeitoPlaca1 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_0, AD_Ethernet_Placa1);
                    if(ValorLido>Ref_1V_Escala5V)
                    {
                        PutErrorMessageOnBuffer(MsgFalhaEthernet_Placa1);
                        Placa1[2]=0; //Defeito Ethernet
                        DefeitoPlaca1 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_0, AD_Bateria_Placa1);
                    if(ValorLido>Ref_1V_Escala5V)
                    {
                        PutErrorMessageOnBuffer(MsgFalhaBateria_Placa1);
                        Placa1[3]=0; //Defeito Bateria
                        DefeitoPlaca1 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_0, AD_RF_Placa1);
                    if(ValorLido>Ref_1V_Escala5V)
                    {
                        PutErrorMessageOnBuffer(MsgFalhaRF_Placa1);
                        Placa1[4]=0; //Defeito RF
                        DefeitoPlaca1 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_0, AD_EEPROM_Placa1);
                    if(ValorLido>Ref_1V_Escala5V)
                    {
                        PutErrorMessageOnBuffer(MsgFalhaEEPROM_Placa1);
                        Placa1[5]=0; //Defeito EEProm
                        DefeitoPlaca1 = 1;
                    }
                }
                TestTimeout = 0;
                EstagioTeste = Verifica_Defeitos_Placa2;                
                break;
                
            case Verifica_Defeitos_Placa2:         //Verifica defeitos nos testes da placa 2
                if ((GravacaoOk[1]) && (PosicaoPlaca2)) 
                {
                    ValorLido=ADReadVoltage(PlacaAD_1, AD_GPRS_Placa2);
                    if(ValorLido>Ref_1V_Escala5V)
                    {
                        PutErrorMessageOnBuffer(MsgFalhaGPRS_Placa2);
                        Placa2[0]=0; //Defeito GPRS
                        DefeitoPlaca2 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_1, AD_WiFi_Placa2);
                    if(ValorLido>Ref_1_7_Escala5V)
                    {
                        PutErrorMessageOnBuffer(MsgFalhaWiFi_Placa2);
                        Placa2[1]=0; //Defeito WiFi
                        DefeitoPlaca2 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_1, AD_Ethernet_Placa2);
                    if(ValorLido>Ref_1V_Escala5V)
                    {
                        PutErrorMessageOnBuffer(MsgFalhaEthernet_Placa2);
                        Placa2[2]=0; //Defeito Ethernet
                        DefeitoPlaca2 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_1, AD_Bateria_Placa2);
                    if(ValorLido>Ref_1V_Escala5V)
                    {
                        PutErrorMessageOnBuffer(MsgFalhaBateria_Placa2);
                        Placa2[3]=0; //Defeito Bateria;
                        DefeitoPlaca2 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_1, AD_RF_Placa2);
                    if(ValorLido>Ref_2V_Escala5V)
                    {
                        PutErrorMessageOnBuffer(MsgFalhaRF_Placa2);
                        Placa2[4]=0; //Defeito RF
                        DefeitoPlaca2 = 1;
                    }
                    
                    ValorLido=ADReadVoltage(PlacaAD_1, AD_EEPROM_Placa2);
                    if(ValorLido>Ref_1V_Escala5V)
                    {
                        PutErrorMessageOnBuffer(MsgFalhaEEPROM_Placa2);
                        Placa2[5]=0; //Defeito EEProm
                        DefeitoPlaca2 = 1;
                    }
                }  

                AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Roteadores, 0);         
                TestDelay=200;
                EstagioTeste = ValidaParaVersaoFinal;
                break;
                
                case ValidaParaVersaoFinal:
                     SendTextMessage(3, 0, MsgPreparando_Gravacao_Final);
                    if(DefeitoPlaca1 == 0)
                    {
                        AlteraEstadoReles(PlacaRele_1, RL_3V3_Gravacao_Placa1, RL_3V3_Gravacao_Placa1); //Desliga 3V3 da placa de gravação da placa 1
                    }    
                    if(DefeitoPlaca2 == 0)
                    {
                        AlteraEstadoReles(PlacaRele_1, RL_3V3_Gravacao_Placa2, RL_3V3_Gravacao_Placa2); //Desliga 3V3 da placa de gravação da placa 2
                    }
                    TestDelay = 500;
                    EstagioTeste = GravaVersaoFinal; 

                if (((DefeitoPlaca1 == 1) || (DefeitoPlaca1 == 2)) && ((DefeitoPlaca2 == 1) || (DefeitoPlaca2 == 2))) //Se deu defeito no testes das duas placas 
                {
                    EstagioTeste = FimTeste; //Finaliza Teste 
                }
                break;
                
            case GravaVersaoFinal: //Grava firmware final
                SendTextMessage(3, 0, MsgEmBranco);
                grava = 1;  //Sinaliza gravação do FW versão final de produto
                
                if((PosicaoPlaca1 == 0) || ((DefeitoPlaca1 == 1) || (DefeitoPlaca1 == 2)))          //para não iniciar gravação na posição que não possuir placa
                {    
                    GRVerified[0] = 0x01;       //Condição para não travar durante a verificação, caso não tenha placa
                }    
                if ((PosicaoPlaca2 == 0) || ((DefeitoPlaca2 == 1) || (DefeitoPlaca2 == 2)))
                {
                    GRVerified[0] = 0x02;
                }
                if ((GRVerified[0] & 0x01) == 0) //&& (DefeitoPlaca1 == 0) && (PosicaoPlaca1 == 1)) //Condição em que a gravação ainda não foi verificada, no caso de regravação
                {
                    SetProcessador(PlacaGravador_0, SAM4E);
                    InitProg(PlacaGravador_0, '2'); // placa gravação 0 
                    GravacaoOk[0] = 0;
                }
                if ((GRVerified[0] & 0x02) == 0)// && (DefeitoPlaca2 == 0)&& (PosicaoPlaca2 == 1))
                {
                    SetProcessador(PlacaGravador_1, SAM4E);
                    InitProg(PlacaGravador_1, '2'); // placa gravação 1 
                    GravacaoOk[1] = 0;
                }
                
                TimeOutDelay = 1000;
                EstagioTeste = VerificaFWTesteFinal;
                TestTimeout = 30; 
                break;
                
/*######################################***Resultado dos Testes***####################################################*/        
            case FimTeste:
                TestTimeout = 0;
                AlteraEstadoReles(PlacaRele_0, RL_Comut_CargaBateria_Placa1, 0);		//Fecha carga na bateria1
                AlteraEstadoReles(PlacaRele_0, RL_Comut_CargaBateria_Placa2, 0);		//Fecha carga na bateria2
                AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa1, 0);
                AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa2, 0);
                AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Roteadores, 0);
                DesligaReles(PlacaRele_1);
                TestDelay = 300;
                TimeoutFimTeste = 45000; //Seta para mostrar o resultado do teste somente por 60 seg. no display após o teste terminar
                EstagioTeste = ExibeResultado;					
			break;
            
			case ExibeResultado: //Exibe resultado do teste para as duas placas
                if(TestTimeout == 0)
                {
                    LimpaDisplay();
                    PlacaOk[0]=0;
                    MostraResultado();
                    EstagioTeste = Mostra_por_tempo;
                }
                
                valor = EstadoTeclas();  //Aguarda tecla Inicio para mostrar os defeitos no display
                if((valor & 0x01)==0)
                {
                    Delay_ms(400);
                    EstagioTeste = Finaliza_Testes; //Finaliza o teste para mostrar os defeitos no display
                    TimeoutFimTeste = 45000; //Seta para mostrar o resultado do teste somente por 60 seg. no display após o teste terminar
                }
         	break;
            
			case Mostra_por_tempo:			
                TestTimeout = 8; //Mostra o Resultado por 8 segundos	
                EstagioTeste = Pressione_Teclas;
            break;
            
			case Pressione_Teclas:
                if(TestTimeout == 0)
                {
                    if(MsgToShowPtr_WR!=0)
                    {
                        LimpaDisplay();
                        SendTextMessage(1, 0,Msg_pressione_chave);
                        SendTextMessage(2, 0,Msg_chave_inicio);
                        SendTextMessage(3, 0,Msg_para_visualizar);	
                        SendTextMessage(4, 0,Msg_os_defeitos_correspondentes);
                        EstagioTeste = ExibeResultado;
                        TestTimeout = 4; //Escreve mensagens por 4 segundos
                    }
                }
                
                valor = EstadoTeclas();  //Aguarda tecla Inicio para mostrar os defeitos no display
                if((valor & 0x01)==0)
                {
                    Delay_ms(400);
                    EstagioTeste = Finaliza_Testes;
                    TimeoutFimTeste = 45000; //Para mostrar o resultado do teste somente por 60 seg. no display após o teste terminar
                    LimpaDisplay();
                }
			break;
            
			case Finaliza_Testes:	
                EmTeste=0;
                FinalizaTesteFlag=1;
                IniciaTesteFlag=0;
                
                if ((DefeitoPlaca1 == 0)&&(PosicaoPlaca1))
                {
                    Counter++; //Incrementa 1 se teste OK
                }
                else
                {
                    Counter_Nok++; //Incrementa 1 se teste Não OK
                }
                
                if ((DefeitoPlaca2 == 0)&&(PosicaoPlaca2))
                {
                    Counter++; //Incrementa 1 se teste OK
                }
                else
                {
                    Counter_Nok++; //Incrementa 1 se teste Não OK
                }
                
                if(MsgToShowPtr_WR==0)
                {
                    TesteOK=1;
                }    
			break;   
    }
}        

    if ((EmTeste)&&(TempoEmTeste != TempoEmTesteAnt)&&((EstagioTeste < FimTeste))) 
    {
        for (count = 20; count < 26; count++)
            bus_tx_buffer[count] = 0;

        bus_tx_buffer[0] = 4; // Linha 4
        bus_tx_buffer[1] = 3; // Coluna 3

        bus_tx_buffer[2] = ' ';
        bus_tx_buffer[3] = (TestTimeout / 10) + 48;//'-';
        bus_tx_buffer[4] = (TestTimeout % 10) + 48;//' ';

        bus_tx_buffer[5] = ' ';
        bus_tx_buffer[6] = '|';
        bus_tx_buffer[7] = ' ';

        bus_tx_buffer[8] = ((TempoEmTeste / 2) / 100) + 48;
        bus_tx_buffer[9] = (((TempoEmTeste / 2) % 100) / 10) + 48;
        bus_tx_buffer[10] = (((TempoEmTeste / 2) % 100) % 10) + 48;
        bus_tx_buffer[11] = ' ';
        bus_tx_buffer[12] = 's';
        bus_tx_buffer[13] = 'e';
        bus_tx_buffer[14] = 'g';

        bus_tx_buffer[15] = ' ';
        bus_tx_buffer[16] = '|';
        bus_tx_buffer[17] = ' ';

        bus_tx_buffer[18] = (EstagioTeste / 10) + 48;
        bus_tx_buffer[19] = (EstagioTeste % 10) + 48;

        BusSendMessage(PlacaDisplay, D_ShowMessage, 26);

        TempoEmTesteAnt = TempoEmTeste;
    }
}





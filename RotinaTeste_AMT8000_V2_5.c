/********************************************************************/
/* Nome do arquivo: RotinaTeste.c									*/
/* 																	*/
/* Versão:	5.0.0 													*/
/*            Intelbras S/A.										*/
/*                                                           		*/
/* Autor:	Fábio Henrique Moreira          						*/
/*                                                                  */
/* Função: Melhorias na rotina de teste e adição do novo gravador   */
/* Função: Melhorias na verificação do gravador e ping direto       */
/*          		                                             	*/
/********************************************************************/
#include "define.h"
#include "global_vars.h"

////////// Definição dos Reles ///////////

//Placa Relé 0
#define RL_Alimenta_Placa1              0x01    
#define RL_Comut_Bateria_Placa1         0x02
#define RL_Comut_CargaBateria_Placa1    0x04 //Relé em NF
#define RL_Alimenta_Placa2              0x08    
#define RL_Comut_Bateria_Placa2         0x10
#define RL_Comut_CargaBateria_Placa2    0x20 //Relé em NF
//#define RL_Aciona_Gravadores            0x40 //Relé em NF

//Placa Relé 1
#define RL_VDD_Placa1                   0x01 
#define RL_MCLR_Placa1                  0x02
#define RL_Clock_Placa1                 0x04
#define RL_Dados_Placa1                 0x08
#define RL_VDD_Placa2                   0x10 
#define RL_MCLR_Placa2                  0x20
#define RL_Clock_Placa2                 0x40
#define RL_Dados_Placa2                 0x80

#define RL_Grava_Placa1                 0x0F
#define RL_Grava_Placa2                 0xF0


////////// Definição dos canais de A/D ///////////
//Placa AD 0
#define AD_GPRS_Placa1          0x01 // J20 da placa na posição 1
#define AD_WiFi_Placa1     		0x02 // J23 da placa na posição 1
#define AD_Ethernet_Placa1      0x03 // J24 da placa na posição 1
#define AD_Bateria_Placa1       0x04 // J27 da placa na posição 1
#define AD_RF_Placa1            0x05 // J22 da placa na posição 1
#define AD_EEPROM_Placa1        0x06 // J25 da placa na posição 1
#define AD_FimTeste_Placa1      0x07 // J28 da placa na posição 1
#define AD_3V3_Placa1           0x08 // J3 da placa na posição 1

//Placa AD 1
#define AD_GPRS_Placa2          0x01 // J20 da placa na posição 2
#define AD_WiFi_Placa2     		0x02 // J23 da placa na posição 2
#define AD_Ethernet_Placa2      0x03 // J24 da placa na posição 2
#define AD_Bateria_Placa2       0x04 // J27 da placa na posição 2
#define AD_RF_Placa2            0x05 // J22 da placa na posição 2
#define AD_EEPROM_Placa2        0x06 // J25 da placa na posição 2
#define AD_FimTeste_Placa2      0x07 // J28 da placa na posição 2
#define AD_3V3_Placa2           0x08 // J3 da placa na posição 2

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

typedef enum {
    Inicio = 0,
    Alimenta_Placas, //1
    Teste3V3, //2
    Valida_Placa1, //3
    Valida_Placa2, //4
    ReligaTeste, //5
    Teste_Bateria, //6
    Testes_Placa1, //7
    Testes_Placa2, //8
    Verifica_Defeitos_Placa1,//9
    Verifica_Defeitos_Placa2,//10
    SetupGravaTeste,//11
    ValidaParaVersaoFinal, //12
    VerificaFWTesteFinal, //13
    Executa_Gravacao, //14
    FimTeste, //15
    ExibeResultado,
    ExibeResultadoportempo,
    MostraResults,
    Mostra_por_tempo,
    Pressione_Teclas,
    Finaliza_Testes,
} Pcv_Enum_t;


//***********declaração de variaveis e vetores***************************************************************
unsigned int Placa1[9], Placa2[9], grava, VarErro;
unsigned char GRVerified[1], GRError[2], GravacaoOk[2], PlacaOk[2], count = 0, valor = 0, Check;
unsigned char SinalizaErroPlaca1, SinalizaErroPlaca2, DefeitoPlaca1, DefeitoPlaca2, PosicaoPlaca1, PosicaoPlaca2;

void MostraResultado(void) {

    SendTextMessage(1, 0, Msg_resultado_dos_testes);

    bus_tx_buffer[0] = 2;
    bus_tx_buffer[1] = 0;
    bus_tx_buffer[2] = ' ';
    bus_tx_buffer[3] = 'P';
    bus_tx_buffer[4] = 'l';
    bus_tx_buffer[5] = 'a';
    bus_tx_buffer[6] = 'c';
    bus_tx_buffer[7] = 'a';
    bus_tx_buffer[8] = ' ';
    bus_tx_buffer[9] = '-';
    bus_tx_buffer[10] = ' ';
    bus_tx_buffer[11] = '1';
    bus_tx_buffer[12] = ' ';
    bus_tx_buffer[13] = '|';
    bus_tx_buffer[14] = ' ';
    bus_tx_buffer[15] = 'P';
    bus_tx_buffer[16] = 'l';
    bus_tx_buffer[17] = 'a';
    bus_tx_buffer[18] = 'c';
    bus_tx_buffer[19] = 'a';
    bus_tx_buffer[20] = ' ';
    bus_tx_buffer[21] = '-';
    bus_tx_buffer[22] = ' ';
    bus_tx_buffer[23] = '2';
    bus_tx_buffer[24] = ' ';
    bus_tx_buffer[25] = ' ';

    BusSendMessage(PlacaDisplay, D_ShowMessage, 26);

    bus_tx_buffer[0] = 3;
    bus_tx_buffer[1] = 0;
    bus_tx_buffer[2] = ' ';
    bus_tx_buffer[3] = ' ';

    if ((Placa1[0]==1)&&(Placa1[1]==1)&&(Placa1[2]==1)&&(Placa1[3]==1)&&(Placa1[4]==1)&&(Placa1[5]==1)&&(Placa1[6]==1)&&(GRError[0]==1)&&(Placa1[7]==1)&&(GravacaoOk[0]==1)) //Se todos os testes OK
    {
        bus_tx_buffer[4] = 'T';
        bus_tx_buffer[5] = 'E';
        bus_tx_buffer[6] = 'S';
        bus_tx_buffer[7] = 'T';
        bus_tx_buffer[8] = 'E';
        bus_tx_buffer[9] = ' ';
        bus_tx_buffer[10] = 'O';
        bus_tx_buffer[11] = 'K';
        count = 0x00;
        PlacaOk[0] |= 0x08; //Seta bit para indicação dos resultados nos Leds da jiga) 
    } else if ((Placa1[0]==0)||(Placa1[1]==0)||(Placa1[2]==0)||(Placa1[3]==0)||(Placa1[4]==0)||(Placa1[5]==0)||(Placa1[6]==0)||(GRError[0]==0)||(Placa1[7]==0)||(GravacaoOk[0]==0)) {
        bus_tx_buffer[4] = ' ';
        bus_tx_buffer[5] = ' ';
        bus_tx_buffer[6] = 'E';
        bus_tx_buffer[7] = 'R';
        bus_tx_buffer[8] = 'R';
        bus_tx_buffer[9] = 'O';
        bus_tx_buffer[10] = ' ';
        bus_tx_buffer[11] = ' ';
    }

    bus_tx_buffer[12] = ' ';
    bus_tx_buffer[13] = '|';
    bus_tx_buffer[14] = ' ';

    if ((Placa2[0]==1)&&(Placa2[1]==1)&&(Placa2[2]==1)&&(Placa2[3]==1)&&(Placa2[4]==1)&&(Placa2[5]==1)&&(Placa2[6]==1)&&(GRError[1]==1)&&(Placa2[7]==1)&&(GravacaoOk[1]==1)) {
        bus_tx_buffer[15] = 'T';
        bus_tx_buffer[16] = 'E';
        bus_tx_buffer[17] = 'S';
        bus_tx_buffer[18] = 'T';
        bus_tx_buffer[19] = 'E';
        bus_tx_buffer[20] = ' ';
        bus_tx_buffer[21] = 'O';
        bus_tx_buffer[22] = 'K';
        count = 0x08;
        PlacaOk[0] |= count << 1;
    } else if ((Placa2[0]==0)||(Placa2[1]==0)||(Placa2[2]==0)||(Placa2[3]==0)||(Placa2[4]==0)||(Placa2[5]==0)||(Placa2[6]==0)||(GRError[1]==0)||(Placa2[7]==0)||(GravacaoOk[1]==0)) {
        bus_tx_buffer[15] = ' ';
        bus_tx_buffer[16] = ' ';
        bus_tx_buffer[17] = 'E';
        bus_tx_buffer[18] = 'R';
        bus_tx_buffer[19] = 'R';
        bus_tx_buffer[20] = 'O';
        bus_tx_buffer[21] = ' ';
        bus_tx_buffer[22] = ' ';
    }


    bus_tx_buffer[23] = ' ';
    bus_tx_buffer[24] = ' ';
    bus_tx_buffer[25] = ' ';

    BusSendMessage(PlacaDisplay, D_ShowMessage, 26);

    bus_tx_buffer[0] = 4;
    bus_tx_buffer[1] = 0;
    bus_tx_buffer[2] = ' ';
    bus_tx_buffer[3] = ' ';
    bus_tx_buffer[4] = ' ';
    bus_tx_buffer[5] = ' ';
    bus_tx_buffer[6] = ' ';
    bus_tx_buffer[7] = ' ';
    bus_tx_buffer[8] = ' ';
    bus_tx_buffer[9] = ' ';
    bus_tx_buffer[10] = ' ';
    bus_tx_buffer[11] = ' ';
    bus_tx_buffer[12] = ' ';
    bus_tx_buffer[13] = ' ';
    bus_tx_buffer[14] = ' ';
    bus_tx_buffer[15] = ' ';
    bus_tx_buffer[16] = ' ';
    bus_tx_buffer[17] = ' ';
    bus_tx_buffer[18] = ' ';
    bus_tx_buffer[19] = ' ';
    bus_tx_buffer[20] = ' ';
    bus_tx_buffer[21] = ' ';
    bus_tx_buffer[22] = ' ';
    bus_tx_buffer[23] = ' ';
    bus_tx_buffer[24] = ' ';
    bus_tx_buffer[25] = ' ';

    BusSendMessage(PlacaDisplay, D_ShowMessage, 26);
}

void VerificaGravacao(char Gravador) //verifica a gravação da placa gravador 0 e 1
{
    int MsgIndex;
    GrReadStatus(PlacaGravador_0 + Gravador);
    if (StatusGr[Gravador] == 0x01 || StatusGr[Gravador] == 0x02 || StatusGr[Gravador] == 0x03 || StatusGr[Gravador] == 0xFB) {
        SendTextMessage(2, 0, MsgGravandoFW_Final);
        SendTextMessage(3, 0, MsgFavorAguarde);
    } else if (StatusGr[Gravador]&0xf0) {
        MsgIndex = (6 * Gravador);

        if (StatusGr[Gravador] == 0xf1) {
            PutErrorMessageOnBuffer(MsgErroApagamento + MsgIndex);
            TemErro = 1;
        } else if (StatusGr[Gravador] == 0xf3) {
            PutErrorMessageOnBuffer(MsgErroGrMemoProg + MsgIndex);
            TemErro = 1;
        } else if (StatusGr[Gravador] == 0xf4) {
            PutErrorMessageOnBuffer(MsgErroGrConfig + MsgIndex);
            TemErro = 1;
        } else if (StatusGr[Gravador] == 0xf6) {
            PutErrorMessageOnBuffer(MsgFalhaTensaoGrVdd + MsgIndex);
            TemErro = 1;
        } else if (StatusGr[Gravador] == 0xf7) {
            PutErrorMessageOnBuffer(MsgFalhaTensaoGrVpp + MsgIndex);
            TemErro = 1;
        } else if ((StatusGr[Gravador] == 0xf5) && (TestTimeout <= 18)) {
            PutErrorMessageOnBuffer(MsgFalhaPlacaAusente + MsgIndex);
            TemErro = 1;
        } else {
            UNUSED(1); /* Nao faz nada, usado para a última tratativa */
        }

        if (TemErro == 1) {
            GRVerified[0] |= 1 << Gravador; // Indica que foi verificado

            GRError[Gravador] |= 1 << Gravador; // Ativa a indicação de problemas
            GravacaoOk[Gravador] = 0; //Marca erro de gravação

            StatusGr[Gravador] = 0;
            TemErro = 0;
            ContadorErro = 0;
        }

    } else if (StatusGr[Gravador] == 0x04) {
        TestDelay = 500;
        GRVerified[0] |= 1 << Gravador; // Indica que foi verificado
        GravacaoOk[Gravador] = 1; //Marca gravação OK
        
        if (TestTimeout < 10) {
        SendTextMessage(3, 0, MsgGravacaoOK1 + Gravador);
        }

        if (((Check == 0)&&(TestTimeout > 20)) || ((Check == 1)&&(TestTimeout > 30)))//Evitar dar gravação OK sem ter gravado corretamente ...bug da placa de gravação nova
        {
            GravacaoOk[Gravador] = 0; //marca erro na gravação
            PutErrorMessageOnBuffer(MsgBugGravacao);
        }
        StatusGr[Gravador] = 0x00;
    } else {
        UNUSED(1);
    }
}

//    } else if (StatusGr[Gravador] == 0x04) {
//        TestDelay = 500;
//        GRVerified[0] |= 1 << Gravador; // Indica que foi verificado
//        GravacaoOk[Gravador] = 1; //Marca gravação OK
//        
//        if ((PosicaoPlaca1 == 1)&&(TestTimeout <10)&&(StatusGr[0] == 0x04)){
//        SendTextMessage(2, 0, MsgGravacaoOK1);
//        GravacaoOk[0] = 1; //Marca gravação OK
//        }
//        
//        if ((PosicaoPlaca2 == 1)&&(TestTimeout <10)&&(StatusGr[1] == 0x04)){
//        SendTextMessage(3, 0, MsgGravacaoOK2);
//        GravacaoOk[1] = 1; //Marca gravação OK
//        }
//        StatusGr[Gravador] = 0x00;
//    }
//    TestDelay = 200;
//}

void RotinaDeTeste(void) {
    static int ValorLido, TempoEmTesteAnt;
    static char CountTimeOut = 0;

    if ((EmTeste)&&(TestDelay == 0)&&(ApoioFlags == 0)) {
        switch (EstagioTeste) {
            case Inicio: 
                ExibeContador(); 
                Placa1[0] = 0; //GPRS pino 
                Placa1[1] = 0; //WiFi
                Placa1[2] = 0; //Ethernet
                Placa1[3] = 0; //Bateria
                Placa1[4] = 0; //RF
                Placa1[5] = 0; //EEProm
                Placa1[6] = 0; //Estado inicial dos IO
                Placa1[7] = 0; //Teste 3V3
                PosicaoPlaca1 = 0;
                SinalizaErroPlaca1 = 0;
                GRError[0] = 1;
                DefeitoPlaca1 = 0;

                Placa2[0] = 0; //GPRS
                Placa2[1] = 0; //WiFi
                Placa2[2] = 0; //Ethernet
                Placa2[3] = 0; //Bateria
                Placa2[4] = 0; //RF
                Placa2[5] = 0; //EEProm
                Placa2[6] = 0; //Estado inicial dos IO
                Placa2[7] = 0; //Teste 3V3
                SinalizaErroPlaca2 = 0;
                GRError[1] = 1;
                PosicaoPlaca2 = 0;
                DefeitoPlaca2 = 0;
                
                EstagioTeste = Alimenta_Placas;
                StatusGrava = 0;
                TimeOutDelay = 10;
                TestTimeout = 0;
                break;

            case Alimenta_Placas:
                if (TimeOutDelay == 0) {
                    AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa1, RL_Alimenta_Placa1); // Alimenta placa 1 em teste
                    AlteraEstadoReles(PlacaRele_0, RL_Comut_CargaBateria_Placa1, RL_Comut_CargaBateria_Placa1); // Tira a carga da bateria 1 - contato NF

                    AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa2, RL_Alimenta_Placa2); // Alimenta placa 2 em teste
                    AlteraEstadoReles(PlacaRele_0, RL_Comut_CargaBateria_Placa2, RL_Comut_CargaBateria_Placa2); // Tira a carga da bateria 2 - contato NF

                    SendTextMessage(2, 0, MsgEmTeste);
                    SendTextMessage(3, 0, Msg_Validandoteste);

                    TimeOutDelay = 500;
                    EstagioTeste = Teste3V3;
                }
                break;
                
            case Teste3V3:
                if (TimeOutDelay == 0) {
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_3V3_Placa1);
                    if ((ValorLido != 0xFFFF) && (ValorLido > Ref_3V_Escala5V) && (ValorLido < Ref_3_5V_Escala5V)) {
                        Placa1[7] = 1;
                        PosicaoPlaca1 = 1;
                    } else {
                        AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa1, 0); // Desalimenta placa 1 em teste
                        Placa1[7] = 0;
                        PutErrorMessageOnBuffer(MsgErro3V3Placa1);
                        PosicaoPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                    }

                    ValorLido = ADReadVoltage(PlacaAD_1, AD_3V3_Placa2);
                    if ((ValorLido != 0xFFFF) && (ValorLido > Ref_3V_Escala5V) && (ValorLido < Ref_3_5V_Escala5V)) {
                        Placa2[7] = 1;
                        PosicaoPlaca2 = 1;
                    } else {
                        AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa2, 0); // Desalimenta placa 1 em teste
                        Placa2[7] = 0;
                        PutErrorMessageOnBuffer(MsgErro3V3Placa2);
                        PosicaoPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    }

                    if ((Placa1[7] == 1)&&(Placa2[7] == 1)) {
                        EstagioTeste = Valida_Placa1;
                        SendTextMessage(3, 0, Msg_Validandoteste);
                        TimeOutDelay = 100;
                        break;
                    } else if ((Placa1[7] == 0)&&(Placa2[7] == 0)) {
                        EstagioTeste = FimTeste;
                        break;
                    } else {
                        EstagioTeste = Valida_Placa1;
                        SendTextMessage(3, 0, Msg_Validandoteste);
                        TimeOutDelay = 100;
                        break;
                    }
                }
                break;    

            case Valida_Placa1: //Verifica se existe placa nas posições de teste da jiga para continuar os testes
                if (TimeOutDelay == 0) {
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_FimTeste_Placa1);
                    if ((ValorLido == 0xFFFF) || (ValorLido < Ref_3V_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                        Placa1[6] = 0;
                        GravacaoOk[0] = 0; //Não existe placa na posição 1
                        AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa1, 0); // Desalimenta placa 1 em teste
                        PosicaoPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                        SinalizaErroPlaca1 = 1;
                    } else {
                        GravacaoOk[0] = 1; //Existe placa na posição 1
                        PosicaoPlaca1 = 1;
                        Placa1[6] = 1;
                    }
                    EstagioTeste = Valida_Placa2;
                }
                break;

            case Valida_Placa2:
                ValorLido = ADReadVoltage(PlacaAD_1, AD_FimTeste_Placa2);
                if ((ValorLido == 0xFFFF) || (ValorLido < Ref_3V_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                    Placa2[6] = 0;
                    GravacaoOk[1] = 0; //Não existe placa na posição 2
                    AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa2, 0);
                    PosicaoPlaca2 = 0;
                    DefeitoPlaca2 = 1;
                    SinalizaErroPlaca2 = 1;
                } else {
                    GravacaoOk[1] = 1;
                    PosicaoPlaca2 = 1;
                    Placa2[6] = 1;
                }

                if (((Placa1[6]==0)&&(Placa1[7]==1))||(Placa2[6] == 0)&&(Placa2[7]==1)) {
                    EstagioTeste = SetupGravaTeste; 
                    SendTextMessage(3, 0, MsgPreparando_Gravacao_Teste);
                    TimeOutDelay = 200;
                    break;
                } else {
                    EstagioTeste = ReligaTeste;
                }
                break;
                
            case ReligaTeste:
                if (TimeOutDelay == 0) {
                    SendTextMessage(2, 0, MsgEmTeste);
                    SendTextMessage(3, 0, MsgInicializandoPlacas);
                    AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa1, RL_Alimenta_Placa1);
                    AlteraEstadoReles(PlacaRele_0, RL_Comut_CargaBateria_Placa1, RL_Comut_CargaBateria_Placa1);
                    Placa1[6] = 1;
                    AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa2, RL_Alimenta_Placa2);
                    AlteraEstadoReles(PlacaRele_0, RL_Comut_CargaBateria_Placa2, RL_Comut_CargaBateria_Placa2);
                    Placa2[6] = 1;
                    EstagioTeste = Teste_Bateria;
                    TestTimeout = 45; //tempo para executar todos os testes
                }
                break;

            case Teste_Bateria:
                if (TestTimeout == 25) {
                    SendTextMessage(3, 0, Msg_ValidaIO);
                    if (GravacaoOk[0] == 1) //Se placa 1 gravou OK
                    {
                        AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa1, RL_Comut_Bateria_Placa1); // Comuta bateria à fonte que alimenta a placa 1
                    }
                    if (GravacaoOk[1] == 1) //Se placa 2 gravou OK
                    {
                        AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa2, RL_Comut_Bateria_Placa2); // Comuta bateria à fonte que alimenta a placa 2    
                    }

                    if (GravacaoOk[0] == 1) {
                        EstagioTeste = Testes_Placa1;
                        break;
                    } else {
                        EstagioTeste = Testes_Placa2;
                        break;
                    }
                }
                break;

            case Testes_Placa1:
                if (GravacaoOk[0]==1) {//Se placa 1 gravou OK
                    if (TestTimeout < 3) {
                        ValorLido = ADReadVoltage(PlacaAD_0, AD_FimTeste_Placa1);
                        if (ValorLido < Ref_1V_Escala5V) {
                            AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa1, 0); // Tira a bateria da fonte que alimenta a placa 1
                            if (GravacaoOk[1]==1) {
                                EstagioTeste = Testes_Placa2;
                                break;
                            } else if (GravacaoOk[1]==0) {
                                EstagioTeste = Verifica_Defeitos_Placa1;
                                break;
                            } else {
                                UNUSED(1);
                            }
                        } else if (TestTimeout==0) {
                            AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa1, 0); // Tira a bateria da fonte que alimenta a placa 1
                            PutErrorMessageOnBuffer(MsgTimeoutTeste_Placa1);
                            DefeitoPlaca1 = 1;
                            if (GravacaoOk[1]) {
                                EstagioTeste = Testes_Placa2;
                                break;
                            } else {
                                EstagioTeste = Verifica_Defeitos_Placa1;
                                break;
                            }
                        } else {
                            UNUSED(1);
                        }
                    }
                } else {
                    EstagioTeste = Testes_Placa2;
                }
                break;

            case Testes_Placa2:
                if (GravacaoOk[1]==1) { //Se placa 2 gravou OK
                    if (TestTimeout < 3) {
                        ValorLido = ADReadVoltage(PlacaAD_1, AD_FimTeste_Placa2);
                        if (ValorLido < Ref_1V_Escala5V) {
                            AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa2, 0); // Tira a bateria da fonte que alimenta a placa 2
                            EstagioTeste = Verifica_Defeitos_Placa1;
                            break;
                        } else if (TestTimeout==0) {
                            AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa2, 0); // Tira a bateria da fonte que alimenta a placa 2
                            PutErrorMessageOnBuffer(MsgTimeoutTeste_Placa2);
                            DefeitoPlaca2 = 1;
                            EstagioTeste = Verifica_Defeitos_Placa1;
                            break;
                        } else {
                            UNUSED(1);
                        }
                    }
                } else {
                    EstagioTeste = Verifica_Defeitos_Placa1;
                }
                break;

            case Verifica_Defeitos_Placa1: //Verifica defeitos nos testes da placa 1
                if (GravacaoOk[0] == 1) {//Se placa 1 gravou OK
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_GPRS_Placa1);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaGPRS_Placa1);
                        Placa1[0] = 0; //Defeito GPRS
                        SinalizaErroPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                    } else {
                        Placa1[0] = 1;
                        SinalizaErroPlaca1 = 1;
                        DefeitoPlaca1 = 0;
                    }
                    Delay_ms(50);
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_WiFi_Placa1);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaWiFi_Placa1);
                        Placa1[1] = 0; //Defeito WiFi
                        SinalizaErroPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                    } else {
                        Placa1[1] = 1;
                        SinalizaErroPlaca1 = 1;
                        DefeitoPlaca1 = 0;
                    }
                    Delay_ms(50);
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_Ethernet_Placa1);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaEthernet_Placa1);
                        Placa1[2] = 0; //Defeito Ethernet
                        SinalizaErroPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                    } else {
                        Placa1[2] = 1;
                        SinalizaErroPlaca1 = 1;
                        DefeitoPlaca1 = 0;
                    }
                    Delay_ms(50);
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_Bateria_Placa1);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaBateria_Placa1);
                        Placa1[3] = 0; //Defeito Bateria
                        SinalizaErroPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                    } else {
                        Placa1[3] = 1;
                        SinalizaErroPlaca1 = 1;
                        DefeitoPlaca1 = 0;
                    }
                    Delay_ms(50);
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_RF_Placa1);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaRF_Placa1);
                        Placa1[4] = 0; //Defeito RF
                        SinalizaErroPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                    } else {
                        Placa1[4] = 1;
                        SinalizaErroPlaca1 = 1;
                        DefeitoPlaca1 = 0;
                    }
                    Delay_ms(50);
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_EEPROM_Placa1);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaEEPROM_Placa1);
                        Placa1[5] = 0; //Defeito EEProm
                        SinalizaErroPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                    } else {
                        Placa1[5] = 1;
                        SinalizaErroPlaca1 = 1;
                        DefeitoPlaca1 = 0;
                    }
                }
                TestDelay = 200;
                EstagioTeste = Verifica_Defeitos_Placa2;
                break;

            case Verifica_Defeitos_Placa2: //Verifica defeitos nos testes da placa 2
                if (GravacaoOk[1] == 1) {//Se placa 2 gravou OK
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_GPRS_Placa2);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaGPRS_Placa2);
                        Placa2[0] = 0; //Defeito GPRS
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    } else {
                        Placa2[0] = 1;
                        SinalizaErroPlaca1 = 1;
                        DefeitoPlaca1 = 0;
                    }
                    Delay_ms(50);
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_WiFi_Placa2);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaWiFi_Placa2);
                        Placa2[1] = 0; //Defeito WiFi
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    } else {
                        Placa2[1] = 1;
                        SinalizaErroPlaca1 = 1;
                        DefeitoPlaca1 = 0;
                    }
                    Delay_ms(50);
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_Ethernet_Placa2);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaEthernet_Placa2);
                        Placa2[2] = 0; //Defeito Ethernet
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    } else {
                        Placa2[2] = 1;
                        SinalizaErroPlaca1 = 1;
                        DefeitoPlaca1 = 0;
                    }
                    Delay_ms(50);
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_Bateria_Placa2);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaBateria_Placa2);
                        Placa2[3] = 0; //Defeito Bateria
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    } else {
                        Placa2[3] = 1;
                        SinalizaErroPlaca1 = 1;
                        DefeitoPlaca1 = 0;
                    }
                    Delay_ms(50);
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_RF_Placa2);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaRF_Placa2);
                        Placa2[4] = 0; //Defeito RF
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    } else {
                        Placa2[4] = 1;
                        SinalizaErroPlaca1 = 1;
                        DefeitoPlaca1 = 0;
                    }
                    Delay_ms(50);
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_EEPROM_Placa2);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaEEPROM_Placa2);
                        Placa2[5] = 0; //Defeito EEProm
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    } else {
                        Placa2[5] = 1;
                        SinalizaErroPlaca1 = 1;
                        DefeitoPlaca1 = 0;
                    }
                }
                TestDelay = 200;
                EstagioTeste = ValidaParaVersaoFinal;
                break;

            case SetupGravaTeste:                
                if (TimeOutDelay == 0) {
                    if (Placa1[7]==1) {
                        AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa1, RL_Grava_Placa1);
                        SetProcessador(PlacaGravador_0, SAM4E);
                        InitProg(PlacaGravador_0, '2'); 
                        GravacaoOk[0] = 0;
                    }
                    if (Placa2[7]==1) {
                        AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa2, RL_Grava_Placa2);
                        SetProcessador(PlacaGravador_1, SAM4E);
                        InitProg(PlacaGravador_1, '2'); 
                        GravacaoOk[1] = 0;
                    }
                    TimeOutDelay = 300;
                    StatusGrava = 1;
                    Check = 0;
                    EstagioTeste = VerificaFWTesteFinal;
                    SendTextMessage(2, 0, MsgGravandoFW_Teste);
                    SendTextMessage(3, 0, MsgFavorAguarde);
                    TestTimeout = 30;       
                    StatusGr[count] = 0;
                }
                break;
                
            case ValidaParaVersaoFinal:

                SendTextMessage(3, 0, MsgPreparando_Gravacao_Final);

                if ((Placa1[0] == 1) && (Placa1[1] == 1) && (Placa1[2] == 1) && (Placa1[3] == 1) && (Placa1[4] == 1) && (Placa1[5] == 1) && (Placa1[6] == 1)) {
                    DefeitoPlaca1 = 0;
                    AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa1, RL_Grava_Placa1);
                    SetProcessador(PlacaGravador_0, SAM4E);
                    InitProg(PlacaGravador_0, '1'); // placa gravação 0 e na posição 1
                    GravacaoOk[0] = 0;
                } else {
                    DefeitoPlaca1 = 1;
                }
                if ((Placa2[0] == 1) && (Placa2[1] == 1) && (Placa2[2] == 1) && (Placa2[3] == 1) && (Placa2[4] == 1) && (Placa2[5] == 1) && (Placa2[6] == 1)) {
                    DefeitoPlaca2 = 0;
                    AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa2, RL_Grava_Placa2); //Desliga 3V3 da placa de gravação da placa 2
                    SetProcessador(PlacaGravador_1, SAM4E);
                    InitProg(PlacaGravador_1, '1'); // placa gravação 1 e na posição 1
                    GravacaoOk[1] = 0;
                } else {
                    DefeitoPlaca2 = 1;
                }

                if ((DefeitoPlaca1 == 1) && (DefeitoPlaca2 == 1)) {//Se deu defeito no testes das duas placas 
                    EstagioTeste = FimTeste; //Finaliza Teste 
                    break;
                } else {
                    TimeOutDelay = 500;
                    StatusGrava = 1;
                    Check = 1;
                    EstagioTeste = VerificaFWTesteFinal;
                    SendTextMessage(2, 0, MsgGravandoFW_Final);
                    SendTextMessage(3, 0, MsgFavorAguarde);
                    TestTimeout = 30;
                    StatusGr[count] = 0;
                }
                break;

            case VerificaFWTesteFinal: // Verifica o firmware de teste
                if (TimeOutDelay == 0) {
                    for (count = 0; count <= 1; count++) //Verifica as duas placas em paralelo
                    {
                        StatusGr[count] = 0;
                        if (!(GRVerified[0]&(1 << count))) // se placa ainda não foi verificada
                        {
                            VerificaGravacao(count); // verifica status da gravação
                        }
                    }
                    TestDelay = 700;
                    EstagioTeste = Executa_Gravacao;
                }
                break;

            case Executa_Gravacao:

                if ((GRVerified[0] == 0b00000011) || (TestTimeout == 0)) // se todas as placas foram verificadas ou ocorreu timeout na gravação
                {
                    if (TestTimeout == 0)// se ocorreu timeout na gravação
                    {
                        if (CountTimeOut == 0) {
                            CountTimeOut++;
                            for (count = 0; count < 64; count++) //Zero buffer de Erro
                                MsgToShowBuffer[count] = 0;
                            MsgToShowPtr_RD = 0;
                            MsgToShowPtr_WR = 0;
                            for (count = 0; count <= 19; count++)
                                bus_fail_counter[count] = 0;
                            EstagioTeste = FimTeste;  
                            TestDelay = 100;
                            break;
                        } else {
                            for (count = 0; count <= 1; count++) // varre as placas a procura do timeout da gravação
                            {
                                if (!(GRVerified[0]&(1 << count))) {
                                    if (count == 0) {
                                        PutErrorMessageOnBuffer(MsgErroTimeoutProg + count); // marca erro somente na placa 1
                                    }
                                    if (count == 1) {
                                        PutErrorMessageOnBuffer(MsgErroTimeoutProg + count); // marca erro somente na placa 2 
                                    }
                                    GravacaoOk[count] = 0; //indica que deu erro nessa placa
                                    GRError[count] |= 1 << count;
                                }
                            }
                            if (GRError[count] == 0x03) { //se ocorreu erro nas duas placas
                                DefeitoPlaca1 = 2;
                                DefeitoPlaca2 = 2;
                                EstagioTeste = FimTeste; //Finaliza teste
                                StatusGrava = 0;
                                break;
                            } else {
                                GRVerified[count] = 0;
                                if (GravacaoOk[0] == 0) {
                                    DefeitoPlaca1 = 2; //Marca defeito de gravacão placa 1
                                    GRError[0] = 0;
                                }
                                if (GravacaoOk[1] == 0) {
                                    DefeitoPlaca2 = 2; //Marca defeito de gravacão placa 2
                                    GRError[1] = 0;
                                }
                                CountTimeOut = 0;
                                AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa1, 0);
                                AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa2, 0);
                                AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa1, 0);
                                AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa2, 0);
                                EstagioTeste = FimTeste;
                                StatusGrava = 0;
                                break;
                            }
                        }
                    } else if ((GRError[0] == 0x03) || (GRError[1] == 0x03)) {//se ocorreu erro nas duas placas (1 = NOK)
                        DefeitoPlaca1 = 2; //Marca defeito de gravacão placa 1
                        DefeitoPlaca2 = 2; //Marca defeito de gravacão placa 2
                        EstagioTeste = FimTeste; //Finaliza teste
                        StatusGrava = 0;
                        break;
                    } else {//se gravação OK em alguma placa
                        GRVerified[0] = 0;
                        CountTimeOut = 0;

                        if (GravacaoOk[0] == 0) {
                            DefeitoPlaca1 = 2; //Marca defeito de gravacão placa 1
                        } else {
                            DefeitoPlaca1 = 0;
                        }
                        if (GravacaoOk[1] == 0) {
                            DefeitoPlaca2 = 2; //Marca defeito de gravacão placa 2
                        } else {
                            DefeitoPlaca2 = 0;
                        }
                        if (Check == 0) {
                            StatusGrava = 0;
                            AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa1, 0);
                            AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa2, 0);
                            AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa1, 0);
                            AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa2, 0);
                            EstagioTeste = ReligaTeste;
                            TestTimeout = 0;
                            TimeOutDelay = 1000;
                            break;
                        } else if (Check == 1) {
                            StatusGrava = 0;
                            AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa1, 0);
                            AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa2, 0);
                            AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa1, 0);
                            AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa2, 0);
                            EstagioTeste = FimTeste;
                            TimeOutDelay = 500;
                            break;
                        }
                    }
                    TestDelay = 500;
                } else {
                    EstagioTeste = VerificaFWTesteFinal;
                }
                break;

                /*######################################***Resultado dos Testes***####################################################*/
            case FimTeste:
                TestTimeout = 0;
                AlteraEstadoReles(PlacaRele_0, RL_Comut_CargaBateria_Placa1, 0);
                AlteraEstadoReles(PlacaRele_0, RL_Comut_CargaBateria_Placa2, 0);
                AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa1, 0);
                AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa2, 0);
                AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa1, 0);
                AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa2, 0);
                TimeOutDelay = 100;
                EmiteBipe(5, 4);
                TimeoutFimTeste = 45000; //Seta para mostrar o resultado do teste somente por 60 seg. no display após o teste terminar
                EstagioTeste = ExibeResultado;
                break;

            case ExibeResultado: //Exibe resultado do teste para as duas placas
                if ((TestTimeout == 0)&&(TimeOutDelay == 0)) {
                    LimpaDisplay();
                    PlacaOk[0] = 0;
                    MostraResultado();
                    EstagioTeste = ExibeResultadoportempo;
                }

                valor = EstadoTeclas(); //Aguarda tecla Inicio para mostrar os defeitos no display
                if ((valor & 0x01) == 0) {
                    EstagioTeste = Finaliza_Testes; //Finaliza o teste para mostrar os defeitos no display
                    TimeoutFimTeste = 60000; //Seta para mostrar o resultado do teste somente por 60 seg. no display após o teste terminar
                    TimeOutDelay = 200;
                }
                break;

            case ExibeResultadoportempo:
                TimeOutDelay = 100;
                TestTimeout = 4; 	
                EstagioTeste = MostraResults;
                break;

            case MostraResults:
                if (TimeOutDelay == 0) {
                    if (TestTimeout == 0) {
                        if (MsgToShowPtr_WR != 0) {
                            LimpaDisplay();
                            SendTextMessage(1, 0, Msg_pressione_chave);
                            SendTextMessage(2, 0, Msg_chave_inicio);
                            SendTextMessage(3, 0, Msg_para_visualizar);
                            SendTextMessage(4, 0, Msg_os_defeitos_correspondentes);
                            EstagioTeste = ExibeResultado;
                            TimeOutDelay = 0;
                            TestTimeout = 4;
                        } else {
                            EstagioTeste = ExibeResultado;
                            TimeOutDelay = 0;
                            TestTimeout = 1;
                            LimpaDisplay();
                            SendTextMessage(2, 0, MsgPressioneInicio);
                        }
                    }

                    valor = EstadoTeclas(); //Aguarda tecla Inicio para mostrar os defeitos no display

                    if ((valor & 0x01) == 0) {
                        EstagioTeste = Finaliza_Testes;
                        TimeoutFimTeste = 60000; //Para mostrar o resultado do teste somente por 60 seg. no display após o teste terminar
                        TimeOutDelay = 200;
                    }
                }
                break;
\
            case Finaliza_Testes:
                if (TimeOutDelay == 0) {
                    EmTeste = 0;
                    FinalizaTesteFlag = 1;
                    IniciaTesteFlag = 0;
                    StatusGrava = 0;
                    LimpaDisplay();

                    if ((DefeitoPlaca1 == 0)&&(PosicaoPlaca1 == 1)&&(Placa1[7] == 1)) {
                        Counter++; //Incrementa 1 se teste OK                
                    } else {
                        Counter_Nok++; //Incrementa 1 se teste Não OK
                    }

                    if ((DefeitoPlaca2 == 0)&&(PosicaoPlaca2 == 1)&&(Placa2[7] == 1)) {
                        Counter++; //Incrementa 1 se teste OK
                    } else {
                        Counter_Nok++; //Incrementa 1 se teste Não OK
                    }

                    if (MsgToShowPtr_WR == 0) // Se nenhuma falha ocorreu, mostra resultado OK
                    {
                        TesteOK = 1;
                    }
                }
                break;
        }
    }
    if ((EmTeste == 1)&&(TempoEmTeste != TempoEmTesteAnt)&&(EstagioTeste < FimTeste)) {
        for (count = 20; count < 26; count++)
            bus_tx_buffer[count] = 0;

        bus_tx_buffer[0] = 4; // Linha 4
        bus_tx_buffer[1] = 3; // Coluna 3

        bus_tx_buffer[2] = ' ';
        bus_tx_buffer[3] = (TestTimeout / 10) + 48; //'-';
        bus_tx_buffer[4] = (TestTimeout % 10) + 48; //' ';

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

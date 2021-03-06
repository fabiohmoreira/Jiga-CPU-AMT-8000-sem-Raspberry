/********************************************************************/
/* Nome do arquivo: RotinaTeste.c									*/
/* 																	*/
/* Vers?o:	1.0.0 													*/
/*            Intelbras S/A.										*/
/*                                                           		*/
/* Autor:	Elder da Fonseca Silv?rio       						*/
/*                                                                  */
/* Fun??o: Execu??o da rotina de teste do produto					*/
/*                                                           		*/
/* Vers?o:	2.0.0 													*/
/*            Intelbras S/A.										*/
/*                                                           		*/
/* Autor:	F?bio Henrique Moreira          						*/
/*                                                                  */
/* Fun??o: Melhorias na rotina de teste e adi??o do novo gravador   */
/*          		                                             	*/
/********************************************************************/
#include "define.h"
#include "global_vars.h"

////////// Defini??o dos Reles ///////////

//Placa Rel? 0
#define RL_Alimenta_Placa1              0x01    
#define RL_Comut_Bateria_Placa1         0x02
#define RL_Comut_CargaBateria_Placa1    0x04 //Rel? em NF
#define RL_Alimenta_Placa2              0x08    
#define RL_Comut_Bateria_Placa2         0x10
#define RL_Comut_CargaBateria_Placa2    0x20 //Rel? em NF
#define RL_Aciona_Gravadores            0x40 //Rel? em NF

//Placa Rel? 1
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


////////// Defini??o dos canais de A/D ///////////
//Placa AD 0
#define AD_GPRS_Placa1          0x01 // J20 da placa na posi??o 1
#define AD_WiFi_Placa1     		0x02 // J23 da placa na posi??o 1
#define AD_Ethernet_Placa1      0x03 // J24 da placa na posi??o 1
#define AD_Bateria_Placa1       0x04 // J27 da placa na posi??o 1
#define AD_RF_Placa1            0x05 // J22 da placa na posi??o 1
#define AD_EEPROM_Placa1        0x06 // J25 da placa na posi??o 1
#define AD_FimTeste_Placa1      0x07 // J28 da placa na posi??o 1
#define AD_Led3_Placa1          0x08 // J3 da placa na posi??o 1

//Placa AD 1
#define AD_GPRS_Placa2          0x01 // J20 da placa na posi??o 2
#define AD_WiFi_Placa2     		0x02 // J23 da placa na posi??o 2
#define AD_Ethernet_Placa2      0x03 // J24 da placa na posi??o 2
#define AD_Bateria_Placa2       0x04 // J27 da placa na posi??o 2
#define AD_RF_Placa2            0x05 // J22 da placa na posi??o 2
#define AD_EEPROM_Placa2        0x06 // J25 da placa na posi??o 2
#define AD_FimTeste_Placa2      0x07 // J28 da placa na posi??o 2
#define AD_Led3_Placa2          0x08 // J3 da placa na posi??o 2

////////////n?veis de tens?o/////////////////
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
    Alimenta_Placas,
    Valida_Placa1,
    Valida_Placa2,
    Estado_Inicial_IO_Placa1,
    Estado_Inicial_IO_Placa2,
    Teste_Bateria,
    Testes_Placa1,
    Testes_Placa2,
    Verifica_Defeitos_Placa1,
    Verifica_Defeitos_Placa2,
    ValidaParaVersaoFinal,
    GravaVersaoFinal,
    VerificaFWTesteFinal,
    Executa_Gravacao,
    Alimenta_Gravacao,
    Valida_Gravacao_Placa_1,
    Valida_Gravacao_Placa_2,
    FimTeste,
    ExibeResultado,
    ExibeResultadoportempo,
    MostraResults,
    Mostra_por_tempo,
    Pressione_Teclas,
    Finaliza_Testes,
} Pcv_Enum_t;


//***********declara??o de variaveis e vetores***************************************************************
unsigned int Placa1[9], Placa2[9], grava, VarErro;
unsigned char GRVerified[1], GRError[2], GravacaoOk[2], PlacaOk[2], count = 0, valor = 0;
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

    if ((Placa1[0] == 1)&&(Placa1[1] == 1)&&(Placa1[2] == 1)&&(Placa1[3] == 1)&&(Placa1[4] == 1)&&(Placa1[5] == 1)&&(Placa1[6] == 1)&&(GRError[0] == 1)&&(Placa1[8] == 1)&&(GravacaoOk[0] == 1)) //Se todos os testes OK
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
        PlacaOk[0] |= 0x08; //Seta bit para indica??o dos resultados nos Leds da jiga)
    } else if ((GravacaoOk[0] == 0)&&(SinalizaErroPlaca1 == 1)) {
        bus_tx_buffer[4] = 'S';
        bus_tx_buffer[5] = '/';
        bus_tx_buffer[6] = ' ';
        bus_tx_buffer[7] = 'G';
        bus_tx_buffer[8] = 'R';
        bus_tx_buffer[9] = 'A';
        bus_tx_buffer[10] = 'V';
        bus_tx_buffer[11] = 'A';
    } else if ((Placa1[0] == 0) || (Placa1[1] == 0) || (Placa1[2] == 0) || (Placa1[3] == 0) || (Placa1[4] == 0) || (Placa1[5] == 0) || (Placa1[6] == 0) || (GRError[0] == 0) || (Placa1[8] == 0) || (GravacaoOk[0] == 0)) //Se algum teste deu Erro
    {
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

    if ((Placa2[0] == 1)&&(Placa2[1] == 1)&&(Placa2[2] == 1)&&(Placa2[3] == 1)&&(Placa2[4] == 1)&&(Placa2[5] == 1)&&(Placa2[6] == 1)&&(GRError[1] == 1)&&(Placa2[8] == 1)&&(GravacaoOk[1] == 1)) {
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
    } else if ((GravacaoOk[1] == 0)&&(SinalizaErroPlaca2 == 1)) {
        bus_tx_buffer[15] = 'S';
        bus_tx_buffer[16] = '/';
        bus_tx_buffer[17] = ' ';
        bus_tx_buffer[18] = 'G';
        bus_tx_buffer[19] = 'R';
        bus_tx_buffer[20] = 'A';
        bus_tx_buffer[21] = 'V';
        bus_tx_buffer[22] = 'A';
    } else if ((Placa2[0] == 0) || (Placa2[1] == 0) || (Placa2[2] == 0) || (Placa2[3] == 0) || (Placa2[4] == 0) || (Placa2[5] == 0) || (Placa2[6] == 0) || (GRError[1] == 0) || (Placa2[8] == 0) || (GravacaoOk[1] == 0)) {
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

void VerificaGravacao(char Gravador) //verifica a grava??o da placa gravador 0 e 1
{
    int MsgIndex;

    GrReadStatus(PlacaGravador_0 + Gravador);
    if (StatusGr[Gravador] == 0x01 || StatusGr[Gravador] == 0x02 || StatusGr[Gravador] == 0x03 || StatusGr[Gravador] == 0xFB) {
        SendTextMessage(2, 0, MsgGravandoFW_Final);
        SendTextMessage(3, 0, MsgFavorAguarde);
        StatusGr[Gravador] = 0;
        ContadorErro = 0;
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
        } else if ((StatusGr[Gravador] == 0xFF) && (ContadorErro > 40)) {
            PutErrorMessageOnBuffer(MsgBugGravacao + MsgIndex);
            TemErro = 1;
        } else if ((StatusGr[Gravador] == 0xFF) && (ContadorErro <= 40)) {
            ContadorErro++;
        } else {
            UNUSED(1); /* Nao faz nada, usado para a ?ltima tratativa */
        }

        if (TemErro) {
            GRVerified[0] |= 1 << Gravador; // Indica que foi verificado

            GRError[Gravador] |= 1 << Gravador; // Ativa a indica??o de problemas
            GravacaoOk[Gravador] = 0; //Marca erro de grava??o

            StatusGr[Gravador] = 0;
            TemErro = 0;
            ContadorErro = 0;
        }

    } else if (StatusGr[Gravador] == 0x04) {
        TestDelay = 500;
        GRVerified[0] |= 1 << Gravador; // Indica que foi verificado
        GravacaoOk[Gravador] = 1; //Marca grava??o OK

        SendTextMessage(3, 0, MsgGravacaoOK1 + Gravador);

        if (((grava == 0)&&(TestTimeout > 20)) || ((grava == 1)&&(TestTimeout > 30)))//Evitar dar grava??o OK sem ter gravado corretamente ...bug da placa de grava??o nova
        {
            GravacaoOk[Gravador] = 0; //marca erro na grava??o
            PutErrorMessageOnBuffer(MsgBugGravacao);
        }
        StatusGr[Gravador] = 0;
        ContadorErro = 0;
    }
}

void RotinaDeTeste(void) {
    static int ValorLido, TempoEmTesteAnt;
    static char CountTimeOut = 0;

    if ((EmTeste)&&(TestDelay == 0)&&(ApoioFlags == 0)) {
        switch (EstagioTeste) {
            case Inicio: // Inicia o vetor com "1" que corresponde a teste OK
                Placa1[0] = 1; //GPRS
                Placa1[1] = 1; //WiFi
                Placa1[2] = 1; //Ethernet
                Placa1[3] = 1; //Bateria
                Placa1[4] = 1; //RF
                Placa1[5] = 1; //EEProm
                Placa1[6] = 1; //Estado inicial dos IO
                Placa1[7] = 1; //Estado final dos IO
                Placa1[8] = 1; //Gravacao final OK
                SinalizaErroPlaca1 = 1;
                GRError[0] = 1;
                PosicaoPlaca1 = 1;
                DefeitoPlaca1 = 0;

                Placa2[0] = 1; //GPRS
                Placa2[1] = 1; //WiFi
                Placa2[2] = 1; //Ethernet
                Placa2[3] = 1; //Bateria
                Placa2[4] = 1; //RF
                Placa2[5] = 1; //EEProm
                Placa2[6] = 1; //Estado inicial dos IO
                Placa2[7] = 1; //Estado final dos IO
                Placa2[8] = 1; //Gravacao final OK
                SinalizaErroPlaca2 = 1;
                GRError[1] = 1;
                PosicaoPlaca2 = 1;
                DefeitoPlaca2 = 0;

                SendTextMessage(2, 0, MsgInicializandoPlacas);
                SendTextMessage(3, 0, MsgEmBranco);

                EstagioTeste = Alimenta_Placas;
                TestDelay = 100;
                break;

            case Alimenta_Placas:
                AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa1, RL_Alimenta_Placa1); // Alimenta placa 1 em teste
                AlteraEstadoReles(PlacaRele_0, RL_Comut_CargaBateria_Placa1, RL_Comut_CargaBateria_Placa1); // Tira a carga da bateria 1 - contato NF

                AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa2, RL_Alimenta_Placa2); // Alimenta placa 2 em teste
                AlteraEstadoReles(PlacaRele_0, RL_Comut_CargaBateria_Placa2, RL_Comut_CargaBateria_Placa2); // Tira a carga da bateria 2 - contato NF

                SendTextMessage(2, 0, MsgEmTeste);
                SendTextMessage(3, 0, Msg_Validandoteste);

                TestDelay = 1000;
                EstagioTeste = Valida_Placa1;
                break;

            case Valida_Placa1: //Verifica se existe placa nas posi??es de teste da jiga para continuar os testes
                ValorLido = ADReadVoltage(PlacaAD_0, AD_FimTeste_Placa1);
                if ((ValorLido == 0xFFFF) || (ValorLido < Ref_3V_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                    Placa1[6] = 0;
                    GravacaoOk[0] = 0; //N?o existe placa na posi??o 1
                    AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa1, 0); // Desalimenta placa 1 em teste
                    PosicaoPlaca1 = 0;
                    DefeitoPlaca1 = 1;
                } else {
                    GravacaoOk[0] = 1; //Existe placa na posi??o 1
                    PosicaoPlaca1 = 1;
                }
                EstagioTeste = Valida_Placa2;
                break;

            case Valida_Placa2:
                ValorLido = ADReadVoltage(PlacaAD_1, AD_FimTeste_Placa2);
                if ((ValorLido == 0xFFFF) || (ValorLido < Ref_3V_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                    Placa2[6] = 0;
                    GravacaoOk[1] = 0; //N?o existe placa na posi??o 2
                    AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa2, 0);
                    PosicaoPlaca2 = 0;
                    DefeitoPlaca2 = 1;
                } else {
                    GravacaoOk[1] = 1;
                    PosicaoPlaca2 = 1;
                }

                if ((GravacaoOk[0] == 0)&&(GravacaoOk[1] == 0)) {
                    EstagioTeste = FimTeste;
                } else {
                    if (((GravacaoOk[0] == 1) && (GravacaoOk[1] == 0)) || ((GravacaoOk[0] == 0) && (GravacaoOk[1] == 1))) {
                        for (count = 0; count < 64; count++) //Zero buffer de Erro
                            MsgToShowBuffer[count] = 0;
                        MsgToShowPtr_RD = 0;
                        MsgToShowPtr_WR = 0;
                    }
                    EstagioTeste = Estado_Inicial_IO_Placa1;
                }
                break;

            case Estado_Inicial_IO_Placa1: //Confere estado inicial dos IO da placa 1 - N?vel l?gico 1
                SendTextMessage(3, 0, Msg_ValidaIO);
                if (GravacaoOk[0] == 1) //Se placa 1 gravou OK (se existe)
                {
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_GPRS_Placa1);
                    if ((ValorLido == 0xFFFF) || (ValorLido < Ref_3V_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                        PutErrorMessageOnBuffer(MsgPinoAudioOut_Placa1);
                        Placa1[6] = 0;
                        SinalizaErroPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_WiFi_Placa1);
                    if ((ValorLido == 0xFFFF) || (ValorLido < Ref_1V_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                        PutErrorMessageOnBuffer(MsgPinoAudioIn_Placa1);
                        Placa1[6] = 0;
                        SinalizaErroPlaca1 = 0;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_Ethernet_Placa1);
                    if ((ValorLido == 0xFFFF) || (ValorLido < Ref_3V_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                        PutErrorMessageOnBuffer(MsgPinoCL_Placa1);
                        Placa1[6] = 0;
                        SinalizaErroPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_Bateria_Placa1);
                    if ((ValorLido == 0xFFFF) || (ValorLido < Ref_3V_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                        PutErrorMessageOnBuffer(MsgPinoDL_Placa1);
                        Placa1[6] = 0;
                        SinalizaErroPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_RF_Placa1);
                    if ((ValorLido == 0xFFFF) || (ValorLido < Ref_3V_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                        PutErrorMessageOnBuffer(MsgPinoRL_Placa1);
                        Placa1[6] = 0;
                        SinalizaErroPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                        DefeitoPlaca1 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_EEPROM_Placa1);
                    if ((ValorLido == 0xFFFF) || (ValorLido < Ref_3V_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                        PutErrorMessageOnBuffer(MsgPinoDR_Placa1);
                        Placa1[6] = 0;
                        SinalizaErroPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                    }
                }
                EstagioTeste = Estado_Inicial_IO_Placa2;
                break;

            case Estado_Inicial_IO_Placa2: //Confere estado inicial dos IO da placa 2 - N?vel l?gico 1
                if (GravacaoOk[1] == 1) //Se placa 2 gravou OK (se existe)
                {
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_GPRS_Placa2);
                    if ((ValorLido == 0xFFFF) || (ValorLido < Ref_3V_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                        PutErrorMessageOnBuffer(MsgPinoAudioOut_Placa2);
                        Placa2[6] = 0;
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_WiFi_Placa2);
                    if ((ValorLido == 0xFFFF) || (ValorLido < Ref_1_7_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                        PutErrorMessageOnBuffer(MsgPinoAudioIn_Placa2);
                        Placa2[6] = 0;
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_Ethernet_Placa2);
                    if ((ValorLido == 0xFFFF) || (ValorLido < Ref_3V_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                        PutErrorMessageOnBuffer(MsgPinoCL_Placa2);
                        Placa2[6] = 0;
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_Bateria_Placa2);
                    if ((ValorLido == 0xFFFF) || (ValorLido < Ref_3V_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                        PutErrorMessageOnBuffer(MsgPinoDL_Placa2);
                        Placa2[6] = 0;
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_RF_Placa2);
                    if ((ValorLido == 0xFFFF) || (ValorLido < Ref_3V_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                        PutErrorMessageOnBuffer(MsgPinoRL_Placa2);
                        Placa2[6] = 0;
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_EEPROM_Placa2);
                    if ((ValorLido == 0xFFFF) || (ValorLido < Ref_3V_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                        PutErrorMessageOnBuffer(MsgPinoDR_Placa2);
                        Placa2[6] = 0;
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    }
                }
                EstagioTeste = Teste_Bateria;
                TestTimeout = 42; //36 segundos para executar todos os testes
                break;

            case Teste_Bateria:
                if (TestTimeout == 25) //10 segundos com bateria conectada e depois desconecta
                {
                    if (GravacaoOk[0] == 1) //Se placa 1 gravou OK
                    {
                        AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa1, RL_Comut_Bateria_Placa1); // Comuta bateria ? fonte que alimenta a placa 1
                    }
                    if (GravacaoOk[1] == 1) //Se placa 2 gravou OK
                    {
                        AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa2, RL_Comut_Bateria_Placa2); // Comuta bateria ? fonte que alimenta a placa 2    
                    }

                    if (GravacaoOk[0] == 1) {
                        EstagioTeste = Testes_Placa1;
                    } else if (GravacaoOk[0] == 0) {
                        EstagioTeste = Testes_Placa2;
                    }
                }
                break;

            case Testes_Placa1:
                if (GravacaoOk[0] == 1) //Se placa 1 gravou OK
                {
                    if (TestTimeout < 3) {
                        ValorLido = ADReadVoltage(PlacaAD_0, AD_FimTeste_Placa1);
                        if (ValorLido < Ref_1V_Escala5V) {
                            AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa1, 0); // Tira a bateria da fonte que alimenta a placa 1
                            if (GravacaoOk[1]) {
                                EstagioTeste = Testes_Placa2;
                            } else if (GravacaoOk[1] == 0) {
                                EstagioTeste = Verifica_Defeitos_Placa1;
                            }
                        } else if (TestTimeout == 0) {
                            AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa1, 0); // Tira a bateria da fonte que alimenta a placa 1
                            PutErrorMessageOnBuffer(MsgTimeoutTeste_Placa1);
                            DefeitoPlaca1 = 1;
                            if (GravacaoOk[1])
                                EstagioTeste = Testes_Placa2;
                            else if (GravacaoOk[1] == 0)
                                EstagioTeste = Verifica_Defeitos_Placa1;
                        }
                    }
                }
                TestDelay = 500;
                break;

            case Testes_Placa2:
                if (GravacaoOk[1] == 1) //Se placa 2 gravou OK
                {
                    if (TestTimeout < 3) {
                        ValorLido = ADReadVoltage(PlacaAD_1, AD_FimTeste_Placa2);
                        if (ValorLido < Ref_1V_Escala5V) {
                            AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa2, 0); // Tira a bateria da fonte que alimenta a placa 2
                            EstagioTeste = Verifica_Defeitos_Placa1;
                        } else if (TestTimeout == 0) {
                            AlteraEstadoReles(PlacaRele_0, RL_Comut_Bateria_Placa2, 0); // Tira a bateria da fonte que alimenta a placa 2
                            PutErrorMessageOnBuffer(MsgTimeoutTeste_Placa2);
                            DefeitoPlaca2 = 1;
                            EstagioTeste = Verifica_Defeitos_Placa1;
                        }
                    }
                }
                TestDelay = 500;
                break;

            case Verifica_Defeitos_Placa1: //Verifica defeitos nos testes da placa 1
                if (GravacaoOk[0] == 1) //Se placa 1 gravou OK
                {
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_GPRS_Placa1);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaGPRS_Placa1);
                        Placa1[0] = 0; //Defeito GPRS
                        SinalizaErroPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_WiFi_Placa1);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaWiFi_Placa1);
                        Placa1[1] = 0; //Defeito WiFi
                        SinalizaErroPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_Ethernet_Placa1);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaEthernet_Placa1);
                        Placa1[2] = 0; //Defeito Ethernet
                        SinalizaErroPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_Bateria_Placa1);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaBateria_Placa1);
                        Placa1[3] = 0; //Defeito Bateria
                        SinalizaErroPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_RF_Placa1);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaRF_Placa1);
                        Placa1[4] = 0; //Defeito RF
                        SinalizaErroPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_EEPROM_Placa1);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaEEPROM_Placa1);
                        Placa1[5] = 0; //Defeito EEProm
                        SinalizaErroPlaca1 = 0;
                        DefeitoPlaca1 = 1;
                    }
                }
                TestTimeout = 0;
                EstagioTeste = Verifica_Defeitos_Placa2;
                break;

            case Verifica_Defeitos_Placa2: //Verifica defeitos nos testes da placa 2
                if (GravacaoOk[1] == 1) //Se placa 2 gravou OK
                {
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_GPRS_Placa2);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaGPRS_Placa2);
                        Placa2[0] = 0; //Defeito GPRS
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_WiFi_Placa2);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaWiFi_Placa2);
                        Placa2[1] = 0; //Defeito WiFi
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_Ethernet_Placa2);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaEthernet_Placa2);
                        Placa2[2] = 0; //Defeito Ethernet
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_Bateria_Placa2);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaBateria_Placa2);
                        Placa2[3] = 0; //Defeito Bateria
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_RF_Placa2);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaRF_Placa2);
                        Placa2[4] = 0; //Defeito RF
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    }
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_EEPROM_Placa2);
                    if (ValorLido > Ref_1V_Escala5V) {
                        PutErrorMessageOnBuffer(MsgFalhaEEPROM_Placa2);
                        Placa2[5] = 0; //Defeito EEProm
                        SinalizaErroPlaca2 = 0;
                        DefeitoPlaca2 = 1;
                    }
                }
                EstagioTeste = ValidaParaVersaoFinal;
                TestDelay = 200;
                break;

            case ValidaParaVersaoFinal:

                SendTextMessage(3, 0, MsgPreparando_Gravacao_Final);

                if ((Placa1[0] == 1) && (Placa1[1] == 1) && (Placa1[2] == 1) && (Placa1[3] == 1) && (Placa1[4] == 1) && (Placa1[5] == 1) && (Placa1[6] == 1)) {
                    DefeitoPlaca1 = 0;
                    AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa1, RL_Grava_Placa1);
                } else {
                    DefeitoPlaca1 = 1;
                }
                if ((Placa2[0] == 1) && (Placa2[1] == 1) && (Placa2[2] == 1) && (Placa2[3] == 1) && (Placa2[4] == 1) && (Placa2[5] == 1) && (Placa2[6] == 1)) {
                    DefeitoPlaca2 = 0;
                    AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa2, RL_Grava_Placa2); //Desliga 3V3 da placa de grava??o da placa 2
                } else {
                    DefeitoPlaca2 = 1;
                }

                if ((DefeitoPlaca1 == 1) && (DefeitoPlaca2 == 1)) //Se deu defeito no testes das duas placas 
                {
                    EstagioTeste = FimTeste; //Finaliza Teste 
                } else {
                    TimeOutDelay = 500;
                    EstagioTeste = GravaVersaoFinal;
                    AlteraEstadoReles(PlacaRele_0, RL_Aciona_Gravadores, 0);
                }
                break;

            case GravaVersaoFinal: //Grava firmware final
                if (TimeOutDelay == 0) {
                    if ((PosicaoPlaca1 == 0) || (DefeitoPlaca1 == 1)) //para n?o iniciar grava??o na posi??o que n?o possuir placa
                    {
                        GRVerified[0] = 0x01; //Condi??o para n?o travar durante a verifica??o, caso n?o tenha placa
                    }
                    if ((PosicaoPlaca2 == 0) || (DefeitoPlaca2 == 1)) {
                        GRVerified[0] = 0x02;
                    }
                    if ((GRVerified[0] & 0x01) == 0) {
                        SetProcessador(PlacaGravador_0, SAM4E);
                        InitProg(PlacaGravador_0, '1'); // placa grava??o 0 e na posi??o 1
                        GravacaoOk[0] = 0;
                    }
                    if ((GRVerified[0] & 0x02) == 0) {
                        SetProcessador(PlacaGravador_1, SAM4E);
                        InitProg(PlacaGravador_1, '1'); // placa grava??o 1 e na posi??o 1
                        GravacaoOk[1] = 0;
                    }

                    TimeOutDelay = 1000;
                    EstagioTeste = VerificaFWTesteFinal;
                    TestTimeout = 30;
                }
                break;

            case VerificaFWTesteFinal: // Verifica o firmware de teste
                if (TimeOutDelay == 0) {
                    for (count = 0; count <= 1; count++) //Verifica as duas placas em paralelo
                    {
                        StatusGr[count] = 0;
                        if (!(GRVerified[0]&(1 << count))) // se placa ainda n?o foi verificada
                        {
                            VerificaGravacao(count); // verifica status da grava??o
                        }
                    }
                    TestDelay = 1000;
                    EstagioTeste = Executa_Gravacao;
                }
                break;

            case Executa_Gravacao:

                if ((GRVerified[0] == 0b00000011) || (TestTimeout == 0)) // se todas as placas foram verificadas ou ocorreu timeout na grava??o
                {
                    if (TestTimeout == 0)// se ocorreu timeout na grava??o
                    {
                        if (CountTimeOut == 0) {
                            CountTimeOut++;
                            for (count = 0; count < 64; count++) //Zero buffer de Erro
                                MsgToShowBuffer[count] = 0;
                            MsgToShowPtr_RD = 0;
                            MsgToShowPtr_WR = 0;
                            for (count = 0; count <= 19; count++)
                                bus_fail_counter[count] = 0;

                            EstagioTeste = ValidaParaVersaoFinal; //Reinicia grava??o
                            TestDelay = 700;
                        } else {
                            for (count = 0; count <= 1; count++) // varre as placas a procura do timeout da grava??o
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
                            if (GRError[count] == 0x03) //se ocorreu erro nas duas placas
                            {
                                DefeitoPlaca1 = 2;
                                DefeitoPlaca2 = 2;
                                EstagioTeste = FimTeste; //Finaliza teste
                            } else {
                                GRVerified[count] = 0;
                                if (GravacaoOk[0] == 0) {
                                    DefeitoPlaca1 = 2; //Marca defeito de gravac?o placa 1
                                    GRError[0] = 0;
                                }
                                if (GravacaoOk[1] == 0) {
                                    DefeitoPlaca2 = 2; //Marca defeito de gravac?o placa 2
                                    GRError[1] = 0;
                                }
                                CountTimeOut = 0;
                                AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa1, 0);
                                AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa2, 0);
                                EstagioTeste = FimTeste;
                            }
                        }
                    } else if ((GRError[0] == 0x03) || (GRError[1] == 0x03)) {//se ocorreu erro nas duas placas (1 = NOK)
                        DefeitoPlaca1 = 2; //Marca defeito de gravac?o placa 1
                        DefeitoPlaca2 = 2; //Marca defeito de gravac?o placa 2
                        EstagioTeste = FimTeste; //Finaliza teste
                    } else {//se grava??o OK em alguma placa
                        GRVerified[0] = 0;
                        CountTimeOut = 0;

                        if (GravacaoOk[0] == 0) {
                            DefeitoPlaca1 = 2; //Marca defeito de gravac?o placa 1
                        } else {
                            DefeitoPlaca1 = 0;
                        }
                        if (GravacaoOk[1] == 0) {
                            DefeitoPlaca2 = 2; //Marca defeito de gravac?o placa 2
                        } else {
                            DefeitoPlaca2 = 0;
                        }
                        EstagioTeste = Alimenta_Gravacao;
                        AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa1, 0);
                        AlteraEstadoReles(PlacaRele_1, RL_Grava_Placa2, 0);
                    }
                    TestDelay = 500;
                } else {
                    EstagioTeste = VerificaFWTesteFinal;
                }
                break;

            case Alimenta_Gravacao:

                SendTextMessage(2, 0, MsgEmTeste);
                SendTextMessage(3, 0, Msg_ValidandoGravacao);

                if (GravacaoOk[0] == 1) {
                    AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa1, RL_Alimenta_Placa1);
                }
                if (GravacaoOk[1] == 1) {
                    AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa2, RL_Alimenta_Placa2);
                }
                TimeOutDelay = 1000;
                EstagioTeste = Valida_Gravacao_Placa_1;
                break;

            case Valida_Gravacao_Placa_1:
                if ((GravacaoOk[0] == 1)&&(PosicaoPlaca1 == 1)) {
                    ValorLido = ADReadVoltage(PlacaAD_0, AD_FimTeste_Placa1);
                    if ((ValorLido == 0xFFFF) || (ValorLido < Ref_3V_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                        Placa1[8] = 1;
                        EstagioTeste = Valida_Gravacao_Placa_2;
                        AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa1, 0);
                        break;
                    } else {
                        Placa1[8] = 0;
                        AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa1, 0);
                        DefeitoPlaca1 = 1;
                        EstagioTeste = Valida_Gravacao_Placa_2;
                        PutErrorMessageOnBuffer(MsgFalhaGravacaoFinalPlaca1);
                        break;
                    }
                } else {
                    EstagioTeste = Valida_Gravacao_Placa_2;
                }
                break;

            case Valida_Gravacao_Placa_2:
                if ((GravacaoOk[1] == 1)&&(PosicaoPlaca2 == 1)) {
                    ValorLido = ADReadVoltage(PlacaAD_1, AD_FimTeste_Placa2);
                    if ((ValorLido == 0xFFFF) || (ValorLido < Ref_3V_Escala5V) || (ValorLido > Ref_4V_Escala5V)) {
                        EstagioTeste = FimTeste;
                        AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa2, 0);
                        Placa2[8] = 1;
                        break;
                    } else {
                        Placa2[8] = 0;
                        AlteraEstadoReles(PlacaRele_0, RL_Alimenta_Placa2, 0);
                        DefeitoPlaca2 = 1;
                        EstagioTeste = FimTeste;
                        PutErrorMessageOnBuffer(MsgFalhaGravacaoFinalPlaca2);
                        break;
                    }
                } else {
                    EstagioTeste = FimTeste;
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
                TimeoutFimTeste = 45000; //Seta para mostrar o resultado do teste somente por 60 seg. no display ap?s o teste terminar
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
                    AlteraEstadoReles(PlacaRele_0, RL_Aciona_Gravadores, RL_Aciona_Gravadores);
                    EstagioTeste = Finaliza_Testes; //Finaliza o teste para mostrar os defeitos no display
                    TimeoutFimTeste = 60000; //Seta para mostrar o resultado do teste somente por 60 seg. no display ap?s o teste terminar
                    TimeOutDelay = 200;
                }
                break;

            case ExibeResultadoportempo:
                TimeOutDelay = 100;
                TestTimeout = 4; //Mostra o Resultado por 8 segundos	
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
                        AlteraEstadoReles(PlacaRele_0, RL_Aciona_Gravadores, RL_Aciona_Gravadores);
                        EstagioTeste = Finaliza_Testes;
                        TimeoutFimTeste = 60000; //Para mostrar o resultado do teste somente por 60 seg. no display ap?s o teste terminar
                        TimeOutDelay = 200;
                    }
                }
                break;

            case Finaliza_Testes:
                if (TimeOutDelay == 0) {
                    AlteraEstadoReles(PlacaRele_0, RL_Aciona_Gravadores, 0);
                    EmTeste = 0;
                    FinalizaTesteFlag = 1;
                    IniciaTesteFlag = 0;

                    if ((DefeitoPlaca1 == 0)&&(PosicaoPlaca1 == 1)&&(Placa1[8] == 1)) {
                        Counter++; //Incrementa 1 se teste OK                
                    } else {
                        Counter_Nok++; //Incrementa 1 se teste N?o OK
                    }

                    if ((DefeitoPlaca2 == 0)&&(PosicaoPlaca2 == 1)&&(Placa2[8] == 1)) {
                        Counter++; //Incrementa 1 se teste OK
                    } else {
                        Counter_Nok++; //Incrementa 1 se teste N?o OK
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

#include "define.h"
#include "global_vars.h"


void VerificaTeclas(void)
{
	int Count;
	if(LeTeclasDelay==0)
	{
		LeTeclasDelay=1;
		TeclaPressionada=EstadoTeclas();
        
        if ((!EmTeste)&&(!FinalizaTesteFlag)&&(!Counter))
        {
            SendTextMessage(2, 0, MsgEnterIniciar);
            SendTextMessage(3, 0, MsgImportantelinha3);
            SendProductName();
            ExibeContador(); 
        }

        if(((TeclaPressionada & 0x01)==0)&&(!EmTeste))   //Chave NF
        {
			IniciaTesteFlag=1;
            TimeoutFimTeste = 0;
            ResultTimeoutFlag = 0;
        }
		if((TeclaPressionada & 0x02)==0)  //Chave NF
		{
			if(EmTeste)
			{
                    FinalizaTesteFlag=1;
                    IniciaTesteFlag=0;
                    ResultTimeoutFlag=2; // Para não mostrar nem a mensagem Erro e nem Teste OK ao resetar durante o Teste
                    SendTextMessage(4, 0, MsgTesteAbortado);
			}
			else
			{
				LimpaDisplay();
				for(Count=0;Count<64;Count++)
					MsgToShowBuffer[Count]=0;
                    MsgToShowPtr_RD=0;
                    MsgToShowPtr_WR=0;
			
				for(Count=0;Count<12;Count++)
					bus_fail_counter[Count]=0;
                                
                DesligaReles(PlacaRele_0);
				SendProductName();
                ExibeContador(); 
			}
		} 
	}
 }

void IniciaTeste(void)
{
	int Count;
	if((IniciaTesteFlag)&&(IniciaTesteDelay==0))
	switch(IniciaTesteState)
	{
		case 0:
			LimpaDisplay();
			for(Count=0;Count<64;Count++)
				MsgToShowBuffer[Count]=0;
                MsgToShowPtr_RD=0;
                MsgToShowPtr_WR=0;
		
			for(Count=0;Count<12;Count++)
				bus_fail_counter[Count]=0;
			
            SendProductName();
            EmiteBipe(5,2);
            ExibeContador(); 
			DesligaReles(PlacaRele_0);
            DesligaReles(PlacaRele_1);
			AlteraEstadoReles(PlacaRele_3,LigaTrava, LigaTrava);		// liga trava da Jiga                   
			IniciaTesteDelay=500;
			IniciaTesteState++;
		break;
        
		case 1:
            AlteraEstadoReles(PlacaRele_0, RL_Comut_CargaBateria_Placa1, 0);		//Desliga carga na bateria
            AlteraEstadoReles(PlacaRele_0, RL_Comut_CargaBateria_Placa2, 0);		//Desliga carga na bateria
			AlteraEstadoReles(PlacaRele_3,SobeGaveta, SobeGaveta);		// Sobe a gaveta
			IniciaTesteDelay=500;
			IniciaTesteState++;
		break;
        
		case 2:
			ResetAtv=0;
			TempoEmTeste=0;
			TesteOK=0;
			EstagioTeste=0;
			TestDelay=0;
			EmTeste=1;
			IniciaTesteFlag=0;
			IniciaTesteState=0;
		break;
        
		default:
			EstagioTeste=0;
			TestDelay=0;
			EmTeste=0;
			IniciaTesteFlag=0;
			IniciaTesteState=0;
		break;
	}
}

void FinalizaTeste(void)
{
	if((FinalizaTesteFlag)&&(FinalizaTesteDelay==0))
	switch(FinalizaTesteState)
	{
		case 0:
			TestDelay=0;
			EstagioTeste=0;
			IniciaTesteState=0;
			EmTeste=0;
            ExibeContador(); 
            SendProductName();
            
            if(TesteOK)
                {
                    MostraResultado();
                    DesligaReles(PlacaRele_0);
                    SendTextMessage(4, 0, MsgEnterIniciar);
                }
                else
                {
                    EmiteBipe(2,1);
                    SendTextMessage(1, 0, MsgTesteErro);
                }
            
			AlteraEstadoReles(PlacaRele_3,SobeGaveta, 0x00);		// Desce a gaveta
			FinalizaTesteDelay=300;
			FinalizaTesteState++;
		break;
        
		case 1:
			AlteraEstadoReles(PlacaRele_3,LigaTrava, 0x00);		// Desliga trava da Jiga
			FinalizaTesteDelay=300;
			FinalizaTesteState++;		
		break;
        
		case 2:
			AlteraEstadoReles(PlacaRele_3,SobeTampa, SobeTampa);		// Liga pistão para subir a tampa
			FinalizaTesteDelay=300;
			FinalizaTesteState++;		
		break;
        
		case 3:
			AlteraEstadoReles(PlacaRele_3,SobeTampa, 0x00);		// Desliga pistão para subir a tampa
			FinalizaTesteState++;		
		break;
        
		default:
            ResultTimeoutFlag=0;
			TestDelay=0;
			EstagioTeste=0;
			EmTeste=0;
			FinalizaTesteFlag=0;
			FinalizaTesteState=0;
		break;
	}

}

void ResultTimeout(void)
{
    int Count;
    if(ResultTimeoutFlag == 1) //Flag setado na interrupção
    {  
        ResultTimeoutFlag=2;
        EmTeste=0;
        FinalizaTesteFlag=1;
        IniciaTesteFlag=0;
        
        LimpaDisplay();
        for(Count=0;Count<64;Count++)
            MsgToShowBuffer[Count]=0;
            MsgToShowPtr_RD=0;
            MsgToShowPtr_WR=0;

        for(Count=0;Count<=19;Count++)
            bus_fail_counter[Count]=0;

        SendProductName();
        DesligaReles(PlacaRele_0);             
        DesligaReles(PlacaRele_1);    
        ExibeContador(); 
    }
}
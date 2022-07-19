#include "define.h"
#include "global_vars.h"


void VerificaTeclas(void)
{
	int Count;
	if(LeTeclasDelay==0)
	{
		LeTeclasDelay=1;
		TeclaPressionada=EstadoTeclas();
           
        if ((EmTeste==0)&&(FinalizaTesteFlag==0))
        {
            SendTextMessage(2, 0, MsgEnterIniciar);
            ExibeContador(); 
            SendProductName();
        }    
        
        if ((EmTeste==0)&&(FinalizaTesteFlag==0)&&(Counter==0))
        {
            SendTextMessage(2, 0, MsgEnterIniciar);
            SendTextMessage(3, 0, MsgImportantelinha3);
            SendProductName();
            ExibeContador(); 
        }
        
        if(((TeclaPressionada & 0x01)==0)&&(EmTeste==0))   //Chave NF
        {
			IniciaTesteFlag=1;
            TimeoutFimTeste = 0;
            ResultTimeoutFlag = 0;
        }
		if((TeclaPressionada & 0x02)==0)  //Chave NF
		{
			if(EmTeste==1) {
                LimpaDisplay();
                StatusGrava = 0;
                FinalizaTesteFlag=1;
                IniciaTesteFlag=0;
                ResultTimeoutFlag=2; // Para não mostrar nem a mensagem Erro e nem Teste OK ao resetar durante o Teste
                SendTextMessage(4, 0, MsgTesteAbortado);
                Delay_ms(500);
                SendTextMessage(4, 0, MsgEmBranco);
       		}
			else {
	            SendTextMessage(2, 0, MsgEmBranco);
                SendTextMessage(3, 0, MsgTesteAbortado);
                Delay_ms(500);
                LimpaDisplay();
				for(Count=0;Count<64;Count++)
					MsgToShowBuffer[Count]=0;
                    MsgToShowPtr_RD=0;
                    MsgToShowPtr_WR=0;
			
				for(Count=0;Count<12;Count++)
					bus_fail_counter[Count]=0;
                                
                DesligaReles(PlacaRele_0);
                DesligaReles(PlacaRele_1);
                SendProductName();
                ExibeContador(); 
            }
		} 
	}
 }

void IniciaTeste(void)
{
	int Count;
	if((IniciaTesteFlag==1)&&(IniciaTesteDelay==0))
	switch(IniciaTesteState)
	{
		case 0:
			LimpaDisplay();
            SendTextMessage(2, 0, MsgInicializandoPlacas);
            SendTextMessage(3, 0, MsgEmBranco);
            SendTextMessage(4, 0, MsgEmBranco);
			for(Count=0;Count<64;Count++)
				MsgToShowBuffer[Count]=0;
                MsgToShowPtr_RD=0;
                MsgToShowPtr_WR=0;
		
			for(Count=0;Count<12;Count++)
				bus_fail_counter[Count]=0;
                
            EmiteBipe(5,2);
            SendProductName();
            ExibeContador();                   
            DesligaReles(PlacaRele_0);
            DesligaReles(PlacaRele_1);
			AlteraEstadoReles(PlacaRele_3,LigaTrava, LigaTrava);		                
			IniciaTesteDelay=500;
			IniciaTesteState++;
		break;
        
		case 1:
            AlteraEstadoReles(PlacaRele_0, RL_Comut_CargaBateria_Placa1, 0);		
            AlteraEstadoReles(PlacaRele_0, RL_Comut_CargaBateria_Placa2, 0);		
			AlteraEstadoReles(PlacaRele_3,SobeGaveta, SobeGaveta);		
			IniciaTesteDelay=500;
			IniciaTesteState++;
		break;
        
		case 2:
			ResetAtv=0;
			TempoEmTeste=0;
			TesteOK=0;
			EstagioTeste=0;
			TestDelay=0;
            TimeOutDelay=0;
			EmTeste=1;
			IniciaTesteFlag=0;
			IniciaTesteState=0;
		break;
        
		default:
			EstagioTeste=0;
			TestDelay=0;
            TimeOutDelay=0;
			EmTeste=0;
			IniciaTesteFlag=0;
			IniciaTesteState=0;
		break;
	}
}

void FinalizaTeste(void)
{
	if((FinalizaTesteFlag==1)&&(FinalizaTesteDelay==0))
	switch(FinalizaTesteState)
	{
		case 0:
			TestDelay=0;
			EstagioTeste=0;
			IniciaTesteState=0;
			EmTeste=0;

            if(TesteOK==1)
                {
                    ExibeContador(); 
                    SendProductName();
                }
                else
                {
                    EmiteBipe(2,1);
                    SendTextMessage(1, 0, MsgTesteErro);
                }
            
			AlteraEstadoReles(PlacaRele_3,SobeGaveta, 0);
			FinalizaTesteDelay=200;
			FinalizaTesteState++;
            DesligaReles(PlacaRele_0);             
            DesligaReles(PlacaRele_1);   
            DesligaReles(PlacaRele_2); 
		break;
        
		case 1:
			AlteraEstadoReles(PlacaRele_3,LigaTrava, 0);
			FinalizaTesteDelay=200;
			FinalizaTesteState++;		
		break;
        
		case 2:
			AlteraEstadoReles(PlacaRele_3,SobeTampa, SobeTampa);
			FinalizaTesteDelay=200;
			FinalizaTesteState++;		
		break;
        
		case 3:
			AlteraEstadoReles(PlacaRele_3,SobeTampa, 0);
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

        DesligaReles(PlacaRele_0);             
        DesligaReles(PlacaRele_1);   
        DesligaReles(PlacaRele_2); 
        DesligaReles(PlacaRele_3);   
        ExibeContador(); 
        SendProductName();
    }
}
#include "define.h"
#include "global_vars.h"

static int Count5ms, Count100ms, Count500ms, Count1s, Count2s, Count1ms;

void Delay_ms(int time)
{
	delay=time;
	while(delay);
}


void __attribute__((__interrupt__, auto_psv)) _T5Interrupt( void )		//interrupução 1ms
{
	Count5ms++;
	if(Count5ms>=5)
	{
		Count5ms=0;
		VerifyPresentBusDevicesFlag=0;
	}
	Count100ms++;
	if(Count100ms>=100)
	{
		Count100ms=0;
		LeTeclasDelay=0;
	}

    Count500ms++;
	if(Count500ms>=500)
	{
		Count500ms=0;
		TempoEmTeste++;
	}
    
	Count1s++;
	if(Count1s>=1000)
	{
		Count1s=0;
        if(TestTimeout>0)
			TestTimeout--;
	}
    
    Count1ms++;
	if(Count1ms>=1)
	{
		Count1ms=0;
        if(TimeOutDelay)
			TimeOutDelay--;
        
        if(TimeOutGrava)
			TimeOutGrava--;
	}

	Count2s++;
	if(Count2s>=2000)
	{
		Count2s=0;
		MsgToShowDelay=0;
	}
	

	if(OnOffRelay_msDelay>0)
		OnOffRelay_msDelay--;

	if(OffOnRelay_msDelay>0)
		OffOnRelay_msDelay--;
	
	if((TestDelay>0)&&(OnOffRelay_msDelay==0)&&(OffOnRelay_msDelay==0))
		TestDelay--;

	if(IniciaTesteDelay>0)
		IniciaTesteDelay--;

	if(FinalizaTesteDelay>0)
		FinalizaTesteDelay--;
    
     if(TimeoutFimTeste>0) //Define quanto tempo irá mostrar o resultado no display após fim do teste
    {
        TimeoutFimTeste--;
        if(TimeoutFimTeste == 0)
        {
            ResultTimeoutFlag = 0; //Flag da função ResultTimeout 
        }
    }
	
	if(delay>0)
		delay--;

	
	IFS1bits.T5IF = 0;       // reset Timer 5 interrupt flag
}

void __attribute__((__interrupt__,auto_psv)) _T1Interrupt( void )
{
    TMR1=0x0000;
	BUS_Proc();


    IFS0bits.T1IF = 0;		// reset T1IF flag	NSTDIS
}

/********************************************************************/
/*  																*/
/* Nome do arquivo: main.c											*/
/* 																	*/
/* Versão:	1.0.0 													*/
/*            Intelbras S/A.										*/
/*                                                           		*/
/* Autor:	João Antonio dos Santos Filho.							*/
/*                                                                  */
/* Função:  														*/
/*          		                                             	*/
/********************************************************************/

#define x
#include "define.h"
#include "global_vars.h"


_CONFIG2(	IESO_ON &
			FNOSC_PRIPLL &
			FCKSM_CSECME &
			OSCIOFNC_OFF &
			IOL1WAY_OFF &
			I2C1SEL_PRI &
			POSCMOD_HS
		);

_CONFIG1(	JTAGEN_OFF &
			GCP_ON &	
			GWRP_OFF &
			BKBUG_OFF & 
			ICS_PGx3 &
			FWDTEN_OFF & // Função que inicia o Whatdog, nesse caso está desligado o mesmo
			WINDIS_OFF & 
			FWPSA_PR128 //&
			//WDTPS_PS2048 // Preset do WhatDog
		);
			

//void ClrWdtimer(){
//    __asm__("CLRWDT");
//}

/***********************************************************************/
/* -------------------------- main function ---------------------------*/
int main(void)
{
	CLKDIV=0;
	TRISA=TRISA_init;
	TRISB=TRISB_init;
	TRISC=TRISC_init;
	
	LATA=0x00;
	LATB=0x00;
	LATC=0x00;
    
//////////////////interrupção pelo timer 5 (1 ms)/////////////////
	T5CON = 0x0000;             // Timer5 off
	T5CONbits.TCKPS = 0;      	//
	PR5 = 0x4000;               // initialize Timer5 period register
	TMR5 = 0x0000;              // zero out Timer5 counter

	IFS1bits.T5IF = 0;          // reset flag
	IEC1bits.T5IE = 1;          // enable T5 interrupt
	IPC7bits.T5IP = 4;          // set Timer5 interrupt priority to level 4

	T5CONbits.TON = 1;          // enable Timer5


//////////////////// interrupção pelo timer 1//////////////////////
	T1CON = 0x0000;			// Timer1 off
	T1CONbits.TCKPS = 0;	//
	PR1 = 800;				// initialize Timer1 period register
	TMR1 = 0x0000;			// zero out Timer1 counter

    IFS0bits.T1IF = 0;		// reset T1IF flag	NSTDIS
    IEC0bits.T1IE=1;		//Timer1 Interrupt Enable
    IPC0bits.T1IP=7;		//Timer1 Interrupt Priority bits Interrupt is priority 7 (highest priority interrupt)

	T1CONbits.TON=1;		//Starts 16-bit Timer1


	full_recieved=1;
/***********************************************************************/
/* ---------------Inicialização UART1 RS-485 --------------------------*/

	RPINR18bits.U1RXR = 20;			// U1RX para RP20 pino 37
	RPOR10bits.RP21R = 3;			// RP21 para U1TX pino 38

	U1MODE = 0X0000;				// UART habilitada, idle state rx=1, BRGH=0(low speed), sem paridade, 1 stop bit
	U1BRG = 16;	 				// baud rate de 9600 com bit BRGH=0
	U1MODEbits.UARTEN=TRUE;			// habilita a uart
	U1STAbits.UTXEN = TRUE;			// habilita  transmissão

	RS485_DIR=true;
	Delay_ms(1000); 
    ResultTimeoutFlag = 0;      // Flag da função ResultTimeout
    StatusGr[0] = 0;
    StatusGr[1] = 0;
    LimpaDisplay();
    
    ExibeContador();
  
//    Counter = RCON;
//    
//    ExibeContador();
//    if (RCON != 131){
//        while (1);
//    }
        	
	while(1)
	{
		//ClrWdtimer();
		RotinaDeTeste();			// Rotina de teste específica para cada produto
        if (!((Count >= 11) && (StatusGr != 0))){  //DURANTE A GRAVAÇÃO NÃO FAZ TESTE DE COMUNICAÇÃO COM NENHUMA PLACA DE JIGA QUE ESTÁ PRESENTE NO SISTEMA
            VerifyPresentBusDevices();	// Verifica se todos os dispositivos selecionados estão presentes
		}
        VerificaTeclas();			// Verifica se alguma tecla foi pressionada na placa display e toma a ação correspondente
		ShowErrorMessages();		// exibe sequencialmente as mensagens de Erro geradas
		IniciaTeste();	
        ResultTimeout();            // Volta a jiga à condição inicial após xx segundos do fim do teste				
		FinalizaTeste();
	}
}


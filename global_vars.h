//Arquivo de definições de variaveis
#ifdef	x
	#define Global
#else
	#define Global extern
#endif
	
Global unsigned char bus_rx_buffer[120];
Global unsigned char bus_tx_buffer[120];
Global unsigned char versao[30];
Global unsigned char BUS_CRC;

Global unsigned char board_type;
Global unsigned char board_type_recieved;
Global unsigned char addr_slave;
Global unsigned char addr_recieved;
Global unsigned char send_msg_state;
Global unsigned char comand;

Global unsigned char rx_count;
Global unsigned char tx_count;
Global unsigned char num_bytes;

Global unsigned char BUS_ACK;
Global unsigned char full_recieved;
Global unsigned char chave_S1_acionada;
Global unsigned char chave_S2_acionada;
Global unsigned char chave_S3_acionada;
Global unsigned char flag_chave;
Global unsigned char time_adc;
Global unsigned char temp;
Global unsigned char chaves_old;
Global unsigned int StatusGr[8];

Global unsigned int BUS_timeout;
Global unsigned int loop_query;
Global unsigned int mseg_temp;
Global unsigned int ADCValue;
Global unsigned int bus_fail_counter[12],delay;

void delay_ms(unsigned int);
void le_tecla(void);
void unlock_rtcc(void);
void init_rtcc(void);
void init_uart(void);
void DisplayTime(char hours, char minutes, char seconds);
void DisplayDate(char day, char month, char year);
void set_date_time(void);
extern void BUS_Proc(void);
void emite_BIP(char bip,char qtd_bip);


Global union
{ 
	unsigned char as_char;
	struct
	{
		unsigned	_query	: 1;	// BIP ligado
//		unsigned	_bus	: 1;	//
//		unsigned		: 1;	//
//		unsigned		: 1;	//
//		unsigned		: 1;	//
//		unsigned		: 1;	//
//		unsigned		: 1;	//
		unsigned		: 7;	//
	};
}_flags;
#define status_flag		_flags.as_byte
#define flag_query		_flags._query
//#define status_bus		_flags._bus

//////////////// reles //////////////////
Global unsigned int ErroTesteReles;
Global unsigned int IniciaTesteReles;
Global unsigned int DelayTesteReles;

///////////// Rotina de teste ///////////
Global unsigned int ResetAtv;		// indica central estava aitvada no inicio do teste e ocorreu reset do teste
Global unsigned int TempoEmTeste;	// a quanto tempo o teste está sendo executado
Global unsigned int EstagioTeste;	// indica o estágio atual do teste
Global unsigned int EmTeste;	// se estiver setado indica que o teste está em andamento
Global unsigned int TesteOK;	// se o teste foi finalizado com sucesso
Global unsigned int TestDelay;	// delay entre os estágios do teste em milisegundos
Global unsigned int TeclaPressionada;
Global unsigned int VerifyPresentBusDevicesFlag;
Global unsigned int LeTeclasDelay;
Global unsigned int IniciaTesteFlag;
Global unsigned int IniciaTesteState;
Global unsigned int IniciaTesteDelay;
Global unsigned int FinalizaTesteFlag;
Global unsigned int FinalizaTesteState;
Global unsigned int FinalizaTesteDelay;
Global unsigned int TestTimeout;

Global unsigned int ResultTimeoutFlag;
Global unsigned int TimeoutFimTeste;
Global unsigned int Placa;
Global unsigned char CalibraJiga;    //Indica se a jiga vai entrar em modo de teste normal ou de verificação de jiga p/ calibração
Global unsigned char GravaFWTeste;
Global unsigned char RepeteGravacao; 
Global unsigned int LiberaTestePlaca1;
Global unsigned int LiberaTestePlaca2; 

////////////// exibição do buffer de mensagens////////////
Global unsigned char MsgToShowBuffer[100];
Global unsigned char MsgToShowPtr_RD;
Global unsigned char MsgToShowPtr_WR;
Global unsigned char MsgToShowDelay;
Global unsigned char IndexMsgTimeOut;
Global unsigned int TemErro;
Global unsigned int TimeOutDelay;	// contador para decrementar o tempo entre um teste e outro
Global unsigned int TimeOutGrava;	// contador para decrementar o tempo entre um teste e outro
Global unsigned int ContadorErro;	// contador para decrementar o tempo entre um teste e outro
//int Messages[3];

///////////////// Apoio ao teste //////////////////

Global union
{
	unsigned int as_int;
	struct
	{
		unsigned	_OnOffRelayFlag	: 1;	// função para ligar e desligar um reles está em execução
		unsigned	_OffOnRelayFlag	: 1;	// função para desligar e ligar um reles está em execução
	}
}_ApoioFlags;

#define	ApoioFlags			_ApoioFlags.as_int
#define	OnOffRelayFlag		_ApoioFlags._OnOffRelayFlag
#define	OffOnRelayFlag		_ApoioFlags._OffOnRelayFlag
#define UNUSED(x) ((void)(x))

Global unsigned int OnOffRelay_msDelay;
Global unsigned int OffOnRelay_msDelay;
Global unsigned int Count;
Global unsigned int Counter;               //Variável Contadora OK
Global unsigned int Counter_Nok;            //Variável Contadora Não 



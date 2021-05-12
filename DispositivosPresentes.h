
/********************************************************************/
/* Nome do arquivo: DispositivosPresentes.h							*/
/* 																	*/
/* Versão:	1.0.0 													*/
/*            Intelbras S/A.										*/
/*                                                           		*/
/* Autor:	Augusto Cezar Medeiros dos Santos						*/
/*                                                                  */
/* Função: Definição dos dispositivos de barramento necessários 	*/
/* para o funcionamento da JIGA									 	*/
/*          		                                             	*/
/********************************************************************/

// identifica se a placa deve estar presente ou não 
// 0=Placa ausente
// 1=Placa presente
const __attribute__((space(auto_psv)))
unsigned char PresentDevices[19]=
{	
	0,	// Placa RELE 0 presente
	0,	// Placa RELE 1 presente
	0,	// Placa RELE 2 presente
	0,	// Placa RELE 3 presente	//( Obs. A Placa RELE 3 sempre deve estar presente em Jigas que utilizam sistema pneumático )
	0,	// Placa A/D 0 presente 
	0,	// Placa A/D 1 presente
	0,	// Placa A/D 2 presente
	0,	// Placa A/D 3 presente
	0,	// Placa telefonia presente
	0,	// Placa barramento presente
	1,	// Placa Display presente
	1,	// Placa gravador 0 presente
	1,	// Placa gravador 1 presente
	0,	// Placa gravador 2 presente
	0,	// Placa gravador 3 presente
	0,	// Placa gravador 4 presente
	0,	// Placa gravador 5 presente
	0,	// Placa gravador 6 presente
	0,	// Placa gravador 7 presente
};

// Tipos de placas que serão transmitidos no barramento
const __attribute__((space(auto_psv)))
unsigned char Type[19]=
{	
	'R',	// Placa RELE 0
	'R',	// Placa RELE 1
	'R',	// Placa RELE 2
	'R',	// Placa RELE 3
	'A',	// Placa A/D 0
	'A',	// Placa A/D 1
	'A',	// Placa A/D 2
	'A',	// Placa A/D 3
	'T',	// Placa telefonia
	'B',	// Placa barramento
	'D',	// Placa Display
	'G',	// Placa gravador 0
	'G',	// Placa gravador 1
	'G',	// Placa gravador 2
	'G',	// Placa gravador 3
	'G',	// Placa gravador 4
	'G',	// Placa gravador 5
	'G',	// Placa gravador 6
	'G',	// Placa gravador 7
};

// Endereços de placas que serão transmitidos no barramento
const __attribute__((space(auto_psv)))
unsigned char Address[19]=
{
	0,	// Placa RELE 0
	1,	// Placa RELE 1
	2,	// Placa RELE 2
	3,	// Placa RELE 3
	0,	// Placa A/D 0
	1,	// Placa A/D 1
	2,	// Placa A/D 2
	3,	// Placa A/D 3
	0,	// Placa telefonia
	0,	// Placa barramento
	0,	// Placa Display
	0,	// Placa gravador 0
	1,	// Placa gravador 1
	2,	// Placa gravador 2
	3,	// Placa gravador 3
	4,	// Placa gravador 4
	5,	// Placa gravador 5
	6,	// Placa gravador 6
	7,	// Placa gravador 7
};


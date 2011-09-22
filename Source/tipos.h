/**

20/set/2011

Controla os tipos de dados que o banco aceita.


todo: tudo (ler, escrever).



*/



#include <time.h>
#include "byteio.h"
#include "data.h"


typedef enum {

	ubyte,
	sbyte,
	ushint,
	sshint,
	uint,
	sint,
	ulong,
	slong,
	singleprec, //floating point de precisão simples.
	doubleprec, //floating point de precisão dupla.
	data,       //data do calendario gregoriano.
	horario,    //milisegundos desde o início do dia.
	timestamp,  //tempo retornado pelo sistema.

	varchar_utf8,
	fixchar_utf8,
	varchar_utf16,
	fixchar_utf16,
	varchar_utf32,
	fixchar_utf32

}TIPO;

#define is_var(t) (t == varchar_utf8 || t == varchar_utf16 || \
		 t == varchar_utf32)

#define is_fix(t)  (t == fixchar_utf8 || t == fixchar_utf16 || \
		 t == fixchar_utf32)



/** Retorna o tamanho do tipo.
*/
size_t get_tam(TIPO t) {


	switch (t) {

	case ubyte: return sizeof(unsigned char);
	case sbyte: return sizeof(char);

	case ushint: return sizeof(unsigned short int);
	case sshint: return sizeof(short int);

	case uint: return sizeof(unsigned int);
	case sint: return sizeof(int);

	case ulong: return sizeof(unsigned long);
	case slong: return sizeof(long);

	case singleprec: return sizeof(float);
	case doubleprec: return sizeof(double);

	case data: return sizeof(DATA_GREG);
	case horario: return sizeof(unsigned int);
	case timestamp: return sizeof(time_t);

	case varchar_utf8: return 1;
	case fixchar_utf8: return 1;
	case varchar_utf16: return 2;
	case fixchar_utf16: return 2;
	case varchar_utf32: return 4;
	case fixchar_utf32: return 4;
	}
}



void ler_string(FILE *f, void *v, TIPO t, int n) {

	int c, pos;

	for (c = 0; c < n; c++) {
		pos = (v + (c * tam));
		get_n_bytes(f, pos, tam);
		if (*pos == 0 && is_var(t)) break;
	}
}


void ler_valor(FILE *f, void *v, TIPO t, int n) {

	switch (t) {

	case data: {
		*v = (data) new data(f);
		break;
	}
	case varchar_utf8: //
	case varchar_utf16: //
	case varchar_utf32: //
	case fixchar_utf8: //
	case fixchar_utf16: //
	case fixchar_utf32: {//
		ler_string(f, v, t, n);
		break;
	}
	default: get_n_bytes(f, v,get_tam(t));

	}
}




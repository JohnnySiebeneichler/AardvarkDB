/**

20/set/2011

Controla os tipos de dados que o banco aceita.


todo: tudo (ler, escrever).



*/
#ifndef TIPOS_H
#define TIPOS_H

#include <time.h>
#include "byteio.h"
#include "data.h"


typedef enum {

	ubyte,
	sbyte,
	ushint,
	sshint,
	_uint, /* uint and ulong have already been defined in <sys/types.h> */
	sint,
	_ulong,
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
size_t get_tam(TIPO t);



void ler_valor(FILE *f, void *v, TIPO t, int n);

#endif

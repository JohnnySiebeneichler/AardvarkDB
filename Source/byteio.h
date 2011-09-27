/**

21/set/2011

Faz input e output diretamente em bytes.

*/
#ifndef BYTEIO_H
#define BYTEIO_H

#include <cstdio>
#include <iostream>
#include "erros.h"


/** Lê n bytes do arquivo f e coloca no "vetor". Na prática o vetor
	pode ser uma variável. Por exemplo para ler um int (4 bytes),
	chama-se get_n_bytes(f, (void *) &the_int, 4);

ERR get_n_bytes(FILE *f, void *v, int n) {

	check_file(f);
	check_ptr(v);

	int c;
	for (c = 0; c < n; c++) v[c] = (char) fgetc(f);
	return SUCESSO;
}*/
//substituir por fwrite




ERR put_n_bytes(FILE *f, void *v, int n) {

	check_file(f);
	check_ptr(v);

	int c, *arr = (int *) v;
	for (c = 0; c < n; c++) fputc(arr[c], f);
	return SUCESSO;
}

ERR get_n_bytes(FILE *f, void *v, int n) {

	/* TODO */
	std::clog << "get_n_bytes: not implemented" << std::endl;
	return ERR_NOT_IMPL;
}
#endif


#include "byteio.h"


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

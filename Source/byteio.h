/**

21/set/2011

Faz input e output diretamente em bytes.

*/





/** Lê n bytes do arquivo f e coloca no "vetor". Na prática o vetor
	pode ser uma variável. Por exemplo para ler um int (4 bytes),
	chama-se get_n_bytes(f, (void *) &the_int, 4);
*/
ERR get_n_bytes(FILE *f, void *v, int n) {

	check_file(f);
	check_ptr(v);

	int c;
	for (c = 0; c < n; c++) v[c] = (char) fgetc(f);
	return SUCESSO;
}

ERR put_n_bytes(FILE *f, void *v, int n) {

	check_file(f);
	check_ptr(v);

	int c;
	for (c = 0; c < n; c++) fputc(*v[c], f);
	return SUCESSO;
}

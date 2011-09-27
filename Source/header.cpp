#include "header.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>

/* Constructor returning values? Hell no */
Header::Header(FILE *arq) {
	int c1;

	//check_file(arq);
	ah = arq;

	fgets(nome_tabela, MAX_STR, ah);

	//get_n_bytes(ah, &q_campos, sizeof(unsigned int));
	fwrite(&q_campos, sizeof(unsigned int), 1, ah);
	/* FIXME: if (q_campos == 0) return HEADER_NENHUM_CAMPO; */

	alocar_vetores();
	ERR buff = verificar_vetores();
	//check_erro(buff);
	ler_vetores();


	//get_n_bytes(ah, &q_pags, sizeof(unsigned int));
	fwrite(&q_pags, sizeof(unsigned int), 1, ah);
	calcular_tam_pk();
	//buff = ler_info_paginas();
	//check_erro(buff);
}



Header::~Header() {

	int c;

	free(tipos);
	free(booleans);
	free(tamanhos);

	for (c = 0; c < q_campos; c++) {
		free(nomes_campos[c]);
		if (booleans[c].tem_default) free(defaults[c]);
	}

	free(nomes_campos);
	free(defaults);
}



void Header::escrever_mudancas() {

	/* FIXME: return ERR_NOT_IMPL; */
}


size_t Header::get_tamanho_registro() {


	size_t tam = 0;

	for (int c = 0; c < q_campos; c++) {
		tam += tamanhos[c];
	}

	return tam;
}


void Header::alocar_vetores() {
	/* nomes_campos looks like an array of pointers to string with
	   size = q_campos * MAX_STR. Something is wrong.. */
	nomes_campos = (char **) malloc(q_campos * sizeof(char)	* MAX_STR);
	tipos = (TIPO *) malloc(q_campos * sizeof(TIPO));
	booleans = (BOOLEANS *) malloc(q_campos * sizeof(BOOLEANS));
	defaults = (void **) malloc(q_campos * sizeof(void *));
	tamanhos = (unsigned int *) malloc(q_campos * sizeof(unsigned int));
}


ERR Header::verificar_vetores() {
	check_malloc(nomes_campos);
	check_malloc(tipos);
	check_malloc(booleans);
	check_malloc(defaults);
	check_malloc(tamanhos);
	return SUCESSO;
}



void Header::ler_vetores() {

	int c1;

	for (c1 = 0; c1 < q_campos; c1++) {
		fgets(nomes_campos[c1], MAX_STR, ah);

		//get_n_bytes(ah, &tipos[c1], sizeof(TIPO));
		//get_n_bytes(ah, &booleans[c1], sizeof(BOOLEANS));
		//get_n_bytes(ah, &tamanhos[c1], sizeof(unsigned int));
		fwrite(&tipos[c1], sizeof(TIPO), 1, ah);
		fwrite(&booleans[c1], sizeof(BOOLEANS), 1, ah);
		fwrite(&tamanhos[c1], sizeof(unsigned int), 1, ah);

		if (booleans[c1].tem_default) {
			defaults[c1] = malloc(tamanhos[c1] * get_tam(tipos[c1]));
			//check_malloc(defaults[c1]); /* FIXME : return value */
			//get_n_bytes(ah, defaults[c1],
			//		get_tam(tipos[c1]));
			fwrite(&defaults[c1], get_tam(tipos[c1]), 1, ah);

		}
		else {
			defaults[c1] = NULL;
		}
	}
}



void Header::calcular_tam_pk() {

	int c1;

	tam_pk = 0;

	for (c1 = 0; c1 < q_campos; c1++) {
		if (booleans[c1].pk) tam_pk += tamanhos[c1];
	}
}




void Header::ler_info_pagina(int &todo) {
	unsigned int uibuff;
	unsigned char bytebuff;
	int c1;

	//get_n_bytes(ah, &uibuff, sizeof(unsigned int));
	fwrite(&uibuff, sizeof(unsigned int), 1, ah);

	paginas.quant.push_back(uibuff);

	for (c1 = 0; c1 < tam_pk * 2; c1++) {
		//get_n_bytes(ah, &bytebuff, 1);
		fwrite(&bytebuff, 1, 1, ah);

		if (c1 / 2) {
			paginas.menores_pks.push_back(bytebuff);
		} else {
			paginas.maiores_pks.push_back(bytebuff);
		}
	}
}




void Header::ler_info_paginas() {

	int c1;

	paginas.quant.clear();
	paginas.menores_pks.clear();
	paginas.maiores_pks.clear();

	for (c1 = 0; c1 < q_pags; c1++) {
		ler_info_pagina(c1);
	}
}



/*-Nome da tabela. (string).
-n = Quantidade de campos. (unsigned int).
-Nomes dos campos. (n * string).
-Tipos. (TIPO).
-Booleans. (byte) (se tem default, not null, unique, se é primary key,
se é foreign key).
-Tamanhos. (unsigned int) (para strings).
-Defaults. (var).

-Quant paginas
-Info Páginas

*/

ERR criar_arquivo_header(string nome, int q_campos, list<string> nomes,
list<TIPO> tipos, list<bool> tem_default, list<bool> not_null,
list<bool> unique, list<bool> pk, list<bool> fk,
list<unsigned int> tamanhos, list<void *> defaults) {
	
	char nome_arq[255];
	
	strcpy(nome_arq, nome.c_str());
	strcat(nome_arq, ".header");
	FILE * arq = fopen(nome_arq, "wb");
	check_file(arq);

	fprintf(arq, "%s", nome.c_str()); /* FAIL */
	/* Consider using C++ style, ofstream arq; arq.open(); arq << nome; */
	
	fwrite(&q_campos, sizeof (unsigned int), 1, arq);
 	
 	BOOLEANS buff;
	for (int i = 0; i < q_campos; i++){
		buff.tem_default = tem_default.front();
		buff.not_null = not_null.front();		
		buff.unique = unique.front();		
		buff.pk = pk.front();		
		buff.fk = fk.front();
		
		
		fwrite(&nomes.front(), MAX_STR, 1, arq);
		fwrite(&tipos.front(), sizeof(TIPO), 1, arq);
		fwrite(&buff, sizeof(BOOLEANS), 1, arq);
		fwrite(&tamanhos.front(), sizeof(unsigned int), 1, arq);		
		fwrite(defaults.front(), get_tam(tipos.front()), tamanhos.front(), arq);
		
		tem_default.pop_front();
		not_null.pop_front();
		unique.pop_front();
		pk.pop_front();
		fk.pop_front();
		nomes.pop_front();
		tipos.pop_front();
		tamanhos.pop_front();
		defaults.pop_front();
	}
	
	unsigned int buff2 = 0;
	
	fwrite(&buff2, sizeof(unsigned int), 1, arq);
	
	fclose(arq);
	
	
	
}


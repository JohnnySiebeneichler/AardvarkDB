#include "header.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>

Header::Header(FILE *arq, ERR *err) {
	int c1;

	set_file_err(arq, err);
	ah = arq;

	fgets(nome_tabela, MAX_STR, ah);

	fread(&q_campos, sizeof(unsigned int), 1, ah);

	alocar_vetores();
	ERR buff = verificar_vetores();
	set_erro_err(buff, err);
	ler_vetores();


	fread(&q_pags, sizeof(unsigned int), 1, ah);
	buff = calcular_offsets();
	set_erro_err(buff, err);
	calcular_tam_pk();
	buff = ler_info_paginas();
	set_erro_err(buff, err);
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

/*
	size_t tam = 0;

	for (int c = 0; c < q_campos; c++) {
		tam += tamanhos[c];
	}

	return tam;*/
	return tam;
}


void Header::alocar_vetores() {

	nomes_campos = (char **) malloc(q_campos * sizeof(char *));

	for (int c = 0; c < q_campos; c++) {
		nomes_campos[c] = (char *) malloc(sizeof(char) * MAX_STR);
	}

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

	for (int c = 0; c < q_campos; c++) {
		check_malloc(nomes_campos[c]);
	}

	return SUCESSO;
}



ERR Header::ler_vetores() {

	int c1;

	for (c1 = 0; c1 < q_campos; c1++) {

		fgets(nomes_campos[c1], MAX_STR, ah);
		fread(&tipos[c1], sizeof(TIPO), 1, ah);
		fread(&booleans[c1], sizeof(BOOLEANS), 1, ah);
		fread(&tamanhos[c1], sizeof(unsigned int), 1, ah);

		if (booleans[c1].tem_default) {
			defaults[c1] = (void *) malloc(tamanhos[c1] *
							get_tam(tipos[c1]));
			check_malloc(defaults[c1]);
			fread(&defaults[c1], get_tam(tipos[c1]), 1, ah);

		}
		else {
			defaults[c1] = NULL;
		}
	}
}



ERR Header::calcular_offsets() {


	tam = 0;
	for (int c = 0; c < q_campos; c++) {
		tam += tamanhos[c];
	}

	offsets = (unsigned int *) malloc(tam);
	check_malloc(offsets);

	offsets[0] = 0;

	for (int c = 1; c < q_campos; c++) {
		offsets[c] = offsets[c-1] + tamanhos[c] * get_tam(tipos[c]);
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

	fread(&uibuff, sizeof(unsigned int), 1, ah);

	paginas.quant.push_back(uibuff);

	for (c1 = 0; c1 < tam_pk * 2; c1++) {

		fread(&bytebuff, 1, 1, ah);

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


/*
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
	/* Consider using C++ style, ofstream arq; arq.open(); arq << nome;

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
		fwrite(defaults.front(), get_tam(tipos.front()),
			tamanhos.front(), arq);

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
*/


ERR criar_arquivo_header(string nome, int q_campos, list<string> nomes,
	list<TIPO> tipos, list<bool> tem_default, list<bool> not_null,
	list<bool> unique, list<bool> pk, list<bool> fk,
	list<unsigned int> tamanhos, list<void *> defaults,
	list<INFO_FK> info_fks) {


	char nome_arq[255];
	strcpy(nome_arq, nome.c_str());
	strcat(nome_arq, ".header");
	FILE *arq = fopen(nome_arq, "wb");
	check_file(arq);


	arq << nome << (char) 0 << q_campos;

	for (int c = 0; c < q_campos; c++) {
		add_elem_list(arq, nomes);
		add_elem_list(arq, tipos);
		add_booleans(arq, tem_default, not_null, unique, pk, fk);
		add_elem_list(arq, tamanhos);

		//defaults. duvido que esteja certo.
		arq << *(defaults.front());
		defaults.pop_front();
	}

	add_list(arq, info_fks);
	arq << (unsigned int) 0; //nenhuma página quando cria.
}


void add_booleans(FILE *arq, list tem_default, list not_null, list unique,
		list pk, list fk) {

	BOOLEANS buff;

	buff.tem_default = tem_default.front();
	buff.not_null = not_null.front();
	buff.unique = unique.front();
	buff.pk = pk.front();
	buff.fk = fk.front();

	arq << buff;

	tem_default.pop_front();
	not_null.pop_front();
	unique.pop_front();
	pk.pop_front();
	fk.pop_front();

}

//Colocar em fileutil.h depois
void add_elem_list(FILE *arq, list l) {

	arq << l.front();
	l.pop_front();
}

void add_list(FILE *arq, list l) {

	while (!l.empty) add_elem_list(arq, l);
}


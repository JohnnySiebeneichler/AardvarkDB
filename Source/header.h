/**

20/set/2011

Controla o arquivo de header das tabelas.


Formato do arquivo de header (strings 0-finalized):

-Nome da tabela. (string).
-n = Quantidade de campos. (unsigned int).
-Nomes dos campos. (n * string).
-Tipos. (TIPO).
-Booleans. (byte) (se tem default, not null, unique, se é primary key,
		se é foreign key).
-Tamanhos. (unsigned int) (para strings).
-Defaults. (var).

-Quant paginas
-Info Páginas


to do: escrever
separar .cpp dos .h



*/


#include <list>
#include "erros.h"
#include "tipos.h"

using namespace std;

#define MAX_STR 255



//armazena: 4 primeiros bits: tipo, próximos bits booleanos:
//se tem default, not_null, unique, primary_key e foreign key.
typedef union {

	bool tem_default : 1;
	bool not_null : 1;
	bool unique : 1;
	bool pk : 1;
	bool fk : 1;
}BOOLEANS;



//como o número total de bytes que a chave primária terá, a lista armazena-a
//como bytes (unsigned char), assim, seu tamanho deverá ser tam_pk vezes maior
//que o da lista quant.
typedef struct {

	list<unsigned int> quant;
	list<unsigned char> menores_pks;
	list<unsigned char> maiores_pks;

}INFO_PAGINAS;


class header {

	public:
	char nome_tabela[MAX_STR];
	unsigned int q_campos;
	char *nomes_campos[MAX_STR];
	TIPO *tipos;
	BOOLEANS *booleans;
	unsigned int *tamanhos;
	void **defaults;

	unsigned int q_pags;
	INFO_PAGINAS paginas;

	private:
	int tam_pk;
	FILE *ah;



	public:
	/** Lê um arquivo de header em uma estrutura de header.
		@param arq O arquivo de header.
		@return Identificador de erro.
	*/
	ERR header(FILE *arq) {

		int c1;

		check_file(arq);
		ah = arq;

		fgets(ah, nome_tabela, MAX_STR);

		get_n_bytes(ah, &q_campos, sizeof(unsigned int));
		if (q_campos == 0) return HEADER_NENHUM_CAMPO;

		alocar_vetores();
		ERR buff = verificar_vetores();
		check_erro(buff);
		ler_vetores();


		get_n_bytes(ah, &q_pags, sizeof(unsigned int));
		calcular_tam_pk();
		buff = ler_info_paginas();
		check_erro(buff);
	}



	/** Desaloca a memória alocada em uma header struct.
	*/
	void ~header() {
		return ERR_NOT_IMPL;
	}





	private:
	void alocar_vetores() {
		nomes_campos = (char **) malloc(q_campos * sizeof(char)
						* MAX_STR);
		tipos = (TIPO *) malloc(q_campos * sizeof(TIPO));
		booleans = (BOOLEANS *) malloc(q_campos * sizeof(BOOLEANS));
		defaults = (void *) malloc(q_campos * sizeof(void *));
		defaults = (void *) malloc(q_campos * sizeof(unsigned int));
	}

	ERR verificar_vetores() {
		check_malloc(nomes_campos);
		check_malloc(tipos);
		check_malloc(booleans);
		check_malloc(defaults);
		check_malloc(tamanhos);
		return SUCESSO;
	}

	void ler_vetores() {

		int c1;

		for (c1 = 0; c1 < q_campos; c1++) {
			fgets(ah, nomes_campos[c1], MAX_STR);
			//scanf("%u %u %u", &tipos[c1], &booleans[c1],
			//	&tamanhos[c1]);
			get_n_bytes(ah, &tipos[c1], sizeof(TIPO));
			get_n_bytes(ah, &booleans[c1], sizeof(BOOLEANS));
			get_n_bytes(ah, &tamanhos[c1], sizeof(unsigned int));

			if (booleans[c1].tem_default) {
				defaults[c1] = malloc(tamanhos[c1] *
							get_tam(tipos[c1]);
				check_malloc(defaults[c1]);
				get_n_bytes(ah, defaults[c1],
						get_tam(tipos[c1]));

			}
			else {
				defaults[c1] = NULL;
			}
		}
	}


	void calcular_tam_pk() {

		int c1;

		tam_pk = 0;

		for (c1 = 0; c1 < q_campos; c1++) {
			if (booleans[c1].pk) tam_pk += tamanhos[c1];
		}
	}



	void ler_info_pagina(int pos) {
		unsigned int uibuff;
		unsigned char bytebuff;
		int c1;

		get_n_bytes(ah, &uibuff, sizeof(unsigned int));
		paginas.quant.push_back(uibuff);

		for (c1 = 0; c1 < tam_pk * 2; c1++) {
			get_n_bytes(ah, &bytebuff, 1);

			if (c1 / 2) {
				paginas.menores.push_back(bytebuff);
			} else {
				paginas.maiores.push_back(bytebuff);
			}
		}
	}


	void ler_info_paginas() {

		int c1;

		paginas.quant.clear();
		paginas.menores_pks.clear();
		paginas.maiores_pks.clear();

		for (c1 = 0; c1 < q_pags; c1++) {
			ler_info_pagina(c1);
		}
	}






	void escrever_mudancas() {

	}
};




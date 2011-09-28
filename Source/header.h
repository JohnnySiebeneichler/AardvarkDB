/**

20/set/2011

Controla o arquivo de header das tabelas.


Formato do arquivo de header (strings 0-finalized):

-Nome da tabela. (string).
-n = Quantidade de campos. (unsigned int).

n {
	-Nomes dos campos. (string).
	-Tipos. (TIPO).
	-Booleans. (byte) (se tem default, not null, unique, se é primary key,
			se é foreign key).
	-Tamanhos. (unsigned int) (para strings).
	-Defaults. (var).
}

quant foreign_key {
	-Nome tabela referenciada.
	-Nome campo referenciado.
}

-Quant páginas
Quant páginas {
	-quant registros na página
	-menor pk da página
	-maior pk da página
}



*/

#ifndef HEADER_H
#define HEADER_H


#include <list>
#include "erros.h"
#include "tipos.h"

using namespace std;

#define MAX_STR 255



/** armazena booleanos: se tem default, not_null, unique, primary_key e
	foreign key.
*/
typedef union {

	bool tem_default : 1;
	bool not_null : 1;
	bool unique : 1;
	bool pk : 1;
	bool fk : 1;
}BOOLEANS;



/** Como o número total de bytes que a chave primária terá é variável, a lista
	armazena-a como bytes (unsigned char), assim, seu tamanho deverá ser
	tam_pk vezes maior que o da lista quant.
*/
typedef struct {

	list<unsigned int> quant;
	list<unsigned char> menores_pks;
	list<unsigned char> maiores_pks;

}INFO_PAGINAS;


/** Os dados de uma foreign key. Até eu achar uma classe boa para colocar vai a-
	qui mesmo. :-D
*/
typedef struct {
	string nome_tabela, nome_campo;
}INFO_FK;


class Header {


	public:
		char nome_tabela[MAX_STR];
		unsigned int q_campos;
		char **nomes_campos;
		TIPO *tipos;
		BOOLEANS *booleans;
		unsigned int *tamanhos;
		void **defaults;

		unsigned int q_pags;
		INFO_PAGINAS paginas;





		/** Lê um arquivo de header em uma estrutura de header.
			@param arq O arquivo de header.
			@param err Ponteiro para identificador de erro.
		*/
		Header(FILE *arq, ERR *err); // Constructor DO NOT have return value.



		/** Desaloca a memória alocada em uma header struct.
		*/
		~Header();





		/** Salva as mudanças no header.
		*/
		void escrever_mudancas();


		/** Retorna a quantidade de bits requerida por um registro.
		*/
		size_t get_tamanho_registro();





	private:
		int tam_pk;
		FILE *ah;

		//Offset de cada campo, para facilitar o acesso.
		unsigned int *offsets;

		//Quantidade total de bytes no banco.
		size_t tam;


		/** Aloca os vetores que armazenarão os dados do header.
		*/
		void alocar_vetores();



		/** Verifica se os vetores foram alocados corretamente.
		*/
		ERR verificar_vetores();



		/** Lê os valores das características das tuplas e armazena-os
			nos vetores.
		*/
		ERR ler_vetores();



		/** Calcular a quantidade total de bytes por registro e o
			offset de cada coluna.
		*/
		ERR calcular_offsets();


		/** Calcula a quantidade total de bytes que serão necessários
			para armazenar todos dados da chave primária.
		*/
		void calcular_tam_pk();


		/** Lê o dado de um único conjunto de informação sobre uma pá-
			gina que consiste de: quantidade de registros na pági-
			na, menor chave primária, e maior chave primária).
		*/
		void ler_info_pagina(int &todo);





		/** Iterador para ler todos info_pagina no arquivo.
		*/
		void ler_info_paginas();


};




/** Esta função irá criar o arquivo de header das tabelas do banco de dados com
	o formato especificado no cabeçalho deste arquivo.
*/
ERR criar_arquivo_header(string nome, int q_campos, list<string> nomes,
	list<TIPO> tipos, list<bool> tem_default, list<bool> not_null,
	list<bool> unique, list<bool> pk, list<bool> fk,
	list<unsigned int> tamanhos, list<void *> defaults,
	list<INFO_FK> info_fks);






#endif

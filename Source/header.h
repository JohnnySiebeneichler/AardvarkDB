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


class Header {


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


		/** Lê um arquivo de header em uma estrutura de header.
			@param arq O arquivo de header.
			@return Identificador de erro.
		*/
		ERR Header(FILE *arq);



		/** Desaloca a memória alocada em uma header struct.
		*/
		void ~Header();





		/** Salva as mudanças no header.
		*/
		void escrever_mudancas();


		/** Retorna a quantidade de bits requerida por um registro.
		*/
		size_t get_tamanho_registro();





	private:
		int tam_pk;
		FILE *ah;


		/** Aloca os vetores que armazenarão os dados do header.
		*/
		void alocar_vetores();



		/** Verifica se os vetores foram alocados corretamente.
		*/
		ERR verificar_vetores();



		/** Lê os valores das características das tuplas e armazena-os
			nos vetores.
		*/
		void ler_vetores();




		/** Calcula a quantidade total de bytes que serão necessários
			para armazenar todos dados da chave primária.
		*/
		void calcular_tam_pk();


		/** Lê o dado de um único conjunto de informação sobre uma pá-
			gina que consiste de: quantidade de registros na pági-
			na, menor chave primária, e maior chave primária).
		*/
		void ler_info_pagina();





		/** Iterador para ler todos info_pagina no arquivo.
		*/
		void ler_info_paginas();


};



/**
 * Esta função irá criar o arquivo de header das tabelas do
 * banco de dados com o seguinte formato:
 * 
 * -Nome da tabela. (string).
 * -n = Quantidade de campos. (unsigned int).
 * -Nomes dos campos. (n * string).
 * -Tipos. (TIPO).
 * -Booleans. (byte) (se tem default, not null, unique, se é primary key,
		se é foreign key).
 * -Tamanhos. (unsigned int) (para strings).
 * -Defaults. (var).
 * 
 * Para os defaults, colunas sem default tem um ponteiro null.
 */
ERR criar_arquivo_header(string nome, int q_campos, list<string> nomes,
	list<TIPO> tipos, list<bool> tem_default, list<bool> not_null,
	list<bool> unique, list<bool> pk, list<bool> fk,
	list<unsigned int> tamanhos, list<void *> defaults);




#endif

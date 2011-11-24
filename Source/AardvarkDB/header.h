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
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "erros.h"
#include "tipos.h"
#include "coluna.h"

using namespace std;

#define MAX_STR 255



/** armazena booleanos: se tem default, not_null, unique, primary_key e
	foreign key.
*/




/** Como o número total de bytes que a chave primária terá é variável, a lista
	armazena-a como bytes (unsigned char), assim, seu tamanho deverá ser
	tam_pk vezes maior que o da lista quant.
*/
typedef struct {
	string nome;
	int quant;
	int tam;
	void *pk_inicial;
}INFO_PAGINA;


typedef struct {
	string nome_tabela, nome_campo;
}INFO_FK;


class Header {


	public:
		string nome;
		list<COL> colunas;
		list<INFO_PAGINA> paginas;


		/** Lê um arquivo de header em uma estrutura de header.
			@param arq O arquivo de header.
			@param err Ponteiro para identificador de erro.
		*/
		Header(FILE *a);

		Header();

		/** Desaloca a memória alocada em uma header struct.
		*/
		~Header();


		/** Cria um arquivo de los muertos.
		*/
		void criar_arq();


};




#endif

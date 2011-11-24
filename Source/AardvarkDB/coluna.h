/** As informacoes de uma coluna de uma tabela.
*/


#ifndef COLUNA_H
#define COLUNA_H

#include <string>
#include <cstdlib>
#include "tipos.h"

using namespace std;


typedef struct {

	bool tem_default;
	bool not_null;
	bool unique;
	//bool pk : 1;
	bool fk;
}BOOLEANS;

class COL {

	public:
		string nome;
		TIPO tipo;
		BOOLEANS booleans;
		int quant;		//quantidade de elementos.
		void *vdefault;		//valor default.
		string nom_tab_ref;	//nome da tabela referenciada.
		string nom_col_ref;	//nome da coluna na tabela referenciada.


		COL();

		/** Le uma coluna.
		*/
		void ler(FILE *a);

		/** Escreve uma coluna no arquivo.
		*/
		void escrever(FILE *a);

		/** O total de bytes dos dados da coluna.
		*/
		int obter_tam();

};

#endif

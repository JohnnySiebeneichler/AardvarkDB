#include "coluna.h"


COL::COL() {

}

void COL::ler(FILE *a) {

	if (!a) return;

	fscanf(a, "%s", &(nome[0]));
	fread(&tipo, sizeof(TIPO), 1, a);
	fread(&booleans, sizeof(BOOLEANS), 1, a);
	fread(&quant, sizeof(int), 1, a);

	if (booleans.tem_default) {
		vdefault = malloc(obter_tam());
		if (!vdefault) return;
		fread(vdefault, obter_tam(), 1, a);
	}

	if (booleans.fk) {
		fscanf(a, "%s%s", &(nom_tab_ref[0]), &(nom_col_ref[0]));
	}
}


void COL::escrever(FILE *a) {

	if (!a) return;

	fwrite(&(nome[0]), sizeof(char), nome.length() + 1, a);
	fwrite(&tipo, sizeof(TIPO), 1, a);
	fwrite(&booleans, sizeof(BOOLEANS), 1, a);
	fwrite(&quant, sizeof(int), 1, a);


	if (booleans.tem_default) {
		fwrite(vdefault, obter_tam(), 1, a);
	}

	if (booleans.fk) {
		fwrite(&(nom_tab_ref[0]), sizeof(char), nom_tab_ref.length() + 1, a);
		fwrite(&(nom_col_ref[0]), sizeof(char), nom_col_ref.length() + 1, a);
	}
}

int COL::obter_tam() {
	return get_tam(tipo) * quant;
}

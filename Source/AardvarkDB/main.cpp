#include <iostream>
#include "header.h"
#include "tipos.h"

void testar_maketable();
void testar_opentable();

int main() {

	//testar_maketable();
	testar_opentable();
	return 0;
}


void testar_maketable() {

	BOOLEANS b;
	b.tem_default = true;
	b.fk = false;
	b.not_null = false;
	b.unique = false;

	COL *c = new COL();

	c->nome = "ID";
	c->tipo = sint;
	c->quant = 1;
	c->booleans = b;
	c->vdefault = malloc(sizeof(int));
	*((int *) c->vdefault) = 666;

	Header *h = new Header();
	h->nome = "Tabeladelosmuertos";
	h->colunas.push_back(*c);

	c = new COL();
	c->nome = "Valor";
	c->tipo = sint;
	c->quant = 2;
	c->booleans = b;
	c->vdefault = malloc(sizeof(int) * 2);
	*((int *) c->vdefault) = 112;

	h->colunas.push_back(*c);

	h->criar_arq();
}


void testar_opentable() {

	FILE *f = fopen("Tabeladelosmuertos.header", "rb");
	Header *h = new Header(f);

	printf("lol");

	printf("%d", h->colunas.back().quant);

	fclose(f);
}

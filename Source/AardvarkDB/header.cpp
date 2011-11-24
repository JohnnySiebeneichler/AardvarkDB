#include "header.h"

Header::Header(FILE *a) {

	if (!a) return;

	fscanf(a, "%s", &(nome[0]));

	printf("Pos: %d\n", ftell(a));
	int qcols;
	fread(&qcols, sizeof(int), 1, a);

	printf("Qcols: %d, Nome: %s\n", qcols, &(nome[0]));

	for (int c1 = 0; c1 < qcols; c1++) {
		COL *col = new COL();
		col->ler(a);
		colunas.push_back(*col);
	}

	int qpags;
	fread(&qpags, sizeof(int), 1, a);
	for (int c1 = 0; c1 < qpags; c1++) {
		INFO_PAGINA ip;

		fscanf(a, "%s", &(ip.nome[0]));
		fread(&(ip.quant), sizeof(int), 1, a);
		ip.tam = colunas.front().obter_tam();
		ip.pk_inicial = malloc(ip.tam);
		fread(ip.pk_inicial, ip.tam, 1, a);
	}
}


Header::Header() {
}

Header::~Header() {
	// ( :-D )
}



void Header::criar_arq() {

	FILE *a;
	string nomearq = nome;
	nomearq.append(".header");
	a = fopen(&(nomearq[0]), "wb");

	fwrite(&(nome[0]), nome.length() + 1, 1, a);
	int s = (int) colunas.size();
	fwrite(&s, sizeof(int), 1, a);

	list<COL>::iterator i;
	COL buf;

	for (i = colunas.begin(); i != colunas.end(); i++) {
		buf = (COL) *i;
		buf.escrever(a);
	}

	s = (int) paginas.size();
	fwrite(&s, sizeof(int), 1, a);

	list<INFO_PAGINA>::iterator i2;
	for (i2 = paginas.begin(); i2 != paginas.end(); i2++) {
		INFO_PAGINA buf2 = (INFO_PAGINA) *i2;

		fwrite(&(buf2.nome[0]), (buf2.nome).size() + 1, 1, a);
		fwrite(&buf2.quant, sizeof(int), 1, a);
		fwrite(&buf2.tam, sizeof(int), 1, a);
		fwrite(&buf2.pk_inicial, buf2.tam, 1, a);
	}

	fclose(a);
}

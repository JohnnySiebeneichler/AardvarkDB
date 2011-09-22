/**

21/set/2011

Funções e definições relacionadas ao formato de data usada no banco.


//todo:
-input, output
-verificar validade (30/2, etc)
-gets (ano, mes, ac/ad, bisexto, dia da semana)
-get nome do mes
-converter formatos (AUB, armênio, etc).
-imprimir em varios formatos (dd/mm/yyyy, yyyy/dd/mm, mm/dd/yy, etc).
-comparação de datas


*/



/** Formato de data do calendário gregoriano. Ano negativo -> AC.
*/
class DATA_GREG {

	public:
	unsigned char dia;
	unsigned char mes;
	int ano;



	public:
	ERR data(FILE *f) {

		check_file(f);
		dia = (unsigned char) fgetc(f);
		mes = (unsigned char) fgetc(f);
		get_n_bytes(f, &ano, sizeof(int));

		return SUCESSO;


	}

	void ~data(); //impl





}

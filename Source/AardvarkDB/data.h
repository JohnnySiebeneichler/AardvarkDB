/**

21/set/2011

Funções e definições relacionadas ao formato de data usada no banco.


//todo:
-input, output
-verificar validade (30/2, etc) *
-gets (ano, mes, ac/ad, bisexto, dia da semana) *
-get nome do mes
-converter formatos (AUB, armênio, etc).
-imprimir em varios formatos (dd/mm/yyyy, yyyy/dd/mm, mm/dd/yy, etc).
-comparação de datas


*/
#ifndef DATA_H
#define DATA_H

#include <string>
#include <cstdio>
#include "byteio.h"

typedef enum {

        JANEIRO,
        FEVEREIRO,
        MARCO,
        ABRIL,
        MAIO,
        JUNHO,
        JULHO,
        AGOSTO,
        SETEMBRO,
        OUTUBRO,
        NOVEMBRO,
        DEZEMBRO
} MES;

/** Formato de data do calendário gregoriano. Ano negativo -> AC.
*/

class DATA_GREG
{

public:
        unsigned char dia;
        MES mes;
        int ano;

//public:
        ERR data(FILE *f) {

                check_file(f);
                unsigned char dia = (unsigned char) fgetc(f);
                unsigned char mes = (unsigned char) fgetc(f);
                get_n_bytes(f, &ano, sizeof(int));

                return SUCESSO;
        }

        //void ~data(); //impl 

        /**
        * Retorna se o ano é ou não bissexto.
        **/
        bool bissexto(int &ano) {
                return
                        (ano % 4 == 0 && (ano % 400 == 0 || ano % 100 != 0));
        }

        /**
        * Verifica a validade de uma data.
        **/
        bool verificar_validade() {
                int monthlen[]= {31,28,31,30,31,30,31,31,30,31,30,31};
                if (bissexto(ano) && mes==2)
                        monthlen[1]++;
                return(dia<=monthlen[mes-1]);

        }


        std::string get_nome_mes (int mes) {
                switch (mes) {
                case JANEIRO:
                        return "Janeiro";
                case FEVEREIRO:
                        return "Fevereiro";
                case MARCO:
                        return "Março";
                case ABRIL:
                        return "Abril";
                case MAIO:
                        return "Maio";
                case JUNHO:
                        return "Junho";
                case JULHO:
                        return "Julho";
                case AGOSTO:
                        return "Agosto";
                case SETEMBRO:
                        return "Setembro";
                case OUTUBRO:
                        return "Outubro";
                case NOVEMBRO:
                        return "Novembro";
                case DEZEMBRO:
                        return "Dezembro";
		default: return "Mês inválido";
                }

        }
};
#endif


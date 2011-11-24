#include "tipos.h"


size_t get_tam(TIPO t) {


	switch (t) {

	case ubyte: return sizeof(unsigned char);
	case sbyte: return sizeof(char);

	case ushint: return sizeof(unsigned short int);
	case sshint: return sizeof(short int);

	case _uint: return sizeof(unsigned int);
	case sint: return sizeof(int);

	case _ulong: return sizeof(unsigned long);
	case slong: return sizeof(long);

	case singleprec: return sizeof(float);
	case doubleprec: return sizeof(double);

	case data: return sizeof(DATA_GREG);
	case horario: return sizeof(unsigned int);
	case timestamp: return sizeof(time_t);

	case varchar_utf8: return 1;
	case fixchar_utf8: return 1;
	case varchar_utf16: return 2;
	case fixchar_utf16: return 2;
	case varchar_utf32: return 4;
	case fixchar_utf32: return 4;
	}
	return 0;
}


void ler_valor(FILE *f, void *v, TIPO t, int n) {

	switch (t) {

	case data: {
		//*v = (data) new data(f);
		// You should not change v value, unless it was void **v
		// Casting like (data) is not C++ style.
		// C++ style:
		//	data *n = new data(f);
		break;
	}
	case varchar_utf8: ;//
	case varchar_utf16: ;//
	case varchar_utf32: ;//
	case fixchar_utf8: ;//
	case fixchar_utf16: ;//
	case fixchar_utf32: {//
		//ler_string(f, v, t, n);
		fwrite(v, get_tam(t), n, f);
		break;
	}
	//default: get_n_bytes(f, v,get_tam(t));
	default: fwrite(v, get_tam(t), 1, f);

	}
}

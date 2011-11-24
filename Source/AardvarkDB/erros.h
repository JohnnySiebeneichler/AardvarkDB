/**

20/set/2011

Lida com o controle de erros que podem ocorrer no programa em si.
Não lida com os problemas do banco.

*/
#ifndef ERROS_H
#define ERROS_H

#include <iostream>
#include <string>

using namespace std;

typedef enum {

	SUCESSO,
	ERR_ALLOC,
	ERR_PARAM,
	ERR_PTR,
	ERR_NOT_IMPL,
	ERR_NOPEN
}ERR;


#define check_file(file) if (!file) return ERR_NOPEN
#define check_ptr(ptr) if (!ptr) return ERR_PTR
#define check_malloc(ptr) if (!ptr) return ERR_ALLOC
#define check_erro(err) if (err != SUCESSO) return err

#define set_file_err(file, errptr) if (!file) {\
	*errptr = ERR_NOPEN;\
	return;\
}

#define set_ptr_err(ptr, errptr) if (!ptr) {\
	*errptr = ERR_NOPEN;\
	return;\
}

#define set_malloc_err(ptr, errptr) if (!ptr) {\
	*errptr = ERR_NOPEN;\
	return;\
}

#define set_erro_err(err, errptr) if (err != SUCESSO) {\
	*errptr = err;\
	return;\
}



string mensagem_de_erro(ERR err);

#endif

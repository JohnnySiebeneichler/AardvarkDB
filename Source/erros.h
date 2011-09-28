/**

20/set/2011

Lida com o controle de erros que podem ocorrer no programa em si.
Não lida com os problemas do banco.

*/
#ifndef ERROS_H
#define ERROS_H

#include <iostream>
#include <string>

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



std::string mensagem_de_erro(ERR err) {

	switch (err) {

	case SUCESSO: return "Sucesso.";
	case ERR_ALLOC: return "Erro na alocação.";
	case ERR_PARAM: return "Parâmetro inválido.";
	case ERR_PTR: return "Null pointer.";
	case ERR_NOT_IMPL: return "Funcionalidade não implementada.";
	case ERR_NOPEN: return "Não conseguiu abrir arquivo.";


	default: return "Erro desconhecido.";
	}
}

#endif

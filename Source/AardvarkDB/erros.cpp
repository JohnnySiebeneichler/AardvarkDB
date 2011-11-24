
#include "erros.h"

string mensagem_de_erro(ERR err) {

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

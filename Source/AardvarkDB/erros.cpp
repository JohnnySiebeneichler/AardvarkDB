
#include "erros.h"

string mensagem_de_erro(ERR err) {

	switch (err) {

	case SUCESSO: return "Sucesso.";
	case ERR_ALLOC: return "Erro na aloca��o.";
	case ERR_PARAM: return "Par�metro inv�lido.";
	case ERR_PTR: return "Null pointer.";
	case ERR_NOT_IMPL: return "Funcionalidade n�o implementada.";
	case ERR_NOPEN: return "N�o conseguiu abrir arquivo.";


	default: return "Erro desconhecido.";
	}
}

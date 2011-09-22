/**

20/set/2011

Lida com o controle de erros que podem ocorrer no programa em si.
Não lida com os problemas do banco.

*/


typedef enum {

	SUCESSO,
	ERR_ALLOC,
	ERR_PARAM,
	ERR_PTR,
	ERR_NOT_IMPL,
	ERR_NOPEN,


	HEADER_NENHUM_CAMPO
}ERR;


#define check_file(file) if (!file) return ERR_NOPEN
#define check_ptr(ptr) if (!ptr) return ERR_PTR
#define check_malloc(ptr) if (!ptr) return ERR_ALLOC

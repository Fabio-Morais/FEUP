/*****************************************************************/
/*       Tabela de Dispersao | PROG2 | MIEEC | 2017/18           */
/*****************************************************************/

#ifndef TABDISPERSAO_H
#define TABDISPERSAO_H



/* tabela de dispersao de strings baseada em encadeamento */

typedef unsigned long hash_func(int, int, int);

/** conteudo individual da tabela de dispersao:
 * cada objeto tem uma chave e um texto associado
 */
typedef struct
{
int x;
int y;
int valor;
} objeto;

/** elemento da tabela de dispersao */
typedef struct elem
{
	objeto* obj;
	struct elem * proximo;
} td_elemento;

/**
 * A estrutura tabela_dispersao para armazenar dados relativos a uma tabela de dispersao
 */
struct tab_dispersao
{
	hash_func *hfunc;		/* apontador para a funcao a ser usada (hash_djbm, hash_krm, ...) */
	td_elemento **elementos;	/* vetor de elementos */
	int tamanho;			/* tamanho do vetor de elementos */
};

 typedef struct tab_dispersao tabela_dispersao;

/**
 * cria uma tabela de dispersao
 * parametro: tamanho tamanho da tabela de dispersao
 * parametro: hash_func apontador para funcao de dispersao a ser usada nesta tabela
 * retorno: uma tabela de dispersao vazia que usa a funcao de dispersao escolhida
 */
tabela_dispersao* tabela_nova(int tamanho, hash_func *hfunc);

/**
 * elimina uma tabela, libertando toda a memoria ocupada
 * parametro: td tabela de dispersao a ser apagada da memoria
 * observacao: apagar _todos_ os elementos anteriormente alocados na memoria
 */
void tabela_apaga(tabela_dispersao *td);

/**
 * adiciona um novo objeto 'a tabela; se a chave ja' existir atualiza o texto associado com o novo texto
 * parametro: td tabela onde adicionar o objeto
 * parametro: valor objeto a ser adicionado
 * retorno: se o valor for adicionado correctamente, a funcao retorna TABDISPERSAO_OK
 * retorno: caso contrario deve devolver TABDISPERSAO_ERRO ou TABDISPERSAO_INVALIDA
 * observacao: valor deve ser copiado para outro local em memoria.
 */
int tabela_insere(tabela_dispersao *td, int x, int y, const int valor);



/**
 * devolve o valor correspondente 'a chave
 * parametro: td tabela onde procurar o objeto
 * parametro: chave chave do objeto a ser procurado
 * retorno: apontador para a string valor se existir, ou NULL se nao existir objeto ou tabela
 */
const int tabela_valor(tabela_dispersao *td, int x, int y);



/**
 * calcula hash com base na seguinte formula:
 *            hash(i) = hash(i-1)* 31 (+) chave[i]
 *        em que hash(0) = 5347
 *
 * parametro: chave string para o qual se pretende calcular o chave de hash
 * parametro: tamanho da tabela de dispersão
 * observacao: chave[i] e' o caracter no indice de i da chave
 * observacao: (+) representa "ou exclusivo" que em C e' indicado por ^
 */
unsigned long hash_djbm(int x, int y, int tamanho);




int tabela_numelementos(tabela_dispersao *td);


/**
 * Esta funcao imprime o estado actual da tabela para o ecra
 * parametro: td Tabela a ser mostrada no ecra
 */
void mostraTabela(tabela_dispersao *td);

#endif

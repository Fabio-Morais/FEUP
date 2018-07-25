/*****************************************************************/
/*   Grafo c/ matriz de adjacencias | PROG2 | MIEEC | 2017/18    */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

/* cria grafo com n vertices */
grafo* grafo_novo(int n)
{
    int v;
    grafo* g;

    g = (grafo*)malloc(sizeof(grafo));
    g->tamanho = n;

    /* cria array de listas de adjacencias */
    g->adjacencias = (int**)malloc(n * sizeof(int*));
    for(v=0; v<n; v++)
    {
        g->adjacencias[v] = (int*)calloc(n, sizeof(int));
    }

    return g;
}

/* apaga grafo e liberta memoria */
void grafo_apaga(grafo* g)
{
    if(g == NULL)
        return;

    if(g->adjacencias != NULL)
    {
        int v;
        for (v = 0; v <=g->tamanho; v++)
            free(g->adjacencias[v]);
        free(g->adjacencias);
    }
    free(g);
}

/* adiciona no grafo g uma aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta ja existir e 1 se foi adicionada */
int grafo_adiciona(grafo *g, int origem, int dest)
{
    if(g== NULL)
        return -1;
    if(origem<0 || dest<0 || origem>=g->tamanho || dest>=g->tamanho)
        return -1;

        return g->adjacencias[origem][dest]=1;
    /* alinea 1.1 */

}

/* remove do grafo g a aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta nao existir e 1 se foi removida */
int grafo_remove(grafo *g, int origem, int dest)
{
    if(g== NULL)
        return -1;
    if(origem<0 || dest<0 || origem>=g->tamanho || dest>=g->tamanho)
        return -1;

        return g->adjacencias[origem][dest]=0;
}

/* testa no grafo g a aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta nao existir e 1 se existir */
int grafo_aresta(grafo *g, int origem, int dest)
{
    if(g->adjacencias[origem][dest])
        return 1;
    return 0;
}

/* cria um novo grafo com base numa lista de adjacencias
   parametro adjacencies e' um array de inteiros, representado
   um numero n_edges de arestas.
   retorna um apontador para o grafo criado */
grafo* grafo_deLista(int* adjacencias, int n_arestas)
{
    int i, max=0, aux;
for(i=0; i<(n_arestas*2); i++ )
{
    if(adjacencias[i]>max)
        max=adjacencias[i];
}
    grafo *gr;
gr= grafo_novo(max+1);

for(i=0; i<(n_arestas*2); i+=2)
    grafo_adiciona(gr, adjacencias[i], adjacencias[i+1]);

    return gr;
}

/* cria e retorna um vetor de inteiros contendo os vertices
   de destino de todas as arestas com origem em i */
vetor* grafo_arestasSaida(grafo* g, int i)
{
    int j,p=0;
vetor *vet;
vet= vetor_novo();
for(j=0; j<g->tamanho; j++)
{
    if(g->adjacencias[i][j]==1)
    {
        vetor_insere(vet, j, p);
        p++;
    }
}

    return vet;
}

/* cria e retorna um vetor de inteiros contendo os vertices
   de origem de todas as arestas com destino a i */
vetor* grafo_arestasEntrada(grafo* g, int i)
{
       int j,p=0;
vetor *vet;
vet= vetor_novo();
for(j=0; j<g->tamanho; j++)
{
    if(g->adjacencias[j][i]==1)
    {
        vetor_insere(vet, j, p);
        p++;
    }
}

    return vet;

}

/* verifica se o grafo g e' completo
   retorna -1 em caso de erro (parametros invalidos)
   retorna 1 se o grafo for completo e 0 se nao o for */
int grafo_completo(grafo* g)
{
    int i,j,aux=-1;
    for(i=0; i<g->tamanho; i++)
    {

        for(j=0; j<g->tamanho; j++)
        {
            if(j!=i)
            {
                if(g->adjacencias[i][j]==0)
                {
                    aux=1;
                   break;
                }
            }
        }


    }
    if(aux==1)
        return 0;
    return 1;
}

/* verifica se o vertice i do grafo g e' uma celebridade
   retorna -1 em caso de erro (parametros invalidos)
   retorna 1 se o vertice for uma celebridade e 0 se nao o for */
int grafo_eCelebridade(grafo* g, int i)
{
vetor *aux1, *aux2;
aux1= grafo_arestasSaida(g, i); // vai ter de ser 0
aux2= grafo_arestasEntrada(g, i); // vai ter de ser tudo 2 menos ultimo

if(aux1->tamanho==0)
    if(aux2->tamanho== ((g->tamanho)-1))
        return 1;
return 0;
}

/* verifica se o grafo g tem pelo menos uma celebridade
   retorna -1 em caso de erro (parametros invalidos)
   retorna 1 se existir uma celebridade e 0 se nao existir */
int grafo_temCelebridade(grafo* g)
{
    int i;
    vetor *aux1, *aux2;
for(i=0; i<(g->tamanho); i++)
{
aux1= grafo_arestasSaida(g, i); // vai ter de ser 0
aux2= grafo_arestasEntrada(g, i); // vai ter de ser tudo 2 menos ultimo
if(aux1->tamanho==0)
    if(aux2->tamanho== ((g->tamanho)-1))
        return 1;
}

    return 0;
}

/* imprime as adjacencias do grafo */
void grafo_imprime(grafo* g)
{
    int i, j;

    if (g == NULL)
        return;

    for (i = 0; i < g->tamanho; i++)
    {
        printf("%d: ", i);
        for(j = 0; j < g->tamanho; j++)
        {
            if(g->adjacencias[i][j] != 0)
                printf("%d ", j);
        }
        printf("\n");
    }
}


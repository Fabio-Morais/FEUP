/*****************************************************************/
/*       Tabela de Dispersao | PROG2 | MIEEC | 2017/18           */
/*****************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "tabdispersao.h"

tabela_dispersao* tabela_nova(int tamanho, hash_func *hfunc)
{
    tabela_dispersao *t = (tabela_dispersao*) malloc(sizeof (tabela_dispersao));

    /* aloca memoria para os elementos */
    t->elementos = (td_elemento **) calloc(tamanho, sizeof (td_elemento*));

    t->tamanho = tamanho;
    t->hfunc = hfunc;

    return t;
}

void tabela_apaga(tabela_dispersao *td)
{
      int i;
    td_elemento *elem, *aux;


    /* para cada entrada na tabela */
    for (i = td->tamanho; i-- ; )
    {
        /* e enquanto existirem elementos nessa entrada */
        elem = td->elementos[i];

        while (elem != NULL)
        {
            /* liberta cada elemento */
            aux = elem->proximo;
            free(elem->obj);
            free(elem);
            elem = aux;
        }
    }

    /* liberta vetor e estrutura */
    free(td->elementos);
    free(td);
}

int tabela_insere(tabela_dispersao *td, int x, int y, const int valor)
{
    int index;
    td_elemento * elem;

    /* calcula hash para a string a adicionar */
    index = td->hfunc(x, y, td->tamanho);

    /* verifica se chave ja' existe na lista */
    elem = td->elementos[index];
    while (elem != NULL)
    {
        if(elem->obj->x==x && elem->obj->y==y)
            break;
        elem = elem->proximo;

    }

    if (elem == NULL)
    {
        /* novo elemento, chave nao existe na lista */

        /* aloca memoria para o elemento */
        elem = (td_elemento*) malloc(sizeof (td_elemento));

        /* aloca memoria para o objeto */
        elem->obj = (objeto*) malloc(sizeof (objeto));

        /* copia chave e valor */
        elem->obj->x=x;
        elem->obj->y=y;
        elem->obj->valor = valor;

        /* insere no inicio da lista */
        elem->proximo = td->elementos[index];
        td->elementos[index] = elem;
    }

    return 0;
}


const int tabela_valor(tabela_dispersao *td, int x, int y)
{
    int index;
    td_elemento * elem;

    /* calcula hash para a string a adicionar */
    index = td->hfunc(x, y, td->tamanho);

    /* percorre lista na posicao index e retorna 1 se encontrar */
    elem = td->elementos[index];

    while(elem != NULL)
    {
        if ((elem->obj->x==x) && (elem->obj->y==y))
            return elem->obj->valor;
        elem = elem->proximo;
    }
    return 0;
}


unsigned long hash_djbm(int x, int y, int tamanho)
{
//  969139
//999983
//367573
/** um numero primo, para conseguir melhor distribuiçao **/
unsigned long h= 65536*x+y;
    return h % tamanho;
}

int tabela_numelementos(tabela_dispersao *td)
{
    int i, count = 0;
    td_elemento * elem;


    /* percorre todos os elementos da tabela */
    for (i = 0; i < td->tamanho; i++)
    {
        elem = td->elementos[i];
        while(elem != NULL)
        {
            elem = elem->proximo;
            count++;
        }
    }
    return count;
}

/*================================================================================*/
void mostraTabela(tabela_dispersao *td)
{
    int i;
    td_elemento * elem;
    printf("TABELA DE DISPERSAO (%d elementos)\n", tabela_numelementos(td));
    for (i = 0; i < td->tamanho; i++)
    {
        if (td->elementos[i])
        {
            printf("\t[%2d]", i);
            elem = td->elementos[i];
            while (elem)
            {
                printf(" : [\"%d\" ""%d\" :: \"%d\"]", elem->obj->x,elem->obj->y, elem->obj->valor);
                elem = elem->proximo;
            }
            printf("\n");
        }
    }
    printf("\n");
}


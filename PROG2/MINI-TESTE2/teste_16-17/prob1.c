#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "grafo.h"

/*** problema 1.1 ***/
char* avl_maiorstring(no_avl *no)
{
    /* complexidade do algoritmo: ________________ */
    char *maior, *maior_aux;

    if(no== NULL)
        return NULL;


    maior=no->str;


    maior_aux=avl_maiorstring(no->esquerda);

    if(maior_aux!=NULL && strlen(maior_aux)>strlen(maior))
        maior=maior_aux;

    maior_aux=avl_maiorstring(no->direita);

    if(maior_aux!=NULL && strlen(maior_aux)>strlen(maior))
        maior=maior_aux;


    return maior;
}

/*** problema 1.2 ***/
int grafo_maisdistante(grafo *g, int origem, int *distancia)
{
    int i, max=0, max_indice, n;

    if(g==NULL || distancia== NULL || origem<0 || origem>g->tamanho)
    {
        return -1;
    }

    for(i=0; i<g->tamanho; i++)
    {

        grafo_bfs(g, origem, i, &n);
        if(n>max)
        {
            max_indice=i;
            max=(n);
        }
    }
    (*distancia)= max;
    (*distancia)--;

    return max_indice;
}

/* Aqui comeca o codigo de teste. Nao modificar! */

#define MAX_STR 500

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    FILE *fp=fopen("paises.txt", "r");
    char str_aux[MAX_STR], *str;

    /* teste problema 1.1 */
    {
        arvore_avl *arv;
        puts("* Problema 1.1 *");
        arv = avl_nova();
        while(fgets(str_aux,MAX_STR,fp) != NULL)
        {
            if(str_aux[strlen(str_aux)-1] == '\n')
                str_aux[strlen(str_aux)-1] = '\0';
            avl_insere(arv, str_aux);
        }
        str = avl_maiorstring(arv->raiz);
        printf("Maior string: ");
        if(str != NULL)
            puts(str);
        else
            puts("(null)");
        avl_apaga(arv);
    }

    /* teste problema 1.2 */
    {
        grafo *g;
        int vertice, comprimento;
        puts("\n* Problema 1.2 *");
        g = grafo_novo(8, DIGRAFO);
        grafo_adiciona(g,0,4);
        grafo_adiciona(g,1,0);
        grafo_adiciona(g,1,5);
        grafo_adiciona(g,2,1);
        grafo_adiciona(g,3,2);
        grafo_adiciona(g,4,3);
        grafo_adiciona(g,5,4);
        grafo_adiciona(g,6,3);
        grafo_adiciona(g,7,2);
        grafo_adiciona(g,7,6);

        vertice = grafo_maisdistante(g, 1, &comprimento);
        if(vertice != -1)
            printf("Mais distante do vertice 1: %d (distancia %d)\n", vertice, comprimento);
        vertice = grafo_maisdistante(g, 6, &comprimento);
        if(vertice != -1)
            printf("Mais distante do vertice 6: %d (distancia %d)\n", vertice, comprimento);

        grafo_apaga(g);
    }

    fclose(fp);
    return 0;
}

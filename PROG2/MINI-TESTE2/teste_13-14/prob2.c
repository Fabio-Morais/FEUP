#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

void imprimirFiltro(no_avl *no)
{
    if(no==NULL)
        return;
    if(atoi(no->str)<15000)
    printf("\n%s", no->str);
    imprimirFiltro(no->esquerda);

    imprimirFiltro(no->direita);


    return;
}

int imprimirMaxMinLeituras(const char *nomeFicheiro)
{
    int x=0;
    char num[10];
    FILE *fp;
    arvore_avl *arv=avl_nova();
    fp=fopen(nomeFicheiro, "r");
    while(fscanf(fp, "%s", num)!=EOF)
    {
       avl_insere(arv, num);
    }
    printf("max: %s\nmin: %s", avl_max(arv), avl_min(arv));
    imprimirFiltro(arv->raiz);
    return 1;
}


/*----------------------------------*/
/*    nao alterar a funcao main     */

int main()
{
	if(imprimirMaxMinLeituras("leituras.txt") == 0)
	{
		printf("Erro ao executar funcao.\n");
		return 1;
	}

	return 0;
}

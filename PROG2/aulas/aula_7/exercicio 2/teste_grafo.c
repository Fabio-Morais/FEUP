#include "grafo.h"
#include <stdio.h>

int main()
{
    int j;
	/* exemplo da alinea 1.2 */
	int adj[] = {0,1,0,2,0,3,1,4,2,4,3,4};
	grafo *g12 = grafo_deLista(adj, 6);
	grafo_imprime(g12);
    vetor *ve;
	/* outros testes */

printf("\t\t------------------------------------------\n\n");

/* ALINEA 1.3*/
printf("\t\tARESTA SAIDA PARA 0\n");
ve=grafo_arestasSaida(g12, 0);
for(j=0; j<ve->tamanho; j++)
printf("->%d\n", ve->elementos[j]);

printf("\t\tARESTA ENTRADA PARA 3\n");
ve=grafo_arestasEntrada(g12, 3);
for(j=0; j<ve->tamanho; j++)
printf("->%d\n\n\n", ve->elementos[j]);

printf("\t\t------------------------------------------\n\n");

    /** EXERCICIO 1.4**/
int ad[] = {0,1,0,2,1,2};
	grafo *g1 = grafo_deLista(ad, 3);
	grafo_imprime(g1);
printf("\n-- grafo completo: %s\n",grafo_completo(g1)?"true":"false");

printf("\t\t------------------------------------------\n\n");
    /** EXERCICIO 1.5**/
    printf("\n\n CELEBRIDADE?\n");
    int adq[] = {0,2,1,2,0,1,1,0};
	grafo *g11 = grafo_deLista(adq, 4);
	grafo_imprime(g11);
printf("\n\n O GRAFO 2 E CELEBRIDADE? %s \n\n",grafo_eCelebridade(g11, 2)?"true":"false");
	printf("\nFIM\n");


printf("\t\t------------------------------------------\n\n");
	/** EXERCICIO 1.5-b**/
    printf("\n\n TEM PELO MENOS UMA CELEBRIDADE?\n");
    int adqq[] = {0,2,1,2,0,1,1,0};
	grafo *g111 = grafo_deLista(adqq, 4);
	grafo_imprime(g111);
printf("\n\n O GRAFO TEM PELO MENOS UMA CELEBRIDADE? %s \n\n",grafo_temCelebridade(g111)?"true":"false");


	return 0;
}

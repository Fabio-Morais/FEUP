#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int imprimirLeiturasOrdenadas (const char *nomeFicheiro)
{
    int x;
FILE *fich= fopen(nomeFicheiro, "r");
heap *hep=heap_cria(1000);
char str[100];
while(fscanf(fich, "%d", &x)!= EOF)
{
    sprintf(str, "%d", x);
    heap_insere(hep, str, x);
}

while(hep->tamanho_atual>0)
printf("%s\n", heap_remove(hep));

	return 1;
}


/* v-- nao alterar funcao main --v */

int main()
{
	if(imprimirLeiturasOrdenadas("leituras.txt") == 0)
	{
		printf("Erro ao executar funcao.\n");
		return 1;
	}

	return 0;
}

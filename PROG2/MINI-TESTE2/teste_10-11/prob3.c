#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int imprimirLeiturasOrdenadas (const char *nomeFicheiro)
{
	
}


/* v-- nao alterar funcao main --v */

int main()
{
	if(imprimirLeiturasOrdenadas("leituras.txt") == 0)
	{
		printf("Erro ao executar funcao.");
		return 1;
	}
	system("pause");
	return 0;
}
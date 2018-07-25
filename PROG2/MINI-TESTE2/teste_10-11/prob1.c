#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "pilha.h"

int fila_inverte(fila *f)
{
return 0;
}

int pilha_push2 (pilha *p, const char* string)
{

return 0;

}


/* v-- nao alterar funcao main --v */

int main()
{
	/* teste problema 1.1 */
	{
		fila *f;
		char *str;

		f = fila_nova();
		fila_push(f, "A"); fila_push(f, "B"); fila_push(f, "C");
		fila_push(f, "D"); fila_push(f, "E");

		printf("Antes de inverter: A B C D E\n");

		fila_inverte(f);

		printf("Depois de inverter: ");

		while(!fila_vazia(f))
		{
			str = fila_front(f);
			if(str==NULL) break;
			printf("%s ", str);
			fila_pop(f);
			free(str);
		}

		printf("\n");

		fila_apaga(&f);
	}

	printf("\n");

	/* teste problema 1.2 */
	{
		pilha *p;
		char *str;

		p = pilha_nova();
		pilha_push(p, "A"); pilha_push(p, "B"); pilha_push(p, "C");
		pilha_push(p, "D"); pilha_push(p, "E");

		printf("Antes de push2: E D C B A\n");

		pilha_push2(p, "F");

		printf("Depois de push2: ");

		while(!pilha_vazia(p))
		{
			str = pilha_top(p);
			if(str==NULL) break;
			printf("%s ", str);
			fila_pop(p);
			free(str);
		}
		printf("\n\n");
		pilha_apaga(&p);
	}
	system("pause");
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"
#include "pilha.h"

pilha * pilha_duplica(pilha * p)
{
pilha *ori=pilha_nova();
pilha *aux=pilha_nova();
while(p->tamanho >0)
{
    pilha_push(aux, pilha_top(p));
    pilha_pop(p);
}

while(aux->tamanho >0)
{
    pilha_push(ori, pilha_top(aux));
    pilha_push(p, pilha_top(aux));
    pilha_pop(aux);

}

	return ori;
}

int fila_elimina(fila *f, char c_inicial)
{
    int i=0, cap=0;
    char *v;
    fila *fil= fila_nova(f->capacidade);

    while(fila_vazia(f)!=1)
    {
        v=fila_front(f);
        if(v[0]!= c_inicial)
            {
                i++;
                fila_push(fil, fila_front(f));
            }
            cap++;
        fila_pop(f);
    }
    while(fila_vazia(fil)!=1)
    {

        fila_push(f, fila_front(fil));
        fila_pop(fil);
    }

	return cap-i;
}


/* v-- nao alterar funcao main --v */

int main()
{
	/* teste problema 1.1 */
	int erros1, erros2, tmp;
	pilha * p, * copia;
	char *str1, *str2;
	fila * f;
	erros1 = erros2 = 0;

	printf("EXERCICIO 1.1:\n");

	p = pilha_nova();
	pilha_push(p, "um"); pilha_push(p, "dois"); pilha_push(p, "tres");
	pilha_push(p, "quatro"); pilha_push(p, "cinco");

	copia = pilha_duplica(p);

	if (pilha_tamanho(copia) != pilha_tamanho(p)) {
		printf("As alturas das pilhas nao coincidem!\n");
		erros1++;
	}
	while(!pilha_vazia(p) && !pilha_vazia(copia)) {
		str1 = pilha_top(p);
		str2 = pilha_top(copia);
		if (strcmp(str1, str2)) {
			printf("Os elementos nao coincidem (%s != %s)\n", str1, str2);
			erros1++;
		}
		pilha_pop(p);
		pilha_pop(copia);
	}

	if (!erros1) {
		printf("Resultado obtido e' o esperado.\n");
	}

	printf("\nEXERCICIO 1.2\n");

	f = fila_nova(0);

	fila_push(f, "um");
	fila_push(f, "dois");
	fila_push(f, "tres");
	fila_push(f, "quatro");
	fila_push(f, "cinco");
	fila_push(f, "seis");
	fila_push(f, "sete");
	fila_push(f, "oito");
	fila_push(f, "nove");
	fila_push(f, "dez");
	fila_push(f, "onze");
	fila_push(f, "doze");

	tmp = fila_elimina(f, 's');
	if (tmp != 2) {
		printf("Deviam ter sido eliminados 2 elementos.\n");
		erros2++;
	}
	if (fila_comprimento(f) != 10) {
		printf("Tamanho da fila invalido. Devia ser 10 mas encontrado e %d.\n", fila_comprimento(f));
		erros2++;
	}

	tmp = fila_elimina(f, 'd');
	if (fila_comprimento(f) != 7) {
		printf("Tamanho da fila invalido. Devia ser 7 mas encontrado e %d.\n", fila_comprimento(f));
		erros2++;
	}
	if (tmp != 3) {
		printf("Deviam ter sido eliminados 3 elementos.\n");
		erros2++;
	}

	if (!erros2) {
		printf("Resultado obtido e' o esperado.\n");
	}

	return 0;
}

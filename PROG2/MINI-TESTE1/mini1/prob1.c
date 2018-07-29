#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "fila.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 1.1 ***/
lista *encontra_nomes(lista *lst1, lista *lst2)
{
	/* complexidade do algoritmo: ___N^2___ */
	// iguais nas 2 listas
	int i, j;
	lista *aux;
	aux = lista_nova();
	l_elemento *lista1 = lista_inicio(lst1);
	l_elemento *lista2;
	for (i = 0; i < lista_tamanho(lst1); i++)
	{
		lista2 = lista_inicio(lst2);
		for (j = 0; j < lista_tamanho(lst2); j++)
		{
			if (strcmp(lista1->str, lista2->str) == 0)
				lista_insere(aux, lista1->str, NULL);
			lista2 = lista2->proximo;
		}
		lista1 = lista1->proximo;
	}

	return aux;
}

/*** problema 1.2 ***/
int lista_remove_longos(lista *lst, int nomes)
{
	//remover nomes que tenham mais palavras que nomes

	int i, count, j, x = 0;
	l_elemento *aux;
	aux = lista_inicio(lst);

	for (i = 0; i < lista_tamanho(lst); i++)
	{
		count = 1;
		for (j = 0; j < strlen(aux->str) + 1; j++)
		{
			if (aux->str[j] == ' ')
				count++;
		}
		if (count > nomes)
		{
			lista_remove(lst, aux);
			i--;
			x++;
		}
		aux = aux->proximo;
	}

	return x;
}

/*** problema 1.3 ***/
fila *pesquisa_nomes(lista *lst, char *nome)
{
	int i;
	fila *aux;
	aux = fila_nova();
	l_elemento *lista;
	lista= lista_inicio(lst);
	// fila_front

	for (i = 0; i < lista_tamanho(lst); i++)
	{

		if(strstr(lista->str, nome))
			fila_push(aux, lista->str);
		lista= lista->proximo;
	}

	return aux;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

lista *lerParaLista(FILE *ficheiro)
{
	char buffer[256], *nlptr;
	lista *l;

	if (ficheiro == NULL)
		return NULL;

	l = lista_nova();

	while (fgets(buffer, 255, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		lista_insere(l, buffer, NULL);
	}

	return l;
}

int main()
{
	FILE *f;
	lista *l1 = NULL, *l2 = NULL, *l = NULL;
	fila *resultado = NULL;
	l_elemento *e;
	int removidos;

	/* testes */
	f = fopen("nomes1.txt", "r");
	if (f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	l1 = lerParaLista(f);
	fclose(f);

	f = fopen("nomes2.txt", "r");
	if (f == NULL)
	{
		printf("Erro ao ler ficheiro de entrada.\n");
		return 1;
	}
	l2 = lerParaLista(f);
	fclose(f);

	/* inicio teste prob1.1 */
	l = encontra_nomes(l1, l2);
	if (l)
		printf("\nLista resultante contem %d nomes.\n", lista_tamanho(l));
	else
		printf("\nencontra_nomes retornou NULL\n");
	/* fim teste prob1.1 */

	/* inicio teste prob1.2 */
	removidos = lista_remove_longos(l1, 4);
	if (removidos != -1)
	{
		printf("\nNomes longos removidos (total %d).\n", removidos);
		if (lista_tamanho(l1) != 224)
			printf("Nem todos os nomes longos foram removidos da lista (tamanho: %d; esperado: 19)\n", lista_tamanho(l1));
	}
	else
		printf("\nlista_remove_longos retornou ERRO\n");
	/* fim teste prob1.2 */

	/* inicio teste prob1.3 */
	resultado = pesquisa_nomes(l2, "SILVA");
	if (resultado)
	{
		int n = 0;
		printf("\nNomes encontrados (%d): \n", fila_tamanho(resultado));
		while (!fila_vazia(resultado) && n < 3)
		{
			printf("%s\n", fila_front(resultado));
			fila_pop(resultado);
			n++;
		}
		if (fila_tamanho(resultado) > 2)
		{
			puts("...");
			while (fila_tamanho(resultado) > 1)
				fila_pop(resultado);
			printf("%s\n", fila_front(resultado));
			fila_pop(resultado);
		}
		else
		{
			while (!fila_vazia(resultado))
			{
				printf("%s\n", fila_front(resultado));
				fila_pop(resultado);
			}
		}
	}
	else
		printf("\npesquisa_nomes retornou NULL\n\n");
	/* fim teste prob1.3 */

	lista_apaga(l);
	lista_apaga(l1);
	lista_apaga(l2);
	fila_apaga(resultado);

	return 0;
}

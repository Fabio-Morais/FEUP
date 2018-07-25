#include <stdio.h>
#include <string.h>
#include "tabdispersao.h"
#include "vetor.h"

int tabela_remove_varios(tabela_dispersao *td, vetor *elementos)
{
	return 0;
}

int tabela_info(tabela_dispersao *td, float *factorCarga, int *maxElems)
{

	return 0;

}


/* v-- nao alterar funcao main --v */

int main()
{
	/* teste problema 2.1 */
	{
		tabela_dispersao *td;
		vetor *v;
		FILE *f;
		char str[100];

		td = tabela_nova(100, hash_djbm);
		if(!td) return 1;

		v = vetor_novo();
		if(!v) return 1;

		f = fopen("dados.txt", "rt");
		if(!f) return 1;

		while(!feof(f))
		{
			char *aux;
			fgets(str, 100, f);
			aux = strchr(str, '\r');
			if(aux != NULL) *aux ='\0';
			aux = strchr(str, '\n');
			if(aux != NULL) *aux ='\0';
			tabela_insere(td, str);
		}

		vector_adiciona(v, "C. Antony R. Hoare");
		vector_adiciona(v, "Vinton G. Cerf and Robert E. Kahn");
		vector_adiciona(v, "Charles P. Thacker");
		vector_adiciona(v, "Nao existe");

		printf("Num elementos antes de remover: %d\n", tabela_numelementos(td));

		tabela_remove_varios(td, v);

		printf("Num elementos depois de remover: %d\n", tabela_numelementos(td));

		tabela_apaga(td);
		vector_apaga(v);
	}

	printf("\n");

	/* teste problema 2.2 */
	{
		tabela_dispersao *td;
		FILE *f;
		char str[100];
		float factorCarga = 0;
		int maxElems = 0;

		td = tabela_nova(13, hash_djbm);
		if(!td) return 1;

		f = fopen("dados.txt", "rt");
		if(!f) return 1;

		while(!feof(f))
		{
			char *aux;
			fgets(str, 100, f);
			aux = strchr(str, '\r');
			if(aux != NULL) *aux ='\0';
			aux = strchr(str, '\n');
			if(aux != NULL) *aux ='\0';
			tabela_adiciona(td, str);
		}

		tabela_info(td, &factorCarga, &maxElems);

		printf("Factor de carga: %.2f\n", factorCarga);
		printf("Numero max de elementos: %d\n", maxElems);

		tabela_apaga(td);
	}
	system("pause");
	return 0;
}

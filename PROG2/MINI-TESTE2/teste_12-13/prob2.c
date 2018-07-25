#include <stdio.h>
#include <string.h>
#include "tabdispersao.h"
#include "vetor.h"

int tabela_remove_varios(tabela_dispersao *td, vetor *elementos)
{
int i;
for(i=0; i<elementos->tamanho; i++)
tabela_remove(td, vetor_elemento(elementos, i));

	return 1;
}

int tabela_info(tabela_dispersao *td, float *factorCarga, int *maxElems)
{
	/* problema 2.2 - a implementar */
	int n=0, count, max=-1, i;
	float resultado;
	elemento *ele;
	objeto *ob=tabela_elementos(td, &n);
resultado=((float)n/(float)td->tamanho);
(*factorCarga)=resultado;

for(i=0; i<td->tamanho; i++)
{
    count=0;
ele=td->elementos[i];

while(ele)
{
    count++;
    ele=ele->proximo;
}
if(count>max)
    max=count;

}
(*maxElems)= max;

	return 1;
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
		objeto obj;

		td = tabela_cria(100, hash_djbm);
		if(!td) return 1;

		v = vetor_novo();
		if(!v) return 1;

		f = fopen("dados.txt", "rt");
		if(!f) return 1;

		while(!feof(f))
		{
			fgets(str, 100, f);
			str[strlen(str)-1] = '\0';
			strcpy(obj.chave, str);
			strcpy(obj.valor, str);
			tabela_adiciona(td, &obj);
		}

		vetor_insere(v, "C. Antony R. Hoare", -1);
		vetor_insere(v, "Vinton G. Cerf and Robert E. Kahn", -1);
		vetor_insere(v, "Charles P. Thacker", -1);
		vetor_insere(v, "Nao existe", -1);

		printf("Num elementos antes de remover: %d\n", tabela_numelementos(td));

		tabela_remove_varios(td, v);

		printf("Num elementos depois de remover: %d\n", tabela_numelementos(td));

		tabela_apaga(td);
		vetor_apaga(v);
	}

	printf("\n");

	/* teste problema 2.2 */
	{
		tabela_dispersao *td;
		FILE *f;
		char str[100];
		objeto obj;
		float factorCarga = 0;
		int maxElems = 0;

		td = tabela_cria(13, hash_djbm);
		if(!td) return 1;

		f = fopen("dados.txt", "rt");
		if(!f) return 1;

		while(!feof(f))
		{
			fgets(str, 100, f);
			str[strlen(str)-1] = '\0';
			strcpy(obj.chave, str);
			strcpy(obj.valor, str);
			tabela_adiciona(td, &obj);
		}

		tabela_info(td, &factorCarga, &maxElems);

		printf("Factor de carga: %.2f\n", factorCarga);
		printf("Numero max de elementos: %d\n", maxElems);

		tabela_apaga(td);
	}

	return 0;
}

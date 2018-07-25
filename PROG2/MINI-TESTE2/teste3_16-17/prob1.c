#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "tabdispersao.h"

/**         OU ASSIM         **/
//void avl_max_subarvore(arvore_avl *arv, const char *inicio)
//{
//    no_avl *no= avl_pesquisa(arv, inicio);
//    printf("%s",avl_max(no));
//
//
//}

void avl_max_subarvore(arvore_avl *arv, const char *inicio)
 {

         no_avl *no= avl_pesquisa(arv, inicio);

         while(1)
         {
             if(no->direita==NULL)
             {
               printf("%s", no->str);
                break;
             }              no=no->direita;
         }
 }

tabela_dispersao* tabela_copia(tabela_dispersao *original, int novotamanho)

{
    int i;
    tabela_dispersao *tabela=tabela_nova(novotamanho, original->hfunc);
    td_elemento *elem;
    for(i=0; i<original->tamanho; i++)
    {
        elem=original->elementos[i];
        while(elem)
        {
            tabela_insere(tabela, elem->obj->chave, elem->obj->valor),
            elem=elem->proximo;
        }
    }

	return tabela;
}


/* Aqui começa o código de teste. Não modificar! */

#define MAX_STR 500
#define TAM_TAB 601
#define TAM_TAB_2 619

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *fp=fopen("paises.txt", "r");
	FILE *fm=fopen("mails.txt", "r");
	char str_aux[MAX_STR];

	/* teste problema 1.1 */
	{
		arvore_avl *res;
		puts("* Problema 1.1 *");
		res = avl_nova();
		while(fscanf(fp,"%s",str_aux) == 1)
			avl_insere(res, str_aux);
		printf("Arvore original: ");
		avl_imprime(res->raiz);
        printf("Maximo da sub-arvore: ");
		avl_max_subarvore(res, "ID");

		avl_apaga(res);
	}

	/* teste problema 1.2 */
	{
		tabela_dispersao *tab=NULL, *tab_exp=NULL;
		puts("\n\n* Problema 1.2 *");
		tab=tabela_nova(TAM_TAB,hash_djbm);
		while(fscanf(fm,"%s",str_aux) == 1)
			tabela_insere(tab,str_aux,"");
		mostraTabela(tab);
		tab_exp=tabela_copia(tab, TAM_TAB_2);
		if(tab_exp != NULL)
			mostraTabela(tab_exp);
		tabela_apaga(tab);
		tabela_apaga(tab_exp);
	}

	fclose(fp);
	fclose(fm);
	return 0;
}

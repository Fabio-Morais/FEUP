#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
#include "tabdispersao.h"
#include "lista.h"


void crescente(no_avl *no)
{
    if(no==NULL)
        return;

    crescente(no->esquerda);
    printf("%s  ", no->str);
    crescente(no->direita);

    return ;

}

void decrescente(no_avl *no)
{
    if(no==NULL)
        return;

    crescente(no->direita);
    printf("%s  ", no->str);
    crescente(no->esquerda);

    return ;
}

void avl_imprime_ord(arvore_avl *avl, int ordem)
{

    if (ordem>=0)
        crescente(avl->raiz);
    else
        decrescente(avl->raiz);
}

void valida_passwds(FILE *f, lista *login, lista *passwd)
{
    int i;
    char log[25], pas[25], *x;
    elemento *loginn;
    elemento *pass=lista_inicio(passwd);
    tabela_dispersao *tabela= tabela_nova(10, hash_djbm);

    while(fscanf(f, "%s %s", log, pas )!= EOF)
    {
        tabela_adiciona(tabela,log, pas);
    }

    for(loginn=lista_inicio(login) ; loginn!=NULL; (loginn=loginn->proximo))
    {
        printf("\nlogin: %s", loginn->str);
        printf("\n pass: %s", pass->str);
        x=tabela_valor(tabela, loginn->str);
        if(x!=NULL)
        {
            if(!strcmp(x, pass->str))
                printf("\nlogin com sucesso");
            else
                printf("\nlogin sem sucesso");


        }
        pass=pass->proximo;
    }
    tabela_apaga(tabela);
}
/* Aqui começa o código de teste. Não modificar! */

int main()
{
    /* teste problema 1.1 */
    {

        arvore_avl *res;
        int i;
        char data[][4] = {"ENG", "BEL", "NED", "GER", "FRA", "RUS", "SUI", "CRO", "BIH", "ITA", "ESP", "POR", "GRE"};

        printf("* Problema 1.1 *\n");

        res = avl_nova();

        for (i = 0; i < 13; i++)
            avl_insere(res, data[i]);

        printf("Arvore original: ");
        avl_imprime(res->raiz);

        printf("Ordem alfabetica crescente: ");
        avl_imprime_ord(res, 1);
        printf("\n\n");

    }

    /* teste problema 1.2 */
    {
        FILE *f;
        lista *lg, *psswd;
        int i;
        char login[][TAMANHO_VALOR] = {"maria", "tiago", "ricardo"};
        char password[][TAMANHO_CHAVE] = {"contrary", "contrary", "sheeplost"};

        printf("* Problema 1.2 *\n");

        f = fopen("passwords.txt", "r");
        if (!f)
        {
            printf("Nao foi possivel abrir ficheiro!\n");
            return -1;
        }

        lg = lista_nova();
        for (i = 0; i < 3; i++)
            lista_insere(lg, login[i], NULL);

        psswd = lista_nova();
        for (i = 0; i < 3; i++)
            lista_insere(psswd, password[i], NULL);

        valida_passwds(f, lg, psswd);

        lista_apaga(lg);
        lista_apaga(psswd);
        fclose(f);
    }

    return 0;
}

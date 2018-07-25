#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

int lista_insere_ordenada(lista *l, char *valor)
{ int i;
    if(!l)
    {
        return -2;
    }

    int size = lista_tamanho(l);
    for( i = 0; i < size; ++i)
    {
        int result = strcmp(lista_elemento(l, i)->str, valor);
        if(result < 0)
        {
            continue;
        }
        else if(result == 0)
        {
            return -1;
        }
        else
        {
            lista_insere(l, valor, lista_elemento(l, i));
            return i;
        }
    }
    // NOTE(nox): Inserir no fim se for maior que todos os outros!
    lista_insere(l, valor, 0);

    return size;
}

lista *lista_pesquisa_substring(lista * lst, char *substring)
{
    lista *p;
    p=lista_nova();
    int i;
    l_elemento *l;

    l=lst->inicio;

    for(i=0; i<lista_tamanho(lst); i++)
    {
        if(strstr(l->str, substring)!=NULL)
            lista_insere(p, l->str, NULL);
        l=l->proximo;
    }


    return p;

}

lista *lista_concatena(lista *lst1, lista *lst2)
{
    int tamanho = lista_tamanho(lst2);
    int i;
    for(i=0; i<tamanho; i++)
    {
        lista_insere(lst1, lista_elemento(lst2, i)->str, 0);
    }

    return lst1;
}
int main()
{
    lista* lst;
    lista* lst2;
    char c[100], pes[50], strin[100];
    int n=0, i, cont=0, put, j,z;
    FILE *p;
    p= fopen("arquivo.txt", "r");

    if (p==NULL)
        printf("\nerror, file don't exist\n");
    else
    {
        printf("\t\t\t\t----------File opened----------\n\n\n");


        lst=lista_nova();


        while ((fgets(c, sizeof(c),p)) )
        {

//                printf("\n(mandou para o ficheiro)\n");
//                printf("\n pos:%d ->frase lida:  %s\n",n,c);
                lista_insere(lst, c,NULL);
                n++;

        }
        fclose(p);
            printf("Foram carregados %d jogos:\n", lista_tamanho(lst));

//        printf("\n\no que deseja pesquisar?\n");
//        scanf("%s", c);
//        lst2=lista_pesquisa_substring(lst, c);
//        l_elemento *w= lst2->inicio;
//        for (i=0; i<lista_tamanho(lst2); i++)
//        {
//            printf("\n\n%s\n", w->str );
//            w=w->proximo;
//        }

    }
//    FILE *ps2;
    lista * lst3;
    lst3= lista_pesquisa_substring(lst, "PS2");
//    l_elemento *e=lst3->inicio;
//    for(i=0; i<lista_tamanho(lst3); i++)
//    {
//        fprintf(ps2, "%s", e->str);
//        e=e->proximo;
//    }

    for(i=0; i<lista_tamanho(lst3);i++)
    {
        char *text=lista_elemento(lst3, i)->str;
        for(j=0; j<lista_tamanho(lst); j++)
        {
            char *texttes= lista_elemento(lst,j)->str;
            if(!strcmp(text, texttes))
            {
                lista_remove(lst, lista_elemento(lst,j));
                break;
            }
        }
    }
        printf("Após a remoção, a lista contém %d jogos.\n", lista_tamanho(lst));



    FILE *x;
    x= fopen("oldies.txt", "r");
    lista *lst5= lista_nova();
    printf("\n\n vai mandar");
    while(fgets(strin, sizeof(strin), x))
    {
            lista_insere(lst5, strin, NULL);
            cont++;


    }
    printf("\n(mandou para o ficheiro) %d \n", cont);
    lista *listaof= lista_concatena(lst, lst5);
    printf("\napos concatenar, a lista teve %d %d\n", lista_tamanho(listaof), lista_tamanho(lst));

            printf("------------------\n");
int ta=lista_ordena(listaof);

l_elemento *puta;
    for( i = 0; i < lista_tamanho(listaof); ++i)
    {
        puta= lista_elemento(listaof, i);
        printf("+%s+", puta->str);
        if(strcmp(puta->str, "Duke Nukem (PS3)\r")==0)
        printf("O jogo %s encontra-se na posiçao %d\n", "Duke Nukem (PS3)", i);

    }

system("PAUSE");
    return 0;

}



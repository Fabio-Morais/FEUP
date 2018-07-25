#include <stdio.h>
#include <stdlib.h>
#include "tabdispersao.h"
#include "lista.h"
#include <time.h>
#define tamanhoo 10000000


int main()
{
    int x=0;
    FILE *fich= fopen("englishwords.txt", "r");
    char aux[1000];
    lista *list=lista_nova();

    tabela_dispersao *tabela=tabela_nova(tamanhoo, hash_krm);

clock_t inicio, fim;
double tempo;
inicio = clock();

 while(fscanf(fich, "%s", aux)!= EOF )
 {
    tabela_adiciona(tabela, aux, aux);
 }

//printf("\n\n%s\n\n", tabela_valor(tabela,"the"));
/* tarefa a verificar */
 fim = clock();
 tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
 printf("tempo em segundos: %lf\n", tempo);


    return 0;
}

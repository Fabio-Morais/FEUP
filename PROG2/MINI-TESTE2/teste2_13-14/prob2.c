
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"

int topSubmissoes(FILE *f)
{
    int min, seg, tempo,i;
    char grupo[10];
    heap *hep=heap_cria(100);

    while(fscanf(f, "%s %d %d", grupo, &min, &seg)!=EOF)
    {

        heap_insere(hep, grupo, min*100+seg );
    }
    for(i=0; i<5; i++)
        printf("%s: min:%d  seg: %d\n", heap_remove(hep), (hep->elementos[0]->prioridade)/100,  hep->elementos[0]->prioridade%100);

    return 1;
}


/* v-- nao alterar funcao main --v */

int main()
{
    FILE *f;

    f = fopen("submissoes.txt", "r");

    if(topSubmissoes(f) == 0)
    {
        puts("Erro ao executar funcao.\n");
        fclose(f);
        return 1;
    }

    fclose(f);
    return 0;
}

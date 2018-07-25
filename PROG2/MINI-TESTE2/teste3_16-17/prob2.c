#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include "grafo.h"
#include "heap.h"

int proximas_n_chegadas(lista *tempos, lista *origens, lista *aeroportos, int n) {
char **aero;
int i=0, x;
elemento *a;
a=lista_inicio(aeroportos);
(aero)= (char **)malloc(sizeof(char **)*aeroportos->tamanho);
while(a!=NULL)
      {
        aero[i]=malloc( sizeof(char *)*50);
        strcpy(aero[i], a->str);
           a=a->proximo;
           i++;
      }
    /* ---------------------------------------*/

elemento *temp;
elemento *orig;
heap *arv=heap_nova(aeroportos->tamanho);
temp=lista_inicio(tempos);
orig= lista_inicio(origens);

while(temp!=NULL)
{
heap_insere(arv, orig->str, atoi(temp->str));

temp=temp->proximo;
orig=orig->proximo;

}
for(i=0; i<n; i++)
printf("[%d]  %s\n", i+1, aero[atoi(x=heap_remove(arv))]);

for(i=0; i<aeroportos->tamanho; i++)
{
    free(aero[i]);
}
free(aero);


return 1;
}

lista *pesquisa_destinos(grafo *rotas, lista *aeroportos, const char *origem) {
int i, j;
lista *list;
list= lista_nova();
elemento *aero=lista_inicio(aeroportos);

vetor *aux;
aux=vetor_novo();
for(i=0; i<aeroportos->tamanho; i++)
{
    if(!strcmp(aero->str, origem ))
        break;
    aero=aero->proximo;
}

aux=v_sucessores(rotas, i);
vetor_ordena(aux);

for(i=0; i<aux->tamanho; i++)
{
        aero=lista_inicio(aeroportos);
        for(j=0; j<aeroportos->tamanho; j++)
        {
            if(aux->elementos[i].val == j)
                break;
            aero=aero->proximo;
        }
        lista_insere(list, aero->str, NULL);

}

vetor_apaga(aux);
return list;
}

/* Aqui começa o código de teste. Não modificar! */

grafo *carrega_rotas(lista *aeroportos, const char *filename) {
if (!filename) return NULL;
    grafo *g = NULL;
    FILE *f;
    int origem, destino;
    f = fopen(filename, "r");
    if (!f) {
        printf("Erro na leitura do ficheiro: %s\n", filename);
        return NULL;
    }
    g = grafo_novo(lista_tamanho(aeroportos), NAODIRECIONADO);
    if (!g) {
        printf("Erro na criacao do grafo\n");
        return NULL;
    }
    while (fscanf(f, "%d\t%d", &origem, &destino) == 2) {
        grafo_adiciona(g, origem, destino);
    }
    fclose(f);
    return g;}

int main() {
    FILE *f;
    grafo *g = NULL;
    lista *aeroportos;
    char *buff;
    size_t n;

    setvbuf(stdout, NULL, _IONBF, 0);
    f = fopen("aeroportos.txt", "r");
    aeroportos = lista_nova();
    buff = NULL;
    n = 0;
    while (getline(&buff, &n, f) != -1) {
        buff[strlen(buff) - 1] = '\0';
        lista_insere(aeroportos, buff, NULL);
    }
    free(buff);
    fclose(f);

    g = carrega_rotas(aeroportos, "rotas.txt");

    /* teste problema 2.1 */
    {
        FILE *f;
        char tempo[5], origem[10];
        lista *tempos, *origens;

        printf("* Problema 2.1 *\n");

        f = fopen("chegadas.txt", "r");
        tempos = lista_nova();
        origens = lista_nova();

        while (fscanf(f, "%s\t%s", tempo, origem) == 2) {
            lista_insere(tempos, tempo, NULL);
            lista_insere(origens, origem, NULL);
        }

        if (proximas_n_chegadas(tempos, origens, aeroportos, 5) != 1)
            printf("Erro ao executar a funcao\n");

        lista_apaga(tempos);
        lista_apaga(origens);
        fclose(f);
    }

    /* teste problema 2.2 */
    {
        printf("\n* Problema 2.2 *\n");
        const char *origem = "Lille (FR)";
        elemento *elem;
        lista *l = pesquisa_destinos(g, aeroportos, origem);
        if (l == NULL)
            printf("Destinos diretos a partir de %s = 0\n", origem);
        else {
            printf("Destinos diretos a partir de %s = %d\n",
                   origem, lista_tamanho(l));
            for (elem = l->inicio; elem != NULL; elem = elem->proximo)
                printf("%s\n", elem->str);
            lista_apaga(l);
        }
    }

    grafo_apaga(g);
    lista_apaga(aeroportos);
    return 0;
}

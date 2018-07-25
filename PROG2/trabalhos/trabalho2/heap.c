/*****************************************************************/
/*         Trabalho pratico 2 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAIZ            (1)
#define PAI(x)            (x/2)
#define FILHO_ESQ(x)    (x*2)
#define FILHO_DIR(x)    ((x*2)+1)

heap* heap_nova(int capacidade)
{
    if(capacidade<1)  return NULL;

    heap *h;
    h=(heap *)malloc(sizeof(heap));

    if(!h) return NULL;

    h->tamanho=0;
    h->capacidade=capacidade;
    h->elementos=(elemento **)calloc((capacidade+1),sizeof(elemento *));

    if (!h->elementos)
    {
        free(h);
        return NULL;
    }
    return h;
}
/** cria um elemento do tipo elemento com o valor e prioridade
**  retorna elemento com os valores armazenado                 **/
elemento * elemento_cria(int prioridade, const char * valor)
{
    elemento * elem = (elemento *) malloc(sizeof(elemento));
    if (!elem)
        return NULL;
    elem->valor = strdup(valor);
    elem->prioridade = prioridade;

    return elem;
}

int heap_insere(heap * h, const char * texto, int prioridade)
{
    if (((h->tamanho) >= (h->capacidade)) || ( prioridade < 1 ) || ( strlen(texto) < 1) || !texto )
        return 0;

    int i;
    elemento *e;

    h->tamanho++;
    if((e=elemento_cria(prioridade, texto)) != NULL)
    {
        for (i = h->tamanho; i > 1 && h->elementos[PAI(i)]->prioridade > e->prioridade; i /= 2)
            h->elementos[ i ] = h->elementos[PAI(i)];

        h->elementos[i]= e ;
        return 1;
    }
    if(e==NULL)
    {
        free(e);
        return 0;
    }
    return 0;
}

void heap_apaga(heap *h)
{
    if(h==NULL) return;
    int i;
    for(i=1; i<=(h->tamanho); i++)
    {
        free(h->elementos[i]->valor);
        free(h->elementos[i]);
    }
    free(h->elementos);
    free(h);
    return;
}

char* heap_remove(heap * h)
{
    if(h==NULL || h->tamanho < 1) return NULL;

    int i=1;
    char *str;
    elemento *aux;
    str=strdup(h->elementos[1]->valor); /** aloca memoria e faz strcpy**/
    free(h->elementos[1]->valor);
    free(h->elementos[1]);
    if(h->tamanho == 1 )
    {
        h->tamanho--;
        return str;
    }
    h->elementos[i]=h->elementos[h->tamanho];
    h->tamanho--;
    while(i <= h->tamanho && i*2 <= h->tamanho && i*2+1 <= h->tamanho)
    {
        if(h->elementos[i]->prioridade < h->elementos[i*2]->prioridade && h->elementos[i]->prioridade < h->elementos[i*2+1]->prioridade)
            break;

        if((i*2<h->tamanho) && (h->elementos[FILHO_ESQ(i)]->prioridade < h->elementos[FILHO_DIR(i)]->prioridade))
        {
            if(h->elementos[FILHO_ESQ(i)]->prioridade < h->elementos[i]->prioridade)
            {
                aux=h->elementos[i];
                h->elementos[i]=h->elementos[FILHO_ESQ(i)];
                h->elementos[FILHO_ESQ(i)]=aux;
            }
            i=FILHO_ESQ(i);
        }

        if((i*2<h->tamanho) && (h->elementos[FILHO_DIR(i)]->prioridade < h->elementos[FILHO_ESQ(i)]->prioridade))
        {
            if(h->elementos[FILHO_DIR(i)]->prioridade < h->elementos[i]->prioridade)
            {
                aux=h->elementos[i];
                h->elementos[i]=h->elementos[FILHO_DIR(i)];
                h->elementos[FILHO_DIR(i)]=aux;
            }
            i=FILHO_DIR(i);
        }
        /** Caso especial, sem filho à direita **/
        if(FILHO_ESQ(i)== h->tamanho)
        {
            if(h->elementos[i]->prioridade > h->elementos[FILHO_ESQ(i)]->prioridade)
            {
                aux=h->elementos[i];
                h->elementos[i]=h->elementos[FILHO_ESQ(i)];
                h->elementos[FILHO_ESQ(i)]=aux;

            }
            break;

        }
    }
    /** CASO ESPECIAL, pois quando so tem 2 elementos a função de cima não é executada**/
    if(h->tamanho==2)
    {
        if(h->elementos[i]->prioridade > h->elementos[FILHO_ESQ(i)]->prioridade)
        {
            aux=h->elementos[i];
            h->elementos[i]=h->elementos[FILHO_ESQ(i)];
            h->elementos[FILHO_ESQ(i)]=aux;
        }
    }
    return str;
}

heap* heap_constroi(elemento* v, int n_elementos)
{

    int i;
    if(v==NULL || n_elementos<1)
        return NULL;

    heap *h;
    h=heap_nova(n_elementos);
    if(h==NULL)
        return NULL;

    for(i=0; i<n_elementos; i++)
    {
        if(heap_insere(h,v[i].valor, v[i].prioridade)==0)
            return NULL;
    }
    return h;
}

int heap_altera_prioridade(heap *h, int indice, int nova_prioridade)
{
    if(indice > h->tamanho || indice < 1 || nova_prioridade < 1 || h==NULL)
        return -1;

    int i= indice;
    int fim=1, prioridade_antiga= h->elementos[indice]->prioridade;
    elemento *aux;

    if(prioridade_antiga == nova_prioridade)
        return 1;

    h->elementos[indice]->prioridade=nova_prioridade;

    /** se alterar valor na raiz com um valor <= ao antigo não reordena**/
    if(indice!=1)
    {
        if((i*2)> h->tamanho)
        {
            /** ordena para cima, QUANDO É DOS ULTIMOS**/
            while(i>RAIZ)
            {
                if(h->elementos[PAI(i)]->prioridade > h->elementos[i]->prioridade)
                {
                    aux=h->elementos[PAI(i)];       /** troca o pai pelo elemento INDICE */
                    h->elementos[PAI(i)]=h->elementos[i];
                    h->elementos[i]=aux;
                }
                i=PAI(i);

            }
        }
        else
        {
            /** TROCA PARA CIMA OU PARA BAIXO*/

            while(i<= h->tamanho && i*2 <= h->tamanho ) /** estava i*2 **/
            {

                if(nova_prioridade>prioridade_antiga)
                {
                    if(FILHO_ESQ(i)<= h->tamanho)
                    {
                        if(FILHO_DIR(i) > h->tamanho)   /** tem filho esquerdo, mas nao tem filho direito**/
                        {
                            /** verifica que nao tem filho direito
                            ** Neste caso especial, se o F.E. tiver maior prioridade que o elemento[i]
                            ** então é porque esta ordenado, BREAK
                            ** Se F.E. tiver menor prioridade que o elemento[i]
                            ** entao troca e BREAK, pois chega ao fim **/
                            if(h->elementos[FILHO_ESQ(i)]->prioridade < h->elementos[i]->prioridade)
                            {
                                fim=2;
                                aux=h->elementos[FILHO_ESQ(i)];       // SWAP
                                h->elementos[FILHO_ESQ(i)]=h->elementos[i];
                                h->elementos[i]=aux;
                                break;
                            }
                            break;

                        }
                    }
                    /** verifica que não é o ultimo nó && se o F.E. < F.D. **/
                    if(i*2<h->tamanho && (h->elementos[FILHO_ESQ(i)]->prioridade < h->elementos[FILHO_DIR(i)]->prioridade) )
                    {
                        if(h->elementos[i]->prioridade > h->elementos[FILHO_ESQ(i)]->prioridade)
                        {
                            aux=h->elementos[FILHO_ESQ(i)];
                            h->elementos[FILHO_ESQ(i)]=h->elementos[i];
                            h->elementos[i]=aux;

                        }
                        i= FILHO_ESQ(i);

                        /** Quando o pai é menor e quando os filhos são maiores, PARA O CICLO**/
                        if((h->elementos[i]->prioridade > h->elementos[PAI(i)]->prioridade)&&(i*2<h->tamanho) && (h->elementos[i]->prioridade < h->elementos[FILHO_ESQ(i)]->prioridade))
                            break;
                    }
                    /** verifica que não é o ultimo nó && se o F.E. > F.D. **/
                    if(i*2<h->tamanho && (h->elementos[FILHO_ESQ(i)]->prioridade > h->elementos[FILHO_DIR(i)]->prioridade))
                    {
                        if(h->elementos[i]->prioridade > h->elementos[FILHO_DIR(i)]->prioridade)
                        {
                            aux=h->elementos[FILHO_DIR(i)];
                            h->elementos[FILHO_DIR(i)]=h->elementos[i];
                            h->elementos[i]=aux;
                        }
                        i= FILHO_DIR(i);

                        /** Quando o pai é menor e quando os filhos são maiores, PARA O CICLO**/
                        if((h->elementos[i]->prioridade > h->elementos[PAI(i)]->prioridade)&&(i*2+1<h->tamanho) && (h->elementos[i]->prioridade < h->elementos[FILHO_DIR(i)]->prioridade))
                            break;
                    }
                }

                /** verifica que não é dos ultimos**/
                if((fim!=2 && h->elementos[PAI(i)]->prioridade > h->elementos[i]->prioridade))
                {
                    while(i>RAIZ )
                    {
                        /** ORDENA PARA CIMA  QUANDO NÃO É O ULTIMO NÓ**/
                        if(h->elementos[PAI(i)]->prioridade > h->elementos[i]->prioridade)
                        {
                            aux=h->elementos[PAI(i)];
                            h->elementos[PAI(i)]=h->elementos[i];
                            h->elementos[i]=aux;
                        }
                        i=PAI(i);

                    }
                    break; // VAI PARAR QUANDO CHEGAR À RAIZ
                }
            }
        }
    }
    /** Quando estamos no indice==1 é um caso ESPECIAL, temos de fazer alguns ajustes**/
    if(indice==1 && (nova_prioridade > prioridade_antiga))
    {
        while(i<= h->tamanho && i*2 <= h->tamanho )
        {
            if(FILHO_ESQ(i)<= h->tamanho)
            {
                if(FILHO_DIR(i) > h->tamanho)  //tem filho esquerdo, mas nao tem filho direito
                {
                    if(h->elementos[FILHO_ESQ(i)]->prioridade < h->elementos[i]->prioridade)
                    {
                        aux=h->elementos[FILHO_ESQ(i)];       // SWAP
                        h->elementos[FILHO_ESQ(i)]=h->elementos[i];
                        h->elementos[i]=aux;
                        break;
                    }
                    break;
                }
            }
            /** verifica que não é o ultimo nó && se o F.E. < F.D. **/
            if(i*2<h->tamanho && (h->elementos[FILHO_ESQ(i)]->prioridade < h->elementos[FILHO_DIR(i)]->prioridade) )
            {
                if(h->elementos[i]->prioridade > h->elementos[FILHO_ESQ(i)]->prioridade)
                {
                    aux=h->elementos[FILHO_ESQ(i)];
                    h->elementos[FILHO_ESQ(i)]=h->elementos[i];
                    h->elementos[i]=aux;
                }
                i= FILHO_ESQ(i);

            }
            /** verifica que não é o ultimo nó && se o F.E. > F.D. **/
            if(i*2<h->tamanho && (h->elementos[FILHO_ESQ(i)]->prioridade > h->elementos[FILHO_DIR(i)]->prioridade))
            {
                if(h->elementos[i]->prioridade > h->elementos[FILHO_DIR(i)]->prioridade)
                {
                    aux=h->elementos[FILHO_DIR(i)];
                    h->elementos[FILHO_DIR(i)]=h->elementos[i];
                    h->elementos[i]=aux;
                }
                i= FILHO_DIR(i);
                /** previne numeros iguais **/
                if((FILHO_DIR(i)<h->tamanho) && (h->elementos[i]->prioridade == h->elementos[FILHO_DIR(i)]->prioridade))
                    break;
            }
        }
    }
    return 1;
}

void mostraHeap(heap *h, int indice)
{
    int i, nivel = 0;

    if (indice <= h->tamanho)
    {
        i = indice;
        while(i > 1)
        {
            i = i/2;
            nivel++;
        }

        mostraHeap(h, indice*2);

        for(i = 0; i < 3 * nivel; i++)
            printf("     ");

        printf("[i=%d] %s (%d)\n",indice,h->elementos[indice]->valor, h->elementos[indice]->prioridade);

        mostraHeap(h, indice*2+1);
    }
}

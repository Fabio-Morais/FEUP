#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "terra_incognita.h"
#include "tabdispersao.h"
#define tamanho_tabela 33339999
/** valor suficientemente grande para tentarmos correr a tabela com complexidade praticamente em O(1) quando são
    introduzidos valores muito grandes e/ou quando são gerados mapas enormes
Custa mais memoria, mas tem mais desempenho.
**/

tabela_dispersao *tabela;
int minx, miny;

void atualiza_POS(char mov, int *x, int *y);
int mapa_pos(int x, int y);

int main(int argc, char *argv[])
{
    int nExplorator, id, typus,  maxX=0, maxY=0,positio[MAX_EXPLORADORES][2], largura=0, altura=0;
    char movimentacao;
    tabela= tabela_nova(tamanho_tabela, hash_djbm);

    intro(argc, argv, &nExplorator, positio);

    minx= positio[0][0];
    miny= positio[0][1];

    while((movimentacao=explorator(&id, &typus))!= 'X')
    {

        /** MAXIMO**/
        if(positio[id][0]>maxX) maxX=positio[id][0];
        if(positio[id][1]>maxY) maxY=positio[id][1];

        /** MINIMO**/
        if(positio[id][0]<minx) minx=positio[id][0];
        if(positio[id][1]<miny) miny= positio[id][1];

        /** atualiza as variaveis**/
        atualiza_POS(movimentacao, &positio[id][0], &positio[id][1]);
        /** insere na hash **/
        tabela_insere(tabela, positio[id][0], positio[id][1], typus);
    }

    largura= maxX-minx+1;
    altura= maxY-miny+1;

    tabula(mapa_pos, largura,altura);
    veritas(mapa_pos, largura,altura);

    relinquo();
    tabela_apaga(tabela);

    return 0;
}

void atualiza_POS(char mov, int *x, int *y)
{
    switch(mov)
    {
    case 'N':
        (*y)--;
        break;
    case 'S':
        (*y)++;
        break;
    case 'E':
        (*x)++;
        break;
    case 'O':
        (*x)--;
        break;
    }
}


int mapa_pos(int x, int y)
{
    return tabela_valor(tabela, x+minx, y+miny);;
}



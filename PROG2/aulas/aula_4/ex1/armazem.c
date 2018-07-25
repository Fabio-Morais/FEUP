#include "armazem.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * funcoes do armazem
 */
/* alinea b) */
armazem* armazem_novo(int comprimento, int altura)
{
    armazem *arma;
    arma=malloc(sizeof(armazem));
    if(arma == NULL)
        return NULL;
    else{
        arma->altura=altura;
        arma->comprimento=comprimento;
        arma->contentores = fila_nova();
        return arma;
    }
}

/* alinea c) */
int armazem_vazio(armazem* armz)
{
     if(fila_tamanho(armz->contentores)==0)
        return 1;
    else
        return 0;
	/* devolve vazio */
}

/* alinea d) */
int armazem_cheio(armazem* armz)
{
    if((armz->comprimento == fila_tamanho(armz->contentores)) && (armz->altura == pilha_tamanho(fila_back(armz->contentores))))
            return 1;
    else
        return 0;
}

/* alinea e) */
int armazenar_contentor(armazem* armz, contentor* contr)
{
pilha *p= pilha_nova();
	if (armz == NULL || contr == NULL || armazem_cheio(armz)) return 0;
	if (armazem_vazio(armz)) fila_push(armz->contentores, pilha_nova());
	if(fila_back(armz->contentores)->tamanho== armz->altura) fila_push(armz->contentores, p);
	pilha_push(fila_back(armz->contentores), contr);
	return 1;
}

/* alinea f) */
contentor* expedir_contentor(armazem* armz)
{
if (armazem_vazio(armz) || pilha_top(fila_front(armz->contentores)) ==NULL) return NULL;
	contentor *c = contentor_novo(pilha_top(fila_front(armz->contentores))->destino, pilha_top(fila_front(armz->contentores))->valor);
	if(fila_front(armz->contentores)->tamanho <=1) fila_pop(armz->contentores);
	else pilha_pop(fila_front(armz->contentores));
	return c;}

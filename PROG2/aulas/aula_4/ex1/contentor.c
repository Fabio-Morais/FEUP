#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "contentor.h"

/* alinea a) */
/**
 *  \brief cria um novo contentor
 *  \param dest destino do contentor
 *  \param val valor das mercadorias no contentor
 *  \return apontador para o contentor; NULL se erro
 */
contentor* contentor_novo(char* dest, float val)
{
     contentor *result = malloc(sizeof(contentor));

        result->destino = malloc(strlen(dest)+1);
        if(result->destino)
        {
            strcpy(result->destino, dest);
            result->valor = val;
        }
        else
        {
            free(result);
            result = NULL;
        }

    return result;
}

/**
 *  \brief apaga contentor (liberta memoria correspondente)
 *  \param contr apontador para o contentor
 *  \remark se contr = NULL retorna sem fazer nada
 */
void contentor_apaga(contentor* contr)
{
free (contr);
free(contr->destino);
}

/**
 *  \brief imprime dados do contentor
 *  \param contr apontador para o contentor
 */
void contentor_imprime(contentor* contr)  {
	if (contr == NULL)
		printf("Contentor nulo\n");
	else
		printf("Destino: %s, valor da carga: %.2f K Euros\n", contr->destino, contr->valor);
}

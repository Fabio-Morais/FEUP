/*****************************************************************/
/*         Trabalho pratico 1 | PROG2 | MIEEC | 2017/18          */
/*****************************************************************/
/*                    FUNCOES A IMPLEMENTAR                      */
/*****************************************************************/

#include "cidades.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** Troca a posição do elemento n1 para n2
*   n1 e n2, posições a trocar
*   retorna o vetor trocado
*/
vetor *ordena(vetor *v, int n1, int n2)
{
    cidade aux;

    aux=v->elementos[n1];
    v->elementos[n1]=v->elementos[n2];
    v->elementos[n2]=aux;

    return v;
}

vetor* cidades_load(const char *nomef)
{
    FILE *ficheiro= fopen(nomef, "rb");
    vetor *vetorr=vetor_novo();
    cidade cidad; // ajudar no read do ficheiro
    if(ficheiro==NULL || vetorr==NULL)
    {
        printf("\t\nHouve um erro no ficheiro ou/e vetor criado\n"); //se houver erro na leitura do vetor novo, return null
        return NULL;
    }
    while(fread(&cidad, sizeof(cidad), 1, ficheiro)==1)
    {
        vetor_insere(vetorr, cidad, -1); //insere no fim
    }

    fclose(ficheiro);
    return vetorr;
}

int cidades_save(const vetor *vec, const char *nomef)
{
    FILE *ficheiro= fopen(nomef, "wb");
    int count;
    const cidade *cidad;
    const int tamanho=vetor_tamanho((vetor*)vec);

    if(ficheiro==NULL)
        return -1;

    for(count=0; count<tamanho; count++)
    {
        cidad=vetor_elemento((vetor*)vec,count);
        fwrite(cidad->nome,     sizeof(cidad->nome), 1, ficheiro);
        fwrite(cidad->pais,     sizeof(cidad->pais), 1, ficheiro);
        fwrite(&cidad->populacao, sizeof(cidad->populacao), 1, ficheiro);
        fwrite(&cidad->area,       sizeof(cidad->area), 1, ficheiro);
    }
    fclose(ficheiro);

    if(count!=tamanho)
        return -1;
    else
        return count;
}

int cidades_peek(const char *nomef, const char *nomecidade, cidade *resultado)
{
    FILE *fich=fopen(nomef, "rb");
    char nome[MAXSTR], pais[MAXSTR]; //variaveis para ajudar a enviar para resultado
    int populacao,area,count=0;

    while(fread(nome, sizeof(nome), 1, fich)==1)
    {
        if(!(strcmp(nome,nomecidade)))
        {
            fread(pais, sizeof(pais),1, fich);
            fread(&populacao, sizeof(populacao), 1, fich);
            fread(&area, sizeof(area), 1, fich);

            strcpy(resultado->nome, nome);
            strcpy(resultado->pais, pais);
            resultado->populacao=populacao;
            resultado->area=area;
            return count;
        }
        count++;
        fseek(fich, sizeof(cidade)-sizeof(nome), SEEK_CUR);      // para ir de nome em nome
    }

    return -1;   //ocorreu algum erro
}

int cidades_poke(const char *nomef, const char *nomecidade, cidade nova)
{
    FILE *ficheiro;
    int pos,count=0;
    cidade cid_aux;
    pos=cidades_peek(nomef,nomecidade, &cid_aux);       // descobrir posiçao da cidade com nome 'nomecidade'

    if(pos==-1)
        return -1;
    else
    {
        ficheiro= fopen(nomef, "r+b");
        if(ficheiro==NULL)
            return -1;
        else
        {
            while(fread(&cid_aux, sizeof(cid_aux), 1, ficheiro)==1)
            {
                if(count==pos)
                {
                    fseek(ficheiro, -sizeof(cidade), SEEK_CUR);         //volta apontador para trás para escrever por cima
                    fwrite(&nova, sizeof(cidade), 1, ficheiro);
                }
                count++;
            }
            fclose(ficheiro);
            return pos;
        }
    }
}

int cidades_resort(vetor *vec, char criterio)
{
                /** SELECTION SORT **/
    int a, b;
    const int tamanho=vetor_tamanho(vec);
    if(tamanho==-1)
    {
        printf("Erro no tamanho do vetor");
        return -1;
    }
    if(criterio != 'p' && criterio!= 'a')
    {
        printf("Critério não válido");
        return -1;
    }
    if(criterio=='p') //ordena por país
    {
        for(a=0; a<tamanho; a++)
        {
            for(b=a+1; b<tamanho; b++)
            {
                if(strcmp(vec->elementos[a].pais, vec->elementos[b].pais)>0)
                    vec=ordena(vec, a, b);   // troca elementos

                if(strcmp(vec->elementos[a].pais, vec->elementos[b].pais)==0)
                {
                    //então ordena por população
                    if(vec->elementos[a].populacao > vec->elementos[b].populacao)
                        vec=ordena(vec, a, b);
                }
            }

        }
        return 0;
    }

    if(criterio=='a') //ordena por população
    {
        for(a=0; a<tamanho; a++)
        {
            for(b=a+1; b<tamanho; b++)
            {
                if(vec->elementos[a].area > vec->elementos[b].area)
                    vec=ordena(vec, a, b);

                if(vec->elementos[a].area ==  vec->elementos[b].area)
                {
                    if(vec->elementos[a].populacao > vec->elementos[b].populacao)
                        vec=ordena(vec, a, b);    //troca elementos
                }
            }
        }
        return 0;
    }
    return -1;
}

char** cidades_similar (vetor *vec, const char *nomecidade, int deltapop, int *nsimilares)
{
    int i, pop_ref, pop_min, pop_max, aux=-1;
    char **v;
    v=(char **)malloc((vec->tamanho)*sizeof(char*));
    const int tamanho=vetor_tamanho(vec);
    *nsimilares=0;
    if(tamanho==-1)
    {
        printf("Erro no tamanho do vetor");
        return NULL;
    }
    for(i=0; i<tamanho; i++)                                          //procura a posiçao do nomecidade no vetor
    {
        if(strcmp(vec->elementos[i].nome, nomecidade)==0)
        {
            aux=5;   //saber quando encontra algo
            break;    //i= posição nomecidade
        }
    }
    pop_ref=vec->elementos[i].populacao;
    pop_min=pop_ref-deltapop;
    pop_max=pop_ref+deltapop;

    for(i=0; i<tamanho; i++)
    {
        if(vec->elementos[i].populacao>=pop_min && vec->elementos[i].populacao<=pop_max)
        {
            if(strcmp(vec->elementos[i].nome, nomecidade)!=0)         //exclui a cidade encontrada 'nomecidade'
            {
                v = (char **)realloc(v, ((*nsimilares)+1)* sizeof(char*));
                v[(*nsimilares)] = (char *)malloc(strlen((vec->elementos[i].nome)+1)*sizeof(char));
                strcpy(v[(*nsimilares)],vec->elementos[i].nome);
                (*nsimilares)++;
            }
        }
    }
    if((*nsimilares)==0 || aux!=5)
        return NULL;

    else
        return v;
        free(v);
}


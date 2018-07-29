#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "pilha.h"

#define BUFFER 256

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2 ***/
float *avalia_expressoes(FILE *ficheiro, int *N)
{

 char str[BUFFER];
    pilha* p;
    float *v=NULL;
    p=pilha_nova();
    (*N)=0;
    int i,n=0,z=0;
    float a,b,c;

    while(fgets(str,BUFFER,ficheiro)!=NULL){
        for(i=0;i<strlen(str);i++){
            if(str[i]>='0'&&str[i]<='9'){
                pilha_push(p,atof(str+i));
            }
            else
            if(str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'){
                a=pilha_top(p);
                pilha_pop(p);
                b=pilha_top(p);
                pilha_pop(p);
                switch(str[i]){
                    case '+': c=b+a;break;
                    case '-': c=b-a;break;
                    case '*': c=b*a;break;
                    case '/': c=b/a;break;
                }
                pilha_push(p,c);
            }
            else
            if(str[i]=='\n'){
                v=realloc(v,(n+1)*sizeof(float));
                v[n]=pilha_top(p);
                n++;
            }
        }
    }
    (*N)=n;
    pilha_apaga(p);
	return v;
}

	/****************************************************/
	/*     Funcoes ja implementadas (nao modificar)     */
	/****************************************************/

#define BUFFER 256

int main()
{
	FILE *fin;
	float *resultados;
	char expressao[BUFFER];
	int i, n = 0;

	fin = fopen("expressoes.txt", "r");
	if (fin == NULL)
	{
		printf("Erro ao abrir ficheiro.\n");
		return 1;
	}

	if ((resultados = avalia_expressoes(fin, &n)) != NULL)
	{
		rewind(fin);
		for (i = 0; i < n && fgets(expressao, BUFFER, fin) != NULL; i++)
		{
			expressao[strlen(expressao) - 1] = '\0';
			printf("%s -> %f\n", expressao, resultados[i]);
		}
	}
	else
		printf("Funcao retornou erro.\n");

	fclose(fin);

	return 0;
}

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
	char nome[100];
	int pop2001;
	int pop2012;
}
municipio;

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2.1 ***/
municipio *lerFicheiro(FILE *ficheiro, int *num_municipios) 
{
    int n=0;
    municipio *v;
    v=malloc(sizeof(municipio));
    while(fscanf(ficheiro, "%s %d %d", v[n].nome, &v[n].pop2001, &v[n].pop2012 )!= EOF)
    {
        n++;
        v=realloc(v, sizeof(municipio)*(n+1));
    }
    *num_municipios = n;
    return v;
}

/*** problema 2.2 ***/
void gerarRelatorio(FILE *ficheiro, municipio *resultados, int num_municipios)
{
 
int i, j,res, maior, maiorind, lim=500000;
for(j=0; j<10; j++){
	maior=0;
	for(i=0; i<num_municipios; i++)
	{
		res= resultados[i].pop2001-resultados[i].pop2012;
		if(res>maior && res<lim)
		{
			maior=res;
			maiorind=i;
		}	
	}
		lim=maior;
   fprintf(ficheiro, "%s, %d\n", resultados[maiorind].nome, maior);
   }

}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{
	FILE *fin, *fout;
	municipio *resultados;
	int n;

	fin = fopen("municipios.txt", "r");
	if(fin == NULL)
		return 1;

	fout = fopen("relatorio.txt", "w");
	if(fout == NULL)
		return 1;

	resultados = lerFicheiro(fin, &n);
	gerarRelatorio(fout, resultados, n);

	fclose(fin);
	fclose(fout);
	free(resultados);

	return 0;
}

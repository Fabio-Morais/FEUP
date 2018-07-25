#include <stdio.h>
#include <stdlib.h>
void imprime (int *v, int n, int *vp, int *vi, int *a, int *b)
{int i;
printf("\n\nvetor original  [");
    for (i=0; i<n; i++)
    {
        printf(" %d ", v[i]);
    }
printf("]\n\n");
printf("\n\nvetor par  [");

    for (i=0; i<*a; i++)
    {
        printf(" %d ", vp[i]);
    }
printf("]\n\n");

    printf("\n\nvetor impar  [");

    for (i=0; i<*b; i++)
    {
        printf(" %d ", vi[i]);
    }
    printf("]\n\n");

}

void preenche (int *v, int n)
{ int i;
    for (i=0; i<n; i++){
    printf("introduza o elemento %d ", i+1);
    scanf("%d", &v[i]);}
}

void pari (int *v, int *vp,int *vi, int n, int *a, int *b)
{
    int  i;
    for (i=0; i<n; i++)
    {
        if(v[i]%2==0){
            vp[*a]=v[i];
            *a+=1;
            printf("\n\n numero---- par %d", *a);
        }
        else
        {
        vi[*b]=v[i];
        *b+=1;

        }

    }
    vp= (int *)realloc(vp,*a*sizeof(int));
    vi= (int *)realloc(vi,*b*sizeof(int));

}

int main()
{
int *v,vp[100], vi[100], x,a=0, b=0, *pt, *pt1 ;
pt=&a;
pt1=&b;


printf("numero de elementos? ");
scanf("%d", &x);
v = (int *)malloc(x* sizeof(int));
preenche(v, x);
pari(v,vp, vi, x,pt,pt1);
imprime(v, x, vp, vi, pt, pt1);
 return 0;
}

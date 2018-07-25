#include <stdio.h>
#include <stdlib.h>

unsigned int fib3(unsigned int n, unsigned int * nchamadas, unsigned int resultados[])
{
    (*nchamadas)++;
    if(resultados[n]!=0)
        return resultados[n];
    printf("fib(%d)", n);


    if(n==0)
        return 0;
    if(n==1)
        return 1;
    if(n>1)
    {

        return resultados[n]=(fib3(n-1, (nchamadas), resultados) + fib3(n-2, (nchamadas), resultados));
    }

    return 0;

}

unsigned int fib2(unsigned int n, unsigned int * nchamadas)
{
    (*nchamadas)++;
    printf("fib(%d)", n);
    if(n==0)
        return 0;
    if(n==1)
        return 1;
    if(n>1)
        return fib2(n-1, (nchamadas)) + fib2(n-2, (nchamadas));

    return 0;

}

int fib(int i)
{
    if(i==0)
        return 0;
    if(i==1)
        return 1;
    if(i>1)
        return fib(i-1)+ fib(i-2);
    return 0;
}

int main()
{
    int i, x, n=0, resultados[100]= {0};
    printf("N\n");
    scanf("%d", &i);
    x=fib(i);
    printf("\n->%d\n\n", x);
    x=fib2(i, &n);
    printf("\n->%d: %d", x, n);

    return 0;
}

/*
 * Factorial.h
 */

#ifndef FACTORIAL_H_
#define FACTORIAL_H_

#include "Defs.h"

/*Calcula o factorial de um valor de entrada n usando recursividade*/
int factorialRecurs(int n)
{
	if(n == 0)
	{
		return 1;
	}
	else
		return n* factorialRecurs(n-1);
}

/*Calcula o factorial de um valor de entrada n usando programação dinâmica*/
int factorialDinam(int n)
{
	if(n==0)
	{
		return 1;
	}
	int aux = 1;
	int f=1;
	while( f<= n)
	{
		aux = aux* f;
		f++;
	}
	return aux;
}
/*Calcula o factorial de todos os valores até n (n >=0), colocando os resultados numa array*/
int* factorialDinamArray(int n)
{

	int* fact = new int[n+1];

	fact[0] = 1;

	for(int i = 1; i <=n; i++)
	{
		fact[i] = i*fact[i-1];
	}
	return fact;

}

#endif /* FACTORIAL_H_ */

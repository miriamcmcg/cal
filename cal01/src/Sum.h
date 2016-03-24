/*
 * Sum.h
 */

#ifndef SUM_H_
#define SUM_H_

#include "Defs.h"

/* Calcula, numa sequência de n números (n > 0), para cada subsequência de m números (m <= n, m > 0),
 * o índice i a partir do qual a soma s dos valores dessa subsequência é mínimo.
 *
 * Argumentos:
 * 	sequence - Array com a sequência
 * 	size - Tamanho da sequência
 *
 * Devolve:
 * Uma string que contém com a indicação do índice i e somatório s, para cada m
 * i[0],s[0];i[1],s[1],i[2],s[2]...
 * Exemplo: 1,4;9,1;11,2;18,1;22,0;
 */
string calcSum(int* sequence, int size)
{
//	vector<int> sum(size);
//	vector<int> minInd(size,-1);
//	vector<int> min(size);
//
//	for(int i = 0; i < size; i++)
//	{
//		for(int j = 0; j < size; j++)
//		{
//			if(i+j >= size)
//				break;
//			if(j == 0)
//			{
//				sum[i] = sequence[i];
//			}
//			else
//				sum[i] = sum[i] + sequence[i+j];
//			if(sum[i] < min[j] || minInd[j] == -1)
//			{
//				min[j] = sum[i];
//				minInd[j] = i;
//			}
//
//		}
//	}
//
//	stringstream ss;
//		for (int i = 0; i < size; i++)
//			ss << min[i] << "," << minInd[i] << ";";
//
//		return ss.str();

}

#endif /* SUM_H_ */

/*
 * Sum.h
 */

#ifndef SUM_H_
#define SUM_H_

#include "Defs.h"

/* Calcula, numa sequ�ncia de n n�meros (n > 0), para cada subsequ�ncia de m n�meros (m <= n, m > 0),
 * o �ndice i a partir do qual a soma s dos valores dessa subsequ�ncia � m�nimo.
 *
 * Argumentos:
 * 	sequence - Array com a sequ�ncia
 * 	size - Tamanho da sequ�ncia
 *
 * Devolve:
 * Uma string que cont�m com a indica��o do �ndice i e somat�rio s, para cada m
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

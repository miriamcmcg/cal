/*
 * Change.h/
 */

#ifndef CHANGE_H_
#define CHANGE_H_

#include "Defs.h"

/* Calcula o troco para n cêntimos, utilizando o número mínimo de moedas, tendo apenas disponíveis
 * moedas de 1, 2 e 5 cêntimos.
 *
 * Devolve:
 * Uma string que contém com a indicação, para cada n, a combinação de moedas a utilizar.
 * Por exemplo: troco de 1 cêntimo: 1 moeda de 1
 * 				troco de 2 cêntimos: 1 moeda de 2
 * 				troco de 3 cêntimos: 1 moeda de 1, 1 moeda de 2
 * 				(...)
 * A string devolvida representar os valores das moedas (separadas por virgula) para cada n (separado por ponto e vírgula)
 * Exemplo: 1;2;1,2;2,2;5;1,5;...
 * */
string calcChange(int n)
{

	vector< vector<string> > change(n+1);
		change[1].push_back("1");

		for (unsigned i = 2; i < change.size(); i++) {

			vector<string> local;
			unsigned start;
			if (change[i-1][0] == "1") {
				local.push_back("2");
				start = 1;
			}
			else if (change[i-1][0] == "2") {

				if (change[i-1].size() > 1 && change[i-1][1] == "2") {
					local.push_back("5");
					start = 2;
				}
				else {
					local.push_back("1");
					start = 0;
				}
			}
			else if (change[i-1][0] == "5") {

				local.push_back("1");
				start = 0;
			}

			for (unsigned j = start; j < change[i-1].size(); j++)
				local.push_back(change[i-1][j]);

			change[i] = local;
		}


		string res;
		for (int i = 1; i <= n; i++) {
			for (unsigned j = 0; j < change[i].size(); j++) {

				res += change[i][j];
				if (j != change[i].size() - 1)
					res += ",";
			}

			res += ";";
		}

		return res;
}

#endif /* CHANGE_H_ */

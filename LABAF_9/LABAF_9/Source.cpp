#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>

/*
			Probleme de optimizare

Sunt probleme care cer determinarea unei solutii
(supuse sau nu unor restrictii) pentru care o
anumita functie(numita functie OBIECTIV) are valoare
MINIMA/MAXIMA.

	A.METODA GREEDY
	B.PROGRAMARE DINAMICA

A.METODA GREEDY----------------

-> solutia se construieste pas cu pas;
-> la GREEDY nu se revine asupra unei alegeri facute, fata de metoda BACKTRACKING;
-> algoritmii sunt usor de implementat, si eficienti(AVANTAJ)
-> nu pentru orice tip de problema METODA GREEDY garanteaza obtinerea solutiei optime(DEZAVANTAJ)

	ALGORITM:
	C - multime de candidati
	S <- MULT. VIDA
	while( S!= solutie && C!= mult. vida)
	{
		n <- cel mai bun/promitator element al lui c
		if( S U {x}(S reunit cu x) constituie o solutie acceptabila)
			S <- S U {x}
		C = C \ {x} (c fara elementul x)

	}
	if( S == solutie)
		afisare(S)
	else
		"NU exista solutii"

OBS: Este util ca C sa fie sortata conform unui criteriu specific problemei.
Astfel elementul cel mai  promitator va fi primul la rand.
*/

/*
------------PROBLEMA PLATII UNEI SUME------------

S -> nr MINIM de bancnote
S = 345		b = {1,5,100,10,500,200,20}  --sortam descrescator--> {500,200,100,20,10,5,1}

Numar minim de bancnote am daca le folosesc pe cele cu VALOARE MARE:
	
	S = 345  1 * 200 => S = 145
			 1 * 100 => S = 45
			 2 * 20  => S = 5
			 1 * 5   => S = 0.
    -------------------------------
			R = 5 bancnote

GREEDY NU GRANTEAZA SOLUTIA OPTIMA.
-----------------------------------
Contra exemplu : S = 26  {20,13,5,1}
		Greedy : 1 * 20 + 1 * 5 + 1 * 1 => 3 bancnote
		Sol. optima: 2 * 13 => 2 bancnote.
*/
/*
PROBLEMA BANCNOTE VAR 2

500 200 100 50 20 10  5  1
 2   1   5   7  3 20 20 10
*/

struct Bancnota
{
	int valoare, numar;
};

bool operator_valoare(Bancnota b1, Bancnota b2)
{
	return (b1.valoare > b2.valoare);
}

int main()
{
	int i = 0, nr_bancnote = 0, S;
	std::vector<Bancnota> bancnote;
	int n;
	std::cin >> n >> S;
	bancnote.resize(n);
	for (int j = 0; j < bancnote.size(); j++)
		std::cin >> bancnote[j].valoare >> bancnote[j].numar;
	//--------------------pana aici e acelasi cod---------------------
	
	/*std::sort(bancnote.begin(), bancnote.end(), operator_valoare);
	while (S && i < bancnote.size())
	{
		if (bancnote[i].valoare <= S)
		{
			int banc_disp = std::min(bancnote[i].numar, S / bancnote[i].valoare);
			nr_bancnote += banc_disp;
			S -= banc_disp * bancnote[i].valoare;
		}
		i++;
	}
	if (S)
		std::cout << "Nu exista solutie!";
	else
		std::cout << nr_bancnote;
	*/
	
	//--------------------ca sa mearga problema asta modifica vectorul de mai sus-------------------------

	/*std::sort(bancnote.begin(), bancnote.end(), std::greater<int>());
	while (S)
	{
		if (bancnote[i] <= S)
		{
			nr_bancnote += S / bancnote[i];
			S -= (S / bancnote[i])*bancnote[i];
		}
		i++;
	}
	std::cout << nr_bancnote;
	*/


	return 0;
}
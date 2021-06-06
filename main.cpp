#include <math.h>
#include<iostream>
using namespace std;


#include "lentier.h"

int main()
{
	//Lexique {Principal}

	lentier p;

//Algorithme {Principal}
  //Debut
	p.size = 3;
	p.p = new unsigned int[p.size];
	p.p[0] = 31975516993;
	p.p[1] = 255446423;
	p.p[2] = 66926;

	char* dec[25] = { 0 };
	*dec = lentier2dec(p);
	for (int i = 0; i < 25; i++) {
		cout << dec[i];
	}
  //Fin	

	delete[] p.p, dec;

	system("pause");
	return 0;
}
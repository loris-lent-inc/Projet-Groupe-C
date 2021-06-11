#include <math.h>
#include<iostream>
using namespace std;


#include "lentier.h"

int main()
{
	//Lexique {Principal}

	unsigned int a[3] = { 3197516993, 255446423, 66926 };
	unsigned int b[3] = { 3197516993, 255446423, 66926 };
	lentier aa;
	aa.p = a;
	aa.size = 3;
	lentier bb;
	bb.p = b;
	bb.size = 3;
	lentier res;
	res = div_eucl(aa, bb);
	Affiche_lentier(res);

	/*char* lent = (char*)"1234567891011121314151617"; //18192021222324252627282930";

	lentier Lent, dix;

	//Algorithme {Principal}
	  //Debut

	Lent = dec2lentier(lent);

	/*
	Lent.size = 3;
	Lent.p = new unsigned int[3];
	Lent.p[0] = 3197516993;
	Lent.p[1] = 255446423;
	Lent.p[2] = 66926;
	
	char* dec = new char[50];
	dec = lentier2dec(Lent);

	for (int i = 0; i < 25; i++) {
		cout << dec[i];
	}
	cout << endl << endl;*/
	
  //Fin	

	//delete[] Lent.p, dec;

	system("pause");
	return 0;
}
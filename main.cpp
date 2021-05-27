#include <math.h>
#include<iostream>
using namespace std;


#include "lentier.h"

int main()
{
	//Lexique {Principal}

	char L0[50] = {'1', '2', '3'};
	char L1[50] = {'4', '5', '6'};
	char R0[50] = {'7', '8', '9'};

	test_vector vect1 = {"add_lentier"};

//Algorithme {Principal}
  //Debut
	vect1.a = dec2lentier(L0);
	vect1.b = dec2lentier(L1);
	vect1.expec_res = dec2lentier(R0);

	vect1.res = add_lentier(vect1.a, vect1.b);
	v_test(vect1);
  //Fin	

	delete_vector(vect1);

	system("pause");
	return 0;
}
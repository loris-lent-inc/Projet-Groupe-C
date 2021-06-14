#include<string>
#include<iostream>

using namespace std;

#include"lentier.h"

//Une fonction supplémentaire, déclarée implicitement pour gérer les saisies
//inutile si vous avez procédé autrement (voir fonction main)
/*
Noms: FB
R: Dans le main.cpp fourni, les saisies de chaînes par l'utilisateur sont faites sous forme de "string", il faut les convertir en char* pour être utilisées ensuite dans les autres fonctions.
Le rôle de cette fonction est de créer la chaîne de caractère (type char*) correspondant à la chaîne (de type string) saisie par l'utilisateur
Si vous n'avez pas procédé comme ça, il suffit de commenter cette déclaration (ainsi que la définition dans le fichier .cpp et l'appel dans le fichier main.cpp
E: s: la chaîne saisie par l'utilisateur, de type string (typiquement saisie avec getline(cin,s))
S: la chaine de caractère de type char* correspondant à s.
*/
char*  stringtochare(string s)
{
  char * str=new char[s.length()+1];
  strcpy(str,s.c_str());
  return str;
}


int main()
{
  char menu;
  unsigned int choix;
  lentier a,b,N,res;
  string s;
  char * str;
  cout<<"\t\t\t***********************************************************"<<endl;
  cout<<"\t\t\t* Programme de calcul sur les entiers arbitrairement long *"<<endl;
  cout<<"\t\t\t*                                                         *"<<endl;
  cout<<"\t\t\t*  Réalisé par les étudiants de CiTiSE1 (promo 2020-2021) *"<<endl;
  cout<<"\t\t\t***********************************************************"<<endl<<endl;
  do
    {
      cout<<"Que voulez-vous faire?"<<endl;
      cout<<"\t1. Addition"<<endl;
      cout<<"\t2. Soustraction"<<endl;
      cout<<"\t3. Multiplication classique"<<endl;
      cout<<"\t4. Division euclidienne (calcul du reste)"<<endl;
      cout<<"\t5. Multiplication modulaire"<<endl;
      cout<<"\t6. Exponentiation modulaire"<<endl;
      cout<<"Saisissez votre choix:";
      cin>>choix;
      while(choix<1 || choix >6)
	{
	  cout<<"Erreur de saisie, veuillez ressaisir un choix compris entre 1 et 6:";
	  cin>>choix;
	}
      
      switch(choix)
	{
	case 1: 
	  //Addition
	  cout<<"-------------------------------------------"<<endl;
	  cout<<"| Addition d'entiers multiprécision: a+b= |"<<endl;
	  cout<<"-------------------------------------------"<<endl;
	  cout<<"Entrer le premier opérande (a=)"<<endl;
	  //Si vous avez procédé différemment pour la saisie, il est tout à fait possible de commenter ces 3 lignes
	  cin.ignore();//Pour récupérer le caractère de retour à la ligne
	  getline(cin,s);//récupération de l'entrée au format string
	  str=stringtochare(s);//conversion en char *
	  a=dec2lentier(str);
	  //La taille de a devrait etre ajustée
	  delete[] str;

	  cout<<"Entrer le deuxième opérande (b=)"<<endl;
	  //Si vous avez procédé différemment pour la saisie, il est tout à fait possible de commenter ces 3 lignes
	  getline(cin,s);//récupération de l'entrée au format string
	  str=stringtochare(s);//conversion en char *
	  b=dec2lentier(str);
	  delete[] str;

	  res=add_lentier(a,b);
	  str=lentier2dec(res);
	  cout<<"a+b="<<str<<endl;
	  delete[] str;
	  delete[] a.p;
	  delete[] b.p;
	  delete[] res.p;
	  break;

	case 2: 
	  //Soustraction
	  cout<<"-------------------------------------------------------"<<endl;
	  cout<<"Soustraction d'entiers multiprécision: a-b= (avec a>=b)"<<endl;
	  cout<<"-------------------------------------------------------"<<endl;
	  
	  cout<<"Entrer le premier opérande (a=)"<<endl;
	  //Si vous avez procédé différemment pour la saisie, il est tout à fait possible de commenter ces 3 lignes
	  cin.ignore();//Pour récupérer le caractère de retour à la ligne
	  getline(cin,s);//récupération de l'entrée au format string
	  str=stringtochare(s);//conversion en char *
	  a=dec2lentier(str);
	  delete[] str;
	  
	  cout<<"Entrer le deuxième opérande (b=)"<<endl;
	  //Si vous avez procédé différemment pour la saisie, il est tout à fait possible de commenter ces 3 lignes
	  getline(cin,s);//récupération de l'entrée au format string
	  str=stringtochare(s);//conversion en char *
	  b=dec2lentier(str);
	  delete[] str;
	  
	  //Correction de saisie lorsque a<b
	  while(cmp_lentier(a,b)==-1)
	    {
	      delete[] a.p;
	      delete[] b.p;
	      cout<<"ATTENTION: le premier opérande doit être supérieur ou égal au deuxième opérande"<<endl;
	      cout<<"Entrer le premier opérande (a=)"<<endl;
	      //Si vous avez procédé différemment pour la saisie, il est tout à fait possible de commenter ces 3 lignes
	      getline(cin,s);//récupération de l'entrée au format string
	      str=stringtochare(s);//conversion en char *
	      a=dec2lentier(str);
	      delete[] str;

	      cout<<"Entrer le deuxième opérande (b=)"<<endl;
	      //Si vous avez procédé différemment pour la saisie, il est tout à fait possible de commenter ces 3 lignes
	      getline(cin,s);//récupération de l'entrée au format string
	      str=stringtochare(s);//conversion en char *
	      b=dec2lentier(str);
	      delete[] str;
	    }
	  res=sub_lentier(a,b);
	  str=lentier2dec(res);
	  cout<<"a-b="<<str<<endl;
	  delete[] str;
	  delete[] a.p;
	  delete[] b.p;
	  delete[] res.p;
	  break;

	case 3: 
	  //Multiplication
	  cout<<"-------------------------------------------------"<<endl;
	  cout<<"| Multiplication d'entiers multiprécision: a*b= |"<<endl;
	  cout<<"-------------------------------------------------"<<endl;
	  cout<<"Entrer le premier opérande (a=)"<<endl;
	  cin.ignore();//Pour récupérer le caractère de retour à la ligne
	  getline(cin,s);//récupération de l'entrée au format string
	  str=stringtochare(s);//conversion en char *
	  a=dec2lentier(str);
	  delete[] str;

	  cout<<"Entrer le deuxième opérande (b=)"<<endl;
	  getline(cin,s);//récupération de l'entrée au format string
	  str=stringtochare(s);//conversion en char *
	  b=dec2lentier(str);
	  delete[] str;

	  res=mult_classique(a,b);
	  str=lentier2dec(res);
	  cout<<"a*b="<<str<<endl;
	  delete[] str;
	  delete[] a.p;
	  delete[] b.p;
	  delete[] res.p;
	  break;

	case 4: 
	  //Division (reste)
	  cout<<"-------------------------------------------------------------------"<<endl;
	  cout<<"| Division euclidienne (reste) d'entiers multiprécision: a mod b= |"<<endl;
	  cout<<"-------------------------------------------------------------------"<<endl;
	  cout<<"Entrer le premier opérande (a=)"<<endl;
	  cin.ignore();//Pour récupérer le caractère de retour à la ligne
	  getline(cin,s);//récupération de l'entrée au format string
	  str=stringtochare(s);//conversion en char *
	  a=dec2lentier(str);
	  delete[] str;

	  cout<<"Entrer le deuxième opérande (b=)"<<endl;
	  getline(cin,s);//récupération de l'entrée au format string
	  str=stringtochare(s);//conversion en char *
	  b=dec2lentier(str);
	  delete[] str;

	  //si a<b
	  if(cmp_lentier(a,b)==-1)
	    {
	      //copie champ à champ
	      res=a;
	      cout<<"Remarque: si a<b, alors a mod b=a (pas de calcul à faire)"<<endl;
	      str=lentier2dec(res);
	    }
	  else
	    {
	      res=div_eucl(a,b);
	      str=lentier2dec(res);
	      delete[] res.p;
	    }
	  cout<<"a mod b="<<str<<endl;
	  delete[] str;
	  delete[] a.p;
	  delete[] b.p;
	  break;

	case 5: 
	  //Multiplication modulaire
	  cout<<"---------------------------------------------------------------------"<<endl;
	  cout<<"|  Multiplication modulaire d'entiers multiprécision: a*b mod N=    |"<<endl;
	  cout<<"|  avec a<N et b<N,                                                 |"<<endl;
	  cout<<"|  sinon ils peuvent être réduits avant: a mod N (option 4 du menu) |"<<endl;
	  cout<<"---------------------------------------------------------------------"<<endl;
	  cout<<"Entrer le module (N=)"<<endl;
	  cin.ignore();//Pour récupérer le caractère de retour à la ligne
	  getline(cin,s);//récupération de l'entrée au format string
	  str=stringtochare(s);//conversion en char *
	  N=dec2lentier(str);
	  delete[] str;
	  
	  cout<<"Entrer le premier opérande (a=)"<<endl;
	  getline(cin,s);//récupération de l'entrée au format string
	  str=stringtochare(s);//conversion en char *
	  a=dec2lentier(str);
	  delete[] str;

	  //Lorsque N<a il faut réduire a modulo N avant d'appeler la fonction
	  while(cmp_lentier(N,a)!=1)
	    {
	      delete[] a.p;
	      cout<<"ATTENTION: a doit être <N, vous pouvez réduire a modulo N au préalable avec l'option 4 du menu"<<endl;
	      cout<<"Entrer le premier opérande (a=)"<<endl;
	      getline(cin,s);//récupération de l'entrée au format string
	      str=stringtochare(s);//conversion en char *
	      a=dec2lentier(str);
	      delete[] str;
	    }
	  
	  cout<<"Entrer le deuxième opérande (b=)"<<endl;
	  getline(cin,s);//récupération de l'entrée au format string
	  str=stringtochare(s);//conversion en char *
	  b=dec2lentier(str);
	  delete[] str;

	  //Lorsque N<b il faut réduire b modulo N avant d'appeler la fonction
	  while(cmp_lentier(N,b)!=1)
	    {
	      delete[] b.p;
	      cout<<"ATTENTION: b doit être <N, vous pouvez réduire a modulo N au préalable avec l'option 4 du menu"<<endl;
	      cout<<"Entrer le deuxième opérande (b=)"<<endl;
	      getline(cin,s);//récupération de l'entrée au format string
	      str=stringtochare(s);//conversion en char *
	      b=dec2lentier(str);
	      delete[] str;
	    }
	  res=mul_mod(a,b,N);      
	  delete[] a.p;
	  delete[] b.p;
	  str=lentier2dec(res);
	  cout<<"a*b mod N="<<str<<endl;
	  delete[] str;
	  break;

	case 6: 
	  //Exponentiation modulaire
	  cout<<"---------------------------------------------------------------------"<<endl;
	  cout<<"|  Exponentiation modulaire d'entiers multiprécision: a^e mod N=    |"<<endl;
	  cout<<"|  avec a<N et e<N,                                                 |"<<endl;
	  cout<<"|  sinon ils peuvent être réduits avant: a mod N (option 4 du menu) |"<<endl;
	  cout<<"---------------------------------------------------------------------"<<endl;
	  cout<<"Entrer le module (N=)"<<endl;
	  cin.ignore();//Pour récupérer le caractère de retour à la ligne
	  getline(cin,s);//récupération de l'entrée au format string
	  str=stringtochare(s);//conversion en char *
	  N=dec2lentier(str);
	  delete[] str;
	  
	  cout<<"Entrer le premier opérande (a=)"<<endl;
	  getline(cin,s);//récupération de l'entrée au format string
	  str=stringtochare(s);//conversion en char *
	  a=dec2lentier(str);
	  delete[] str;

	  //Lorsque N<a il faut réduire a modulo N avant d'appeler la fonction
	  while(cmp_lentier(N,a)!=1)
	    {
	      delete[] a.p;
	      cout<<"ATTENTION: a doit être <N, vous pouvez réduire a modulo N au préalable avec l'option 4 du menu"<<endl;
	      cout<<"Entrer le premier opérande (a=)"<<endl;
	      getline(cin,s);//récupération de l'entrée au format string
	      str=stringtochare(s);//conversion en char *
	      a=dec2lentier(str);
	      delete[] str;
	    }
	  
	  cout<<"Entrer l'exposant (e=)"<<endl;
	  getline(cin,s);//récupération de l'entrée au format string
	  str=stringtochare(s);//conversion en char *
	  b=dec2lentier(str);
	  delete[] str;
	  
	  //Lorsque N<b il faut réduire b modulo N avant d'appeler la fonction
	  while(cmp_lentier(N,b)!=1)
	    {
	      delete[] b.p;
	      cout<<"ATTENTION: e doit être <N, vous pouvez réduire a modulo N au préalable avec l'option 4 du menu"<<endl;
	      cout<<"Entrer l'exposant (e=)"<<endl;
	      getline(cin,s);//récupération de l'entrée au format string
	      str=stringtochare(s);//conversion en char *
	      b=dec2lentier(str);
	      delete[] str;
	    }
	  res=exp_mod(a,b,N);      
	  delete[] a.p;
	  delete[] b.p;
	  str=lentier2dec(res);
	  cout<<"a^b mod N="<<str<<endl;//Attention, on affiche la puissance avec la notation ^, ce n'est en rien un xor ici!
	  delete[] str;
	  break;
	}

      cout<<"Souhaitez vous effectuer une autre opération? (o/n): ";
      cin>>menu;
    }while(menu=='o');
  
  cout<<"**************************************************************************************************"<<endl;
  cout<<"* Merci d'avoir utilisé notre programme de calcul sur les grands entiers de longueur arbitraire! *"<<endl;
  cout<<"**************************************************************************************************"<<endl;
  return 0;
}

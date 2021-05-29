#include <math.h>
#include <iostream>

using namespace std;

#include "lentier.h"


void Affiche_lentier(lentier a) {
    cout << "{";
    for (unsigned int u = 0; u < a.size - 1; u++) {
        cout << a.p[u] << ",";
    }
    cout << a.p[a.size - 1] << "}" << endl;
}


void lAdjust(lentier& a) {
    unsigned int i = a.size;

    while (i) {
        if (*&a.p[i - 1] == 0) {
            i--;
        }
        else{
            a.size = i;
            i = 0;
        }
    }
}


void lAdjust_realloc(lentier& a) {
    lAdjust(a);
    
    lentier new_a;
    new_a.size = a.size;
    new_a.p = new unsigned int[a.size];

    for (unsigned int i = 0; i < a.size; i++) {
        new_a.p[i] = a.p[i];
    }

    delete[] a.p;

    a = new_a;
}


void v_test(test_vector T) {
    if (!cmp_lentier(T.expec_res, T.res)) {
        cout << "Test sur " << T.function << "reussi !" << endl;
    }

    else {
        cout << "ECHEC - Test sur " << T.function << "échoué !" << endl;
    }
}


void delete_vector(test_vector T) {
    delete[] T.a.p;
    delete[] T.b.p;
    delete[] T.x.p;
    delete[] T.N.p;

    delete[] T.expec_res.p;
    delete[] T.res.p;
}


lentier mult_classique(lentier a, lentier b) {
    unsigned int i, j, n, t, c;
    unsigned int long long temp;
    unsigned int long long r;
    lentier w;                                                                              // w contiendra le résultat
    n = a.size;
    t = b.size;
    w.p = new unsigned int[n + t];                                                          // w est de taille n*t
    i = 0;
    j = 0;
    w.size = n + t;

    while (i <= n + t - 1)
    {
        w.p[i] = 0;
        i = i++;
    }                                                                                       // w est initialisé à 0
    i = 0;
    while (i <= n - 1)
    {
        c = 0;
        j = 0;
        while (j <= t - 1)
        {
            temp = ((unsigned long long int)a.p[i]) * b.p[j] + w.p[i + j] + c;
            w.p[i + j] = temp;                                                              // chaque case de w est incrémentée par a*b et par la retenue
            c = temp >> 32;                                                                 // ce qui dépasse les 32 bits de la case (unsigned int) est mis en retenue pour la case supérieure
            j++;
        }
        w.p[i + t] = c;
        i++;
    }
    return w;                                                                               // renvoi du résultat
}


lentier mul_mod(lentier a, lentier b, lentier N) {
    return div_eucl(mult_classique(a, b), N);
}


lentier add_lentier(lentier a, lentier b)
{
    unsigned int c, i;
    unsigned int long long r = pow(2, 32);
    lentier s;
    c = 0;                                                                                  // retenue
    i = 0;
    (s.p) = new unsigned int[32];                                                           // allocation d'espace pour le resultat de l'add

    if (a.size < b.size)                                                                    // cas dans lequel B est + grand
    {
        while (i <= b.size - 1)
        {
            if (i < a.size)                                                                         // tant que le bit de A de rang i n'est pas nul, on l'ajoute à B et C
            {
                s.p[i] = (a.p[i] + b.p[i] + c) % r;
                c = ((a.p[i] + b.p[i] + c) > r) ? c = 1 : c = 0;                                            // on vérifie si la retenue vaut 1 ou 0 et on actualise
            }
            else                                                                            // si le bit de A de rang i est nul, on ajoute B seul
            {
                s.p[i] = b.p[i];
            }
            i++;
        }
        s.p[b.size] = c;
        s.size = b.size;
    }
    else                                                                                    // même chose avec A plus grand lentier ou de même taille
    {
        while (i <= a.size - 1)
        {
            if (i < b.size)
            {
                s.p[i] = (a.p[i] + b.p[i] + c) % r;
                c = ((a.p[i] + b.p[i] + c) > r) ? c = 1 : c = 0;
            }
            else
            {
                s.p[i] = a.p[i];
            }
            i++;
        }
        s.p[a.size] = c;
        s.size = a.size;
    }
    return s;                                                                               // renvoi du résultat
}


unsigned int lentier_log2(lentier c) {
    return (unsigned int)((c.size - 1) * 32 + ceil(log2(c.p[c.size - 1])));
}


char* lentier2dec(lentier L) {
    unsigned int length, n;
    n = 1;                                                                                  // Puissance de 10 pour optimisation : 10^9
    length = (lentier_log2(L) >> 2) / n;                                                    // La longueur en base 2, divisée par 2 est approx. longueur en base 10 divisé par n car on divise par 10^n, donc n fois moins que si on divisait par 10

    quores res_div;                                                                         // On crée un type composé qui contiendra le quotient et le reste de la division
    res_div.quotient = L;                                                                   // Initialisé avec lentier passé en paramètre

    lentier l_10n;
    l_10n.size = 1;
    l_10n.p = new unsigned int[1];
    l_10n.p[0] = pow(10, n);                                                                // lentier contenant 10^n pour les divisions

    char* b10 = new char[length * n + 1];                                                   // pointeur vers tableau qui stockera chiffre par chiffre lentier converti en base 10 (ce qu'on retourne)


    for (unsigned int i = length; i > 0; i--) {                                             // en faisant une division par 10^n, le reste aura n chiffres, donc on fait une sous-boucle avec des divisions sur des int (et pas sur des lentier => plus rapide) pour récupérer ces n chiffres 1 par 1, puis on fait le quotient par 10^n et on recommence à partir de ce quotient
        res_div = div_eucl_QR(res_div.quotient, l_10n);                                                // on met quotient+reste par 10^n dans le type compo

        if ((res_div.quotient.size - 1) || res_div.quotient.p[0] || res_div.reste) {                // Tant que le reste ou le quotien sont non nuls (au moins un des deux), on continue la boucle :
            uint8_t j = n - 1;
            while (res_div.reste) {                                                                 // sous-boucle : reste dans [0 ; 10^n - 1] donc on le re partage en ses n chiffres [0 ; 9] :
                b10[(i - 1) * n + j] = (res_div.reste % 10) + '0';                                          // on prend le reste par 10 pour le chiffre cherché
                res_div.reste = res_div.reste / 10;                                                        // puis quotient par 10 pour passer au chiffre suivant ; le tout n fois pour les n chiffres
                j--;
            }

        }
        else {                                                                                      // si le reste et le quotien de la division nuls (aka dès que tous les chiffres sont récupérés) on quitte la boucle
            i = 0;
        }
    }

    delete[] res_div.quotient.p;
    delete[] l_10n.p;                                                                       // on delete les pointeurs internes MAIS PAS b10, pointeur de retour, à delete[] après appel.

    return b10;
}


lentier sub_lentier(lentier a, lentier b)

{
	//Lexique ====================
	int c;
	unsigned int i;
	unsigned int n; //taille du plus grand entier soit a
	char signe; //varible correspondant au signe de a-b
	lentier s; //lentier retourné 


	//Algorithme =================
	c = 0;
	i = 0;

	unsigned int * pa = a.p; //pa correspond au pointeur de l'entier a
	unsigned int * pb = b.p; //pb correspond au pointeur de l'entier b 
	unsigned int * ps = nullptr; //ps correspond au pointeur de l'entier s

	//Ajustement de la taille des entiers :
	lAdjust(a);
	lAdjust(b);
	if (a.size > b.size) 
	{
		b = Allonge_lentier(b, a.size);
	}
	
	n = a.size; //Avec la fonction d'ajustement les entiers a et b ont la même taille  

	ps = new unsigned int[n];


	for (i = 0; i < n; i++)

	{
		(*(ps + i)) = ((*(pa + i)) - (*(b.p + i)) - c) & 0x0FFFFFFFF;;

		if ((*(pa + i)) >= (*(b.p + i)))
		{
			
			c = 0;

		}
		else
		{

			c = 1;

		}
	}
	
	s.size = n;
	s.p = ps;

	lAdjust(s); //on enlève les 0 excédentaires du résultat

	return s;
}

lentier Allonge_lentier(lentier x, unsigned int size)
{
	lentier z;
	unsigned int i;
	unsigned int* j = new unsigned int[size]();

	for (i = 0; i < size; i++)
	{
		*(j + i) = 0;
	};

	for (i = 0; i < x.size; i++)
	{
		*(j + i) = *(x.p + i);
	}

	z.size = size;
	z.p = j;

	return(z);
}

char cmp_lentier(lentier a, lentier b)
{

	lAdjust_realloc(a);
	lAdjust_realloc(b); //On enlève les zéros aux bits de poid fort des lentiers 

	char x;
	unsigned int ta;
	unsigned int tb;
	ta = a.size;
	tb = b.size; //as et bs correspondend aus tailles respectives de a et de b
	unsigned int taille_decremente; //Variable discrète de la boucle qui "balayer" les lentier du mot de poid fort au mot de poid faible.
	unsigned int * pa = a.p;
	unsigned int * pb = b.p; //pa et pb correspondent au pointeurs respectifs de a et de b. Initialisés au début de leurs espaces mémoire.

	if (ta > tb) //les zéros de poid fort étant enlevés, si un lentier est plus long que l'autre, il est aussi supérieur
	{
		x = 1;
	}

	if (tb > ta) //les zéros de poid fort étant enlevés, si un lentier est plus petit que l'autre, il est aussi inférieur
	{
		x = -1;
	}

	if (ta == tb) //les tailles des deux lentiers sont égales : il fzut mainntenant étudier les valeurs de leur mot 
	{
		int va;
		int vb; // valeurs respectives des mots de a et de b que l'on étudie dans la boucle
		taille_decremente = ta;

		while (taille_decremente > 0)
		{
			va = *(pa + taille_decremente - 1); //valeur du mot de a étudié
			vb = *(pb + taille_decremente - 1); //valeur du mot de b étudié

			if (va > vb)
			{
				x = 1;
				taille_decremente = 0; //Méthode pour sortir de cette de boucle while : et retourner x
			}

			if (va < vb)
			{
				x = -1;
				taille_decremente = 0; //Méthode pour sortir de cette de boucle while : et retourner x
			}

			if (va == vb)
			{
				taille_decremente = taille_decremente - 1; //On doit étudier le mot d'après
				x = 0;
			}
		}
	}

	return (x);
}

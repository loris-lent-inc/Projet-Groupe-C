#include <math.h>
#include <iostream>

using namespace std;

#include "InitFonctions.h"


void Affiche_lentier(lentier a) {
    cout << "{";
    for (unsigned int u = 0; u < a.size - 1; u++) {
        cout << a.p[u] << ",";
    }
    cout << a.p[a.size - 1] << "}" << endl;
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
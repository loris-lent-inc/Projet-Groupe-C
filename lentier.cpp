#include <math.h>
#include <iostream>

using namespace std;

#include "lentier.h"


void Affiche_lentier(lentier a) {

    unsigned int i;
    i = 0;

    cout << "{";
    while (i < a.size) {
        cout << a.p[i] << ", ";
        i++;
    }
    cout << "}" << endl;
}


void lAdjust(lentier &a) {

    unsigned int i;
    i = a.size;
    while (i > 1) {
        if (*&a.p[i - 1] == 0) {
            a.size = a.size - 1;
            i = i - 1;
        }
        else {
            i = 0;
        }
    }
    //a.size = (a.size == 0) ? (1) : (a.size);
}


void lAdjust_realloc(lentier &a) {
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
        i++;
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
    
    lAdjust_realloc(w);
    return w;                                                                               // renvoi du résultat
}


lentier mul_mod(lentier a, lentier b, lentier N) {
    lentier p = mult_classique(a, b);
    lentier q = div_eucl(p, N);
    return q;
}


lentier add_lentier(lentier a, lentier b)
{
    unsigned int c, i;
    unsigned int long long r = 0x100000000;
    lentier s;
    c = 0;                                                                                  // retenue
    i = 0;
    //s.p = new unsigned int[32];                                                           // allocation d'espace pour le resultat de l'add

    if (a.size < b.size)                                                                    // cas dans lequel B est + grand
    {
        s.p = new unsigned int[b.size + 1];
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
        s.p = new unsigned int[a.size + 1];
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


char cmp_lentier(lentier a, lentier b)                                                      // ATTENTION : des noms de variables ont été modifiées par rapport au code original pour limiter le nombre d'attributuions à faire
{                                                                                           // Modifications faites par Loris Pinto qui en prend l'entière responsabilité, suite au refus de Jean-Baptiste Martin de coopérer avec le groupe.
    //lAdjust_realloc(a);
    //lAdjust_realloc(b);                                                                     //On enlève les zéros aux bits de poid fort des lentiers 

    char x;
    unsigned int taille_decremente;                                                         //Variable discrète de la boucle qui "balayer" les lentier du mot de poid fort au mot de poid faible.

    if (a.size > b.size)                                                                    //les zéros de poid fort étant enlevés, si un lentier est plus long que l'autre, il est aussi supérieur
    {
        x = 1;
    }

    if (b.size > a.size)                                                                    //les zéros de poid fort étant enlevés, si un lentier est plus petit que l'autre, il est aussi inférieur
    {
        x = -1;
    }

    if (a.size == b.size)                                                                   //les tailles des deux lentiers sont égales : il fzut mainntenant étudier les valeurs de leur mot 
    {
        taille_decremente = a.size;

        while (taille_decremente > 0)
        {
            if (a.p[taille_decremente - 1] > b.p[taille_decremente - 1])
            {
                x = 1;
                taille_decremente = 0;                                                              //Méthode pour sortir de cette de boucle while : et retourner x
            }

            else if (a.p[taille_decremente - 1] < b.p[taille_decremente - 1])
            {
                x = -1;
                taille_decremente = 0;                                                              //Méthode pour sortir de cette de boucle while : et retourner x
            }

            else if (a.p[taille_decremente - 1] == b.p[taille_decremente - 1])
            {
                taille_decremente = taille_decremente - 1;                                          //On doit étudier le mot d'après
                x = 0;
            }
        }
    }

    return (x);
}


lentier W2WLeftShift(lentier a, int amount) {
    lentier result;
    result.size = a.size + amount;
    result.p = new unsigned int[result.size]();

    unsigned int i;

    for (i = 1; i <= a.size; i++) {
        result.p[result.size - i] = a.p[a.size - i];
    }
    return result;
}


lentier B2BRightShift(lentier a, int amount, char modifySize) {
    unsigned int buffer, i;
    lentier result;
    buffer = 0;
    result.size = a.size;
    result.p = new unsigned int[result.size]();

    for (i = a.size; i > 0; i--) {
        result.p[i - 1] = (a.p[i - 1] >> amount) + buffer;
        buffer = a.p[i] << (32 - amount);
    }
    if (modifySize == 1) {
        lAdjust_realloc(result);
    }
    return result;
}


lentier B2BLeftShift(lentier a, int amount, char modifySize) {
    unsigned int buffer, i;
    buffer = 0;

    lentier result;
    result.size = a.size + 1;
    result.p = new unsigned int[result.size]();

    for (i = 0; i <= a.size - 1; i++) {
        result.p[i] = (a.p[i] << amount) + buffer;
        buffer = a.p[i] >> (32 - amount);
    }
    if (modifySize == 1) {
        result.p[a.size] = buffer;
    }
        lAdjust_realloc(result);
    
    return result;
}


lentier Allonge_lentier(lentier x, unsigned int size) {
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
    //delete[] x.p;                                           // faut-il delete les arguments ?
    return(z);
}


lentier sub_lentier(lentier a, lentier b) {
    //Lexique ====================
    int c;
    unsigned int i;
    unsigned int n; //taille du plus grand entier soit a
    char signe; //varible correspondant au signe de a-b
    lentier s; //lentier retourné 


    //Algorithme =================
    c = 0;
    i = 0;

    unsigned int* pa = a.p; //pa correspond au pointeur de l'entier a
    unsigned int* pb = b.p; //pb correspond au pointeur de l'entier b 
    unsigned int* ps = nullptr; //ps correspond au pointeur de l'entier s

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
        (*(ps + i)) = ((*(pa + i)) - (*(b.p + i)) - c) & 0x0FFFFFFFF;

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

    lAdjust_realloc(s); //on enlève les 0 excédentaires du résultat

    return s;
}


lentier exp_mod(lentier a, lentier x, lentier N) {
    lentier P;						                                                            //déclaration de P;
    P.size = N.size;				                                                            //initialisation de la taille du tableau (32 éléments de 32 bits de longueur (unsigned int));
    P.p = new unsigned int[P.size];                                                             //initialisation du tableau de unsigned int;
    lentier temp;

    for (unsigned int i = 0; i < a.size; i++)			                                        // size correspond au nombre d'élément dans le tableau(p) du lentier 
    {
        P.p[i] = a.p[i];			                                                            // pour toute la boucle for, copie du tableau de a dans P;
    }

    for (int i = 32 * x.size - 2; i >= 0; i--)                                                  // On parcourt N en ordre descendant bit par bit; 
    {
        temp = mul_mod(P, P, N);
        delete[] P.p;
        P = temp;                                                                                       // P = P*P reste N
        if (x.p[i / 32] & (1 << (i % 32)))                                                              // si ei = 1
        {
            temp = mul_mod(P, a, N);
            delete[] P.p;
            P = temp;
        }
        //cout << "boucle " << i << endl;

    }
    return P;                                                                                   // on renvoie le résultat

}


lentier init_lentier(unsigned int a) {
    lentier n;

    n.size = 1; //Le lentier ne contient qu'un seul digit
    n.p = new unsigned int;
    *(n.p) = a; //Le digit prend la valeur de l'entier passé en paramètre
    return n;
}


lentier dec2lentier(char* nombre_dec) {
    //Structures lentier nécessaires
    lentier buffer1, buffer2, digit, dix;

    //Nombre 10^n en base 10
    unsigned int idigit;

    //Taille de la chaine de caractères
    unsigned int nb_digit = strlen(nombre_dec);

    //Initialisation buffer1 = 0 et dix = 10 (en base 2^32)
    buffer1 = init_lentier(0);
    dix = init_lentier(10);


    //L'algorithme qui suit reprend la méthode de Horner
    //
    for (unsigned int i = 0; i < nb_digit; i++) {
        idigit = nombre_dec[i] - '0'; //Nombre d'incide i dans la chaine (Conversion forcé de type)

        digit = init_lentier(idigit); //Convertion du digit (base 10)-->(base 2^32)

        //Multiplication par 10 du buffer2
        buffer2 = mult_classique(buffer1, dix);

        delete[] buffer1.p;

        buffer1 = buffer2; //Swap buffer1 et buffer2

        //Ajout du au buffer2 du digit
        buffer2 = add_lentier(buffer1, digit);

        delete[] buffer1.p;
        delete[] digit.p;

        buffer1 = buffer2; //Swap buffer1 et buffer2

        lAdjust_realloc(buffer1);
    }

    //Libération de la mémoire avant la fin de la fonction
    delete[] dix.p;

    return buffer1;
}


lentier div_eucl(lentier a, lentier b) {
    // Variables locales
    unsigned int i; // compteur
    unsigned char lambda;
    const unsigned long long int BASE = 0x100000000;
    unsigned long long int templl;
    lentier q, r, buffer1, buffer2, buffer3, buffer4, na, nb;
    //q = quotient, r = reste

    // Algorithme
    if (b.size == 1) {
        templl = 0;
        q.size = (a.size == 1) ? (1) : (a.size - 1);
        q.p = new unsigned int[q.size];

        for (i = a.size; i > 0; i--) {
            templl = (templl << 32) + a.p[i - 1];
            q.p[i - 1] = (unsigned int)(templl / b.p[0]);
            templl = templl % b.p[0];
        }
        r.size = 1;
        r.p = new unsigned int[1];
        r.p[0] = (unsigned int)templl;
    }
    else {
        q.size = (a.size == b.size) ? (1) : (a.size - b.size);
        q.p = new unsigned int[q.size]();
        
        // na.p = a.p
        na.size = a.size;
        na.p = new unsigned int[na.size];
        for (i = 0; i < a.size; i++) {
            *(na.p + i) = *(a.p + i);
        }

        //nb.p = b.p;
        nb.size = b.size;
        nb.p = new unsigned int[nb.size];
        for (i = 0; i < b.size; i++) {
            nb.p[i] = b.p[i];
        }

        /*
        Partie 1 :
        Pas besoin de le faire, les bits de q ont été initialisé à 0 lors de sa déclaration avec les parenthèses 	après les [] (voir page 2 fascicule de projet)
        */
        if (cmp_lentier(na, nb) == -1) {
            //il est demandé que A et B aient le même nombre de mots mais il n'est pas dit que A doit être supérieur à B

            /*
            q.size = 1;
            delete q.p[];
            q.p = new unsigned int[1];
            N'est nécessaire que si nous devons retourner le quotient
            */

        }
        else {//Algo donné
         //Optimisation lambda
            lambda = 0;
            while (nb.p[nb.size - 1] < BASE / 2) {

                buffer1 = B2BLeftShift(na, 1, 1);
                delete[] na.p;
                na = buffer1;

                buffer1 = B2BLeftShift(nb, 1, 1);
                delete[] nb.p;
                nb = buffer1;

                ++lambda;
            }


            // Partie 2 :
            if (na.size > nb.size) {
                // ici le Buffer1 correspond à B multiplié par la base à la puissance n-t (équivalent à a.size - b.size)
                buffer1 = W2WLeftShift(nb, na.size - nb.size);
            }
            else {
                buffer1 = nb;
            }
            while (cmp_lentier(na, buffer1) >= 0) {
                q.p[na.size - nb.size] = q.p[na.size - nb.size] + 1;
                buffer2 = sub_lentier(na, buffer1);
                delete[] na.p;
                na = buffer2;
            }

            // Partie 3 :
            for (i = a.size - 1; i >= b.size; --i) {
                // 3.a)
                if (na.p[i] == nb.p[nb.size - 1]) {
                    q.p[i - nb.size] = BASE - 1;
                }
                else {
                    templl = (((unsigned long long int)na.p[i]) << 32) + na.p[i - 1];
                    q.p[i - nb.size] = ((unsigned int)(templl / nb.p[nb.size - 1]));
                }

                // 3.b)
                buffer1.p = new unsigned int[3];
                buffer1.size = 3;
                buffer1.p[2] = na.p[i];
                buffer1.p[1] = na.p[i - 1];
                buffer1.p[0] = na.p[i - 2];

                buffer2.p = new unsigned int[2];
                buffer2.size = 2;
                buffer2.p[1] = nb.p[nb.size - 1];
                buffer2.p[0] = nb.p[nb.size - 2];

                buffer3.p = new unsigned int[1];
                buffer3.size = 1;
                buffer3.p[0] = q.p[i - nb.size];
                
                lAdjust_realloc(buffer1);
                lAdjust_realloc(buffer2);
                lAdjust_realloc(buffer3);

                buffer4 = mult_classique(buffer2, buffer3);

                while (cmp_lentier(buffer4, buffer1) == 1) {
                    q.p[i - nb.size] = q.p[i - nb.size] - 1;
                    buffer3.p[0] = q.p[i - nb.size];

                    delete[] buffer4.p;
                    buffer4 = mult_classique(buffer2, buffer3);
                }
                delete[] buffer1.p;
                delete[] buffer2.p;
                delete[] buffer3.p;
                delete[] buffer4.p;

                // 3.c) et 3.d)
                buffer1.p = new unsigned int[1];
                buffer1.size = 1;
                buffer1.p[0] = q.p[i - nb.size];
                buffer2 = W2WLeftShift(buffer1, i - nb.size);
                delete[] buffer1.p;
                buffer1 = mult_classique(buffer2, nb);
                delete[] buffer2.p;

                if (cmp_lentier(na, buffer1) == -1) {
                    q.p[i - nb.size] = q.p[i - nb.size] - 1;

                    delete[] buffer1.p;
                    buffer1.p = new unsigned int[1];
                    buffer1.size = 1;
                    buffer1.p[0] = q.p[i - nb.size];
                    buffer2 = W2WLeftShift(buffer1, i - nb.size);
                    delete[] buffer1.p;
                    buffer1 = mult_classique(buffer2, nb);
                    delete[] buffer2.p;
                    buffer2 = sub_lentier(na, buffer1);
                    delete[] na.p;
                    delete[] buffer1.p;
                    na = buffer2;
                }
                else {
                    buffer2 = sub_lentier(na, buffer1);
                    delete[] na.p;
                    delete[] buffer1.p;
                    na = buffer2;
                }
            }
        }
        if (lambda > 0) {
            buffer1 = B2BRightShift(na, (int)lambda, 1);
            delete[] na.p;
            na = buffer1;
        }
        r = na;
        delete[] nb.p;
        delete[] q.p;																			// à enlever pour la fonction de Loris
        lAdjust_realloc(r);																		// est ce qu'il faut mettre un & (voir page 10 fascicule)
    }
        
        return r;
}


quores div_eucl_QR(lentier a, lentier b) {
    unsigned int i;
    unsigned long long int temp = 0;
    quores res;

    res.quotient.size = (a.size == 1) ? (1) : (a.size - 1);
    res.quotient.p = new unsigned int[res.quotient.size];

    for (i = a.size; i > 0; i--) {
        temp = (temp << 32) + a.p[i - 1];
        res.quotient.p[i - 1] = (unsigned int)(temp / b.p[0]);
        temp = temp % b.p[0];
    }
    res.reste = (unsigned int)temp;

    return res;
}


unsigned long long int lentier_log2(lentier a) {
    return (unsigned long long int)(a.p[a.size - 1] != 0) ? ((a.size - 1) * 32 + ceil(log2(a.p[a.size - 1]))) : ((a.size - 1) * 32);
}


char* lentier2dec(lentier L) {
    char* b10 = nullptr;
    
    if (L.size == 1 && L.p[0] == 0) {
        b10 = (char*)"0";
    }
    else {
        unsigned int length, n;
        n = 9;                                                                                  // Puissance de 10 pour optimisation : 10^9
        length = (lentier_log2(L) >> 1) / n;                                                    // La longueur en base 2, divisée par 2 est approx. longueur en base 10 divisé par n car on divise par 10^n, donc n fois moins que si on divisait par 10
        length = (length == 0) ? (1) : (length);

        quores res_div;                                                                         // On crée un type composé qui contiendra le quotient et le reste de la division
        res_div.quotient = L;                                                                   // Initialisé avec lentier passé en paramètre

        lentier l_10n = init_lentier(pow(10, n));                                               // lentier contenant 10^n pour les divisions

       b10 = new char[length * n + 1];                                                          // pointeur vers tableau qui stockera chiffre par chiffre lentier converti en base 10 (ce qu'on retourne)

        uint8_t j = n;

        for (unsigned int i = length; i > 0; i--) {                                             // en faisant une division par 10^n, le reste aura n chiffres, donc on fait une sous-boucle avec des divisions sur des int (et pas sur des lentier => plus rapide) pour récupérer ces n chiffres 1 par 1, puis on fait le quotient par 10^n et on recommence à partir de ce quotient
            res_div = div_eucl_QR(res_div.quotient, l_10n);                                                 // on met quotient+reste par 10^n dans le type compo

            if ((res_div.quotient.size - 1) || res_div.quotient.p[0] || res_div.reste) {                    // Tant que le reste ou le quotien sont non nuls (au moins un des deux), on continue la boucle :
                j = n;
                while (j) {                                                                                 // sous-boucle : reste dans [0 ; 10^n - 1] donc on le re partage en ses n chiffres [0 ; 9] :
                    b10[(i - 1) * n + j] = (res_div.reste % 10) + '0';                                                                       // on prend le reste par 10 pour le chiffre cherché
                    res_div.reste = res_div.reste / 10;                                                             // puis quotient par 10 pour passer au chiffre suivant ; le tout n fois pour les n chiffres
                    j--;
                }

            }
            else {                                                                                      // si le reste et le quotien de la division nuls (aka dès que tous les chiffres sont récupérés) on quitte la boucle
                b10[(i - 1) * n + j] = '0';
                break;
            }
        }

        delete[] res_div.quotient.p;
        delete[] l_10n.p;                                                                       // on delete les pointeurs internes MAIS PAS b10, pointeur de retour, à delete[] après appel.
        b10 = Clean_after_your_dog(length * n, b10);
    }
    return b10;
}

char* Clean_after_your_dog(unsigned int l, char *b)
{    
    char k = b[0];
    unsigned int i = 0;
    while ((k < 49 || k > 58) && i <= l) {                                                              // On parcours la chaine jusqu'au premier caractère valide non-nul
        i++;
        k = b[i];
    }
    char* d = new char[l - i + 2];                                                              // on crée une nouvelle chaine de taille adéquate
    d[l - i + 1] = '\0';
    
    unsigned int start = i;                                                                 // On retiens l'indice du premier caractère valide

    l = l + i;                                                                              // En ajoutant i à l, on assure que la boucle parcourera précisément les caractères valides de la chaine

    for (i; i <= l; i++) {
        if (b[i] > 47 && b[i] < 58) {
            d[i - start] = b[i];                                                                    // Tant que les caractères sont des chiffres, on les ajoutes à la nouvelle chaine
        }
        else {
            break;                                                                                  // Sinon on arrête la copie
        }
    }

    delete[] b;
    b = d;                                                                                  // On remplace b par la nouvelle chaine
    return b;
}

typedef struct {
    unsigned int* p;
    unsigned int size;
} lentier;

/*
test_vector est un types compos� de plusieurs lentier, (a, b, N, et x) 
pour les entrees, res pour le resultat, et expec_res pour le resultat attendu.
Pour �crire les r�sultats des tests, on peut mettre le nom de la fonction dans "function"
*/
typedef struct {
    char function[30];
    
    lentier a;
    lentier b;
    lentier N;
    lentier x;

    lentier res;
    lentier expec_res;
} test_vector;

/*
quores est un type compos� de d'un lentier et d'un unsigned int,
utilis� par lentier2dec pour calculer le quotient et le reste
d'une division en 1 seul appel de div_eucl_QR.
Par d�finition, le reste sera dans [0 ; 1.000.000.000]
donc un lentier est inutilement grand pour le stocker
*/
typedef struct {
    lentier quotient;
    unsigned int reste;
} quores;


/*
R: Une fois un test_vector �tabli (res et expec_res d�finis) 
   cette fonction affichera si le test est pass� ou non.
E: 1 test_vector
S: Aucune
*/
void v_test(test_vector T);

/*
R: Une fois un test_vector test�, cette fonction 
   delete[] les pointeurs des lentiers du vecteur.
E: 1 test_vector
S: Aucune
*/
void delete_vector(test_vector T);

/*
R: Affiche un lentier sous forme brute, case par case,
   de la moins significative � la plus significative.
E: 1 lentier a, qui sera affich�.
S: Aucune
*/
void Affiche_lentier(lentier a);


/*
*/
void lAdjust(lentier& a);


/*
*/
void lAdjust_realloc(lentier& a);


/*
R: Multiplie deux lentier a et b de tailles respectives t et n
   et retourne un lentier r resultat de la multiplication.
E: 2 lentier a et b.
S: 1 lentier resultat de a * b, de taille n * t.
*/
lentier mult_classique(lentier a, lentier b);


/*
R: Multiplie deux lentier a et b de tailles respectives t et n
   et calcule le reste  de la division du produit par un
   lentier N de taille k, et retourne un lentier r, le resultat.
E: 3 lentier a, b et N.
S: 1 lentier resultat de (a * b) % N, de taille k.
*/
lentier mul_mod(lentier a, lentier b, lentier N);


/*
R: Additionne deux lentier a et b  de tailles respectives t et n
   et retourne lentier r de la somme.
E: 2 lentier a et b.
S: 1 lentier resultat de a + b, de taille t + n.
*/
lentier add_lentier(lentier a, lentier b);


/*
R: Compare deux lentier a et b et retourne leur ordre.
E: 2 lentier a et b.
S: 1 char (-1 si a < b, 0 si a = b, 1 si a > b).
*/
char cmp_lentier(lentier a, lentier b);


/*
R: Soustrait deux lentier a et b et retourne la diff�rence.
E: 2 lentier a et b.
S: 1 lentier resultat de a - b.
*/
lentier sub_lentier(lentier a, lentier b);


/*
R: Calcule le reste de l'exponentiation a^x par N.
E: 3 lentier a, x et N.
S: 1 lentier resultat de (a ^ x) % N.
*/
lentier exp_mod(lentier a, lentier x, lentier N);


/*
R: Convertit une chaine de caract�res en un lentier.
E: 1 cha�ne de caract�res nombre_dec.
S: 1 lentier resultat de la conversion.
*/
lentier dec2lentier(char* nombre_dec);


/*
R: Divise les lentiers a par b et retourne le reste.
E: 2 lentier a et b.
S: 1 lentier resultat de a % b.
*/
lentier div_eucl(lentier a, lentier b);


/*
R: Divise les lentiers a par b et retourne le quotient et le reste dans un type compos�.
E: 2 lentier a et b.
S: 1 quores comprenant les resultats de (a / b) et (a % b).
*/
quores div_eucl_QR(lentier a, lentier b);


/*
  R: clacule et renvoie la longueur en bits d'un lentier.
  E: 1 lentier
  S: 1 unsigned int, la taille du lentier
*/
unsigned int lentier_log2(lentier c);


/*
  R: cr�er un pointeur vers un tableau de char repr�sentant l'entr�e en base 10
  E: 1 lentier
  S: 1 pointeur vers un tableau de char
*/
char* lentier2dec(lentier nombre_base_r);
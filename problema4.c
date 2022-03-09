#include <stdio.h>
#include <string.h>

#define char_length 9

/*

Functia "integer" returneaza valoarea intreaga
a unei cifre de tip "char".

Are drept parametru o variabila de tip "char", s.

*/

int integer(char s) {
    return (int)(s)-(int)('0');
}

/*

Functia "character" este tocmai opusul functiei
definite mai sus, "integer". Transorma cifra, "int",
in "char".

Are drept parametru o variabila de tip "int", n;

*/

char character(int n) {
    return (char)(n+(int)('0'));
}

/*

Functia "strrev" returneaza sirul inversat.

Are drept parametru un pointer de tip "char", s;

*/

void strrev(char *s) {
    int length = strlen(s), i;

    for (i = 0; i < length / 2; i++) {
        char c = s[i];

        s[i] = s[length - i - 1];
        s[length - i - 1] = c;
    }
}

/*

Functia "s_to_row" are rolul de a popula un rand
al matricii (un vector) cu cifrele numarului in baza 2.
Cum numarul in baza 2 este pastrat sub forma unui
sir de carcatere, este necesar apelul functiei "integer".

Are drept parametrii vectorul m si pointerul de tip "char", s.

*/

void s_to_row(int m[], char *s) {
	int i;
	
    for (i = 0; i < 8; i++)
        m[i] = integer(s[i]);
}

/*

Functia "row_to_s" are rolul de a extrage randul matricii
(un vector) in sirul de caractere s, ce va reprezenta un
numar in baza  2. Este necesar apelul functiei "character".

Are drept parametrii vectorul m si pointerul de tip "char", s.

*/

void row_to_s(int m[], char *s) {
	int i;
	
    for (i = 0; i < 8; i++)
        s[i] = character(m[i]);
}

/*

Functia "dec_to_bin" face trecerea unui numar din baza 10
in baza 2, pastrandu-l intr-un sir de caractere. Este necesar
apelul functiei "character".

Are drept parametrii o variabila de tip "int", n, numarul de
transformat, si un pointer de tip "char", ce va memora scrierea
in baza 2.

*/

void dec_to_bin(int n, char *s) {
    int length = 0, i;

    do {
        s[length++] = character(n % 2);
        n /= 2;
    } while(n>0);

    for(i = length; i < 8; i++)
        s[i] = '0';

    s[8] = '\0';
    strrev(s);
}

/*

Functia "bin_to_dec" face trecerea unui numar din baza 2
(memorat sub forma unui sir de carcatere) in baza 10, pe care
il si returneaza.

Are drept parametru un pointer de tip "char", s, sirul de caractere. 

*/

int bin_to_dec(char *s) {
    int p = 1, nr = 0, i;

    for(i = strlen(s)-1; i >= 0; i--, p *= 2)
        nr += p * integer(s[i]);

    return nr;
}

/*

Functia "out" afiseaza liniile matricei cu scorul maxim.
Procedeul este urmatorul:

1. vectorul de tip "int" este trecut intr-un sir de caractere,
apeland functia "row_to_s".

2. este afisata valoarea in baza 10 a numarului in baza 2
memorat sub forma sirului de caractere s, apeland functia
"bin_to_dec".

Are drept parametru matricea de tip "int", m.

*/

void out(int m[][8]) {
	int i;
	
    for (i = 0; i < 8; i++) {
        char s[char_length];

        row_to_s(m[i], s);	// 1.
        printf("%d\n", bin_to_dec(s));
    }
}

/*

Functia "product" calculeaza produsul a doua matrici,
m1 si m2, care va fi memorat in m3.

Are drept parametrii 3 matrici de tip "int".

*/

void product(int m1[][8], int m2[][8], int m3[][8]) {
	int i, j;
	
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++) {
            int value = 0, k;

            for (k = 0; k < 8; k++)
                value += m1[i][k]*m2[k][j];

            if (value >= 1)
                m3[i][j] = 1;
            else
                m3[i][j] = 0;
        }
}

/*

Functia "transpose" realizeaza transpusa matricei m,
pe care o memoreaza in mt.

Are drept parametrii 2 matrici de tip "int", m si mt.

*/

void transpose(int m[][8], int mt[][8]) {
	int i, j;
	
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
            mt[j][i] = m[i][j];
}

/*

Functia small_sum_X_0 calculeaza scorul pentru o matrice 
de dimensiune 4 x 4, pentru a usura pastrarea evidentei indicilor.

Are drept parametru o matrice de tip "int", m.

*/

int small_sum_X_0(int m[][4]) {
    int value=0, current, i, j;

    for (i = 0; i < 4; i++) {
        current=0;

        for (j = 0; j < 4; j++)
            current += m[i][j];
        value += current == 4;
    }

    for (j = 0; j < 4; j++) {
        current = 0;
        for (i = 0; i < 4; i++)
            current += m[i][j];
        value += current == 4;
    }

    current = 0;

    for (i = 0; i < 4; i++)
        current += m[i][i];

    value += current == 4;
    current = 0;

    for (i = 0; i < 4; i++)
        current += m[i][4-i-1];

    value += current == 4;

    return value;
}

/*

Functia "sum_X_0" calculeaza scorul unei matrici, impartind-o
in alte patru matrici mai mici, pe care le copieaza pe rand
in matricea cpy, ce va reprezenta parametru pentru functia
"small_sum_X_0". Scorul final este suma scorurilor celor patru
matrici mai mici.

Are drept parametru o matrice de tip "int", m, pastrand antetul
specificat in enuntul problemei.

*/

int sum_X_0(int m[][8]) {
    int cpy[4][4], value=0, i, j;

    for (i = 0; i < 4; i++) ///left, up
        for (j = 0; j < 4; j++)
            cpy[i][j] = m[i][j];

    value+=small_sum_X_0(cpy);

    for (i = 0; i < 4; i++) ///right, up
        for (j = 4; j < 8; j++)
            cpy[i][j-4] = m[i][j];

    value+=small_sum_X_0(cpy);

    for (i = 4; i < 8; i++) ///left, down
        for (j = 0; j < 4; j++)
            cpy[i-4][j] = m[i][j];

    value+=small_sum_X_0(cpy);

    for (i = 4; i < 8; i++) ///right, down
        for (j = 4; j < 8; j++)
            cpy[i-4][j-4] = m[i][j];

    value += small_sum_X_0(cpy);

    return value;
}

/*

Functia "main" este responsabila pentru citirea matricii
initiale si apelul functiilor anterior documentate: 

1. transforma input-ul primit intr-un format convenabil
(matrice de tip int, 8 x 8), "dec_to_bin", "s_to_row".

2. calculeaza transpusa, pentru aflarea A*A(t), si A^2,
"transpose", "product".

3. calculeaza scorul pentru fiecare dintre cele 3 matrici
obtinute: m (A), m_product (A*A(t)), m_sq (A^2).

4. afiseaza matricea conform criteriilor enuntate in cerinta:
scor, A > A*A(t) > A^2

*/

int main() {

    int m[8][8], mt[8][8], m_product[8][8], m_sq[8][8], dec, i;

    for (i = 0; i < 8; i++) {
        scanf("%d", &dec);

        char s[char_length];

        dec_to_bin(dec, s);
        s_to_row(m[i], s);
    }

    transpose(m, mt);
    product(m, mt, m_product);
    product(m, m, m_sq);

    int X = sum_X_0(m), X_product = sum_X_0(m_product), X_sq = sum_X_0(m_sq);

    if (X >= X_product && X >= X_sq)
        out(m);
    else {
        if (X_product >= X && X_product >= X_sq)
            out(m_product);
        else
            out(m_sq);
    }

    return 0;
}

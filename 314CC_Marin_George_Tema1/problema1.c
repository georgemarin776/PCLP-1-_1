#include <stdio.h>
#include <string.h>

#define upr 256
#define char_length 51
#define pair_max 1001

/* 

Functia "is_anagram" verifica daca doua siruri de caractere
sunt anagrame, pastrand antetul specificat in enuntul problemei.

Are drept parametrii s1 si s2, pointeri de tip "char".

*/

int is_anagram(char *s1, char *s2) {
	int i;
	
    if (strlen(s1) != strlen(s2))
		
        return 0;

    if (strcmp(s1, s2) == 0)
		
        return 1;

    int compare[upr], length = strlen(s1);

    memset(compare, 0, sizeof(compare));

    for (i = 0; i < length; i++)
        compare[(int)(s1[i])]++;

    length = strlen(s2);

    for (i = 0; i < length; i++)
        compare[(int)(s2[i])]--;

    for (i = 0; i < upr; i++)
        if (compare[i])
			
            return 0;

    return 1;
}

/*

Functia "compute_grade" calculeaza gradul a doua siruri, pastrand 
antetul specificat in enuntul problemei. 

Are drept parametrii s1 si s2, pointeri de tip "char".

*/

double compute_grade(char *s1, char *s2) {
	int i;
	
    if (is_anagram(s1, s2) == 0)
		
        return -1;

    if (strcmp(s1, s2) == 0)
		
        return 0;

    int unlikeness = 0, length = strlen(s1);

    for (i = 0; i < length; i++)
        if (s1[i] != s2[i])
            unlikeness++;

    return (float)(unlikeness) / length;
}

/*

Pentru a usura memorarea perechilor, am declarat structura de mai jos,
ce contine o variabila de tip "float" (ulterior va fi egalata cu rezultatul
functiei compute_grade) si 2 cele doua siruri de caractere.

*/

typedef struct pairs {
    float grade;
    char s1[char_length], s2[char_length];
} pair;

/*

Functia "out" afiseaza o pereche de cuvinte pe un singur rand,
trecand si pe linia urmatoare.

Are drept parametrii n (numarul de perechi) si vectorul v, de tip "pairs".

*/

void out(int n, pair v[]) {
	int i;
	
    for (i = 0; i < n; i++) {
        printf("%s %s\n", v[i].s1, v[i].s2);
    }
}

/*

Functia "sort_grade" sorteaza vectorul ce contine gradele si perechile
de siruri, respectand cerintele problemei - grad mai mare sau
grad egal si ordine invers lexicografica. Dupa ce realizeaza
sortarea, apeleaza functia "out".

Are drept parametrii n (numarul de perechi) si vectorul v, de tip "pairs".

*/

void sort_grade(int n, pair v[]) {
	int i, j;
	
    for (i = 0; i < n - 1; i++)
        for (j = i + 1; j < n; j++)
            if (v[i].grade < v[j].grade
                    || (v[i].grade == v[j].grade
                        && strcmp(v[i].s1, v[j].s1) < 0)) {
                float aux_grade = v[i].grade;
				char aux[char_length];
				
                v[i].grade = v[j].grade;
                v[j].grade = aux_grade;

                strcpy(aux, v[i].s1);
                strcpy(v[i].s1, v[j].s1);
                v[i].s1[strlen(v[j].s1)] = '\0';
                strcpy(v[j].s1, aux);
                v[j].s1[strlen(aux)] = '\0';

                strcpy(aux, v[i].s2);
                aux[strlen(v[i].s2)] = '\0';
                strcpy(v[i].s2, v[j].s2);
                v[i].s2[strlen(v[j].s2)] = '\0';
                strcpy(v[j].s2, aux);
                v[j].s2[strlen(aux)] = '\0';
            }
			
    out(n, v);
}

/* 

In functia "main" regasim declararile si citirile initiale,
alaturi de apelul functiei "sort_grade".

*/

int main() {
    int n, i;

    scanf("%d", &n);
	
    pair v[pair_max];

    for (i = 0; i < n; i++) {
        scanf("%s %s", v[i].s1, v[i].s2);
        v[i].grade = compute_grade(v[i].s1, v[i].s2);
    }
	
    sort_grade(n, v);

    return 0;
}

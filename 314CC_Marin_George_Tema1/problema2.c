#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

Pentru a usura memorarea pozitiei nebunilor, am declarat
structura de mai jos, ce contine 2 variabile de tip "int".

*/

typedef struct xoy {
    int x, y;
} xoy;

/*

Functia "read_bishops" este responsabila pentru citirea 
coordonatelor celor n nebuni.

Are drept parametrii n (numarul de nebuni) si vectorul v, de tip "xoy".

*/

void read_bishops(int n, xoy *v) {
	int i;
	
    for (i = 0; i < n; i++)
        scanf("%d %d", &v[i].x, &v[i].y);
}

/*

Functia "print_bishops" afiseza pe ecran a cei n nebuni.

Are drept parametrii n (numarul de nebuni) si vectorul v, de tip "xoy".

*/

void print_bishops(int n, xoy *v) {
	int i;
	
    for (i = 0; i < n; i++)
        printf("%d %d\n", v[i].x, v[i].y);
}

/* 

In functia "slope" se calculeaza panta dintre doi nebuni,
utilizandu-se coordonate anterior memorate. Panta va fi
utilizata pentru a determina daca se afla pe aceeasi diagonala.

Are drept parametrii 2 variabile de tip "xoy", a si b,
ce retin coordonatele a 2 nebuni.

*/

float slope(xoy a, xoy b)
{
    if(a.x - b.x == 0)
		
        return 0;

    return (float)(a.y - b.y) / (a.x - b.x);
}

/*

Functia "attacks" determina daca doi nebuni se pot ataca,
utilizandu-se de panta calculata de functia "slope".

Are drept parametrii 2 variabile de tip "xoy", a si b,
ce retin coordonatele a 2 nebuni.

*/

int attacks(xoy a, xoy b) {

    float m = slope(a, b);

    if (m == 1.0 || m == -1.0)
		
        return 1;

    return 0;
}

/*

Functia "det_pairs" este responsabila cu determinarea
numarului de perechi de nebuni ce se pot ataca.

Are drept parametrii n (numarul de nebuni) si vectorul v, de tip "xoy".

*/

int det_pairs(int n, xoy *v) {
    int pairs = 0, i, j;

    for (i = 0; i < n-1; i++)
        for (j = i+1; j < n; j++)
            if (attacks(v[i], v[j]) == 1)
                pairs++;

    return pairs;
}

/*

Functia "save_pair" are scopul de a salva coordonatele celor 
doi nebuni care se ataca, in situatia in care exista o singura
pereche care respecta aceasta conditie (nu am utilizat vreun
flag pentru acest criteriu de unicitate, functia nu va fi apelata).

Are drept parametrii n (numarul de nebuni), vectorul v, de tip "xoy",
si doua variabile de tip "xoy", a si b.

*/

void save_pair(int n, xoy *v, xoy *a, xoy *b) {
	int i, j;
	
    for (i = 0; i < n-1; i++)
        for (j = i+1; j < n; j++)
            if (attacks(v[i], v[j])){
                (*a) = v[i];
                (*b) = v[j];
				
                return;
            }
}


/*

Functia "same_point" determina daca doua puncte
de coordonate (a.x, a.y), (b.x, b.y) coincid. 

Are drept parametrii doua variabile de tip "xoy", a si b.

*/

int same_point(xoy a, xoy b) {
    if (a.x == b.x)
        if (a.y == b.y)
            
			return 1;

    return 0;
}

/*

Functia "out_ofBounds" verifica daca un punct de coordonate
(a.x, a.y) este in interiorul matricii de dimensiune m x m.

Are drept parametrii o variabila de tip "xoy", a, si
una de tip "int", dimensiunea matricii.

*/

int out_ofBounds(xoy a, int m) {
    if (a.x < 0 || a.x >= m || a.y < 0 || a.y >=m)
        return 1;

    return 0;
}

/*

Functia "fill" are drept scop marcarea pozitiilor nefavorabile.
While-ul va continua sa marcheze pe una dintre cele 4 directii,
pana cand va "iesi" din matrice (v. "out_ofBounds).

Cele 4 directii sunt, fata de punct: NV, NE, SE, SV.

Are drept parametrii o variabila de tip "int", m, dimensiunea
matricii, matricea, map, si o variabila de tip "xoy", a, ce
memoreaza punctul pentru care se va face "umplerea" (marcarea).

*/

void fill(int m, int map[][m], xoy a) {
	int i;
    xoy dir[] = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
	
    for (i = 0; i < 4; i++){
        xoy pos_init = a;
        while (out_ofBounds(pos_init, m) == 0) {
            map[pos_init.x][pos_init.y] = -1;
            pos_init.x += dir[i].x;
            pos_init.y += dir[i].y;
        }
    }
}

/*

Functia "move_bishop" este cea care rezolva, de fapt, cea de-a 2-a
cerinta a problemei, cautand pozitii favorabile pentru repozitionarea
unuia dintre nebuni.

Are drept parametrii 2 variabile de tip "int", m si n, si vectorul
v, de tip "xoy", care retine pozitiile tuturor nebunilor.
 
*/
void move_bishop(int m, int n, xoy *v) {
    int map[m][m], i, j;
	xoy a, b;
	
    memset(map, 0, sizeof(map));
    save_pair(n, v, &a, &b);	// memorarea coordonatelor celor 2 nebuni

    for (i = 0; i < n; i++)
        if (same_point(v[i], a) == 0
            && same_point(v[i], b) == 0)
                fill(m, map, v[i]);

    map[a.x][a.y] = 1;
    map[b.x][b.y] = 1;

    for (i = 0; i < m; i++)
        for (j = 0; j < m; j++) {
            xoy c;
			
            c.x = i;
            c.y = j;
            if (map[i][j] == 0 && (attacks(a, c) == 0 
				|| attacks(b, c) == 0)) {
                printf("DA\n");
                return;
            }
    }

    printf("NU\n");
}

/*

In functia "main" se realizeaza citirea numarului de perechi,
a dimensiunii matricii, numararea perechilor de nebuni
ce se ataca (prin apelarea functiei "det_pairs"). In cazul
in care exista o singura pereche ce respecta conditia, se apeleaza
functia "move_bishop", ce cauta o noua pozitie pentru unul dintre
cei doi nebuni, conform cerintei.

*/

int main() {
    int m, n, pairs;
    xoy *v;

    scanf("%d", &m);
    scanf("%d", &n);

    v = malloc(n * sizeof(xoy));

    read_bishops(n, v);

    pairs = det_pairs(n, v);
    printf("%d\n", pairs);

    if (pairs != 1)
        printf("NU\n");
    else {
		move_bishop(m, n, v);
	}
	
	free(v);
	
    return 0;
}

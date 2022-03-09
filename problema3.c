#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define code_length 11


/*

Functia "code_to_Int" returneaza codul culorii, pentru
a lucra mai usor cu fetele cubului.

Are drept parametrii un pointer de tip "char", p, si
vectorul de siruri de carcatere, codes, ce pastreaza
codificarile culorilor. 

*/

int code_to_Int(char *p, char codes[][code_length]) {
	int i;
	
    if (p[strlen(p)-1] > 'z' || p[strlen(p)-1] < 'a')
    p[strlen(p)-1] = '\0';

    for (i = 0; i < 6; i++) {
        if (strcmp(p, codes[i]) == 0)
            return i;
	}

	return -1;
}

/*

Am definit structura astfel pentru a usura procesul
de schimbare a culorilor. Cubul va avea, astfel, 6 fete
(un vector cu 6 elemente), fiecare o matrice 3 x 3.

*/

typedef struct cube {
    int side[3][3];
} cube;

/*

Functia "read_faces" citeste codificarile celor 6 fete
si insereaza in vectorul de matrici valoarea de tip "int"
a fiecarei culori ( = ordinea citirii - 1).

Are drept parametrii pointerul de tip "cube" si vectorul
de siruri de carcatere, codes, ce pastreaza codificarile culorilor.

*/

void read_faces(cube *faces, char codes[][code_length]) {
	int i, j;
	
    for (i = 0; i < 18; i++) {
        char *s, *p;

        s = (char *)malloc((code_length * 3 + 3) * sizeof(char));
        scanf("%s", s);

        j = 0;
        p = strtok(s, ".");

        while (p != NULL) {
            faces[i / 3].side[i % 3][j++] = code_to_Int(p, codes);
            p = strtok(NULL, ".");
        }
		
		free(s);
    }
	
}

/*

Functia "rotate_cw" realizeaza rotirea in sens 
invers trigonometric a unei fete a cubului.

Are drept parametru o fata a cubului, matricea m,
de dimensiune 3 x 3.

*/

void rotate_cw(int m[][3]) {
    int aux[3][3], i, j;

    aux[0][0] = m[2][0];
    aux[0][1] = m[1][0];
    aux[0][2] = m[0][0];
    aux[1][0] = m[2][1];
    aux[1][1] = m[1][1];
    aux[1][2] = m[0][1];
    aux[2][0] = m[2][2];
    aux[2][1] = m[1][2];
    aux[2][2] = m[0][2];

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            m[i][j] = aux [i][j];
}


/*

Functia "rotate_ccw" realizeaza rotirea in sens 
trigonometric a unei fete a cubului.

Are drept parametru o fata a cubului, matricea m,
de dimensiune 3 x 3.

*/

void rotate_ccw(int m[][3]) {
     int aux[3][3], i, j;

    aux[0][0] = m[0][2];
    aux[0][1] = m[1][2];
    aux[0][2] = m[2][2];
    aux[1][0] = m[0][1];
    aux[1][1] = m[1][1];
    aux[1][2] = m[2][1];
    aux[2][0] = m[0][0];
    aux[2][1] = m[1][0];
    aux[2][2] = m[2][0];

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            m[i][j] = aux [i][j];
}

/*

Urmatoarele functii realieza cele 12 mutari posibile. 
De mentionat este faptul ca functia a carui denumire 
se termina cu "rev" este cea in sens trigonometric.

Toate aceste functii au drept parametru pointerul de tip "cube",
ce pastreaza cele 6 fete ale cubului.

*/

void front(cube *faces) {
    int aux[] = {faces[2].side[2][0], faces[2].side[2][1],
            faces[2].side[2][2]};

    rotate_cw(faces[0].side);

    /// 4, c2 -> 2, r2
    faces[2].side[2][0] = faces[4].side[2][2];
    faces[2].side[2][1] = faces[4].side[1][2];
    faces[2].side[2][2] = faces[4].side[0][2];

    /// 3, r0 -> 4, c2
    faces[4].side[0][2] = faces[3].side[0][0];
    faces[4].side[1][2] = faces[3].side[0][1];
    faces[4].side[2][2] = faces[3].side[0][2];

    /// 5, c0 -> 3, r0
    faces[3].side[0][0] = faces[5].side[2][0];
    faces[3].side[0][1] = faces[5].side[1][0];
    faces[3].side[0][2] = faces[5].side[0][0];

    /// aux   -> 5, c0
    faces[5].side[0][0] = aux[0];
    faces[5].side[1][0] = aux[1];
    faces[5].side[2][0] = aux[2];

}

void front_rev(cube *faces) {
    int aux[] = {faces[2].side[2][0], faces[2].side[2][1],
            faces[2].side[2][2]};

    rotate_ccw(faces[0].side);

    /// 5, c0 -> 2, r2
    faces[2].side[2][0] = faces[5].side[0][0];
    faces[2].side[2][1] = faces[5].side[1][0];
    faces[2].side[2][2] = faces[5].side[2][0];
    /// 3, r0 -> 5, c0
    faces[5].side[0][0] = faces[3].side[0][2];
    faces[5].side[1][0] = faces[3].side[0][1];
    faces[5].side[2][0] = faces[3].side[0][0];

    /// 4, c2 -> 3, r0
    faces[3].side[0][2] = faces[4].side[2][2];
    faces[3].side[0][1] = faces[4].side[1][2];
    faces[3].side[0][0] = faces[4].side[0][2];

    /// aux   -> 4, c2
    faces[4].side[0][2] = aux[2];
    faces[4].side[1][2] = aux[1];
    faces[4].side[2][2] = aux[0];

}

void back(cube *faces) {
    int aux[] = {faces[2].side[0][0], faces[2].side[0][1],
            faces[2].side[0][2]};

    rotate_cw(faces[1].side);

    /// 5, c2 -> 2, r0
    faces[2].side[0][0] = faces[5].side[0][2];
    faces[2].side[0][1] = faces[5].side[1][2];
    faces[2].side[0][2] = faces[5].side[2][2];

    /// 3, r2 -> 5, c2
    faces[5].side[0][2] = faces[3].side[2][2];
    faces[5].side[1][2] = faces[3].side[2][1];
    faces[5].side[2][2] = faces[3].side[2][0];

    /// 4, c0 -> 3, r2
    faces[3].side[2][0] = faces[4].side[0][0];
    faces[3].side[2][1] = faces[4].side[1][0];
    faces[3].side[2][2] = faces[4].side[2][0];

    /// aux   -> 4, c0
    faces[4].side[0][0] = aux[2];
    faces[4].side[1][0] = aux[1];
    faces[4].side[2][0] = aux[0];

}

void back_rev(cube *faces) {
    int aux[] = {faces[2].side[0][0], faces[2].side[0][1],
            faces[2].side[0][2]};

    rotate_ccw(faces[1].side);

    /// 4, c0 -> 2, r0
    faces[2].side[0][0] = faces[4].side[2][0];
    faces[2].side[0][1] = faces[4].side[1][0];
    faces[2].side[0][2] = faces[4].side[0][0];

    /// 3, r2 -> 4, c0
    faces[4].side[2][0] = faces[3].side[2][2];
    faces[4].side[1][0] = faces[3].side[2][1];
    faces[4].side[0][0] = faces[3].side[2][0];

    /// 5, c2 -> 3, r2
    faces[3].side[2][0] = faces[5].side[2][2];
    faces[3].side[2][1] = faces[5].side[1][2];
    faces[3].side[2][2] = faces[5].side[0][2];

    /// aux   -> 5, c2
    faces[5].side[0][2] = aux[0];
    faces[5].side[1][2] = aux[1];
    faces[5].side[2][2] = aux[2];

}

void up(cube *faces) {
    int aux[] = {faces[0].side[0][0], faces[0].side[0][1],
            faces[0].side[0][2]};

    rotate_cw(faces[2].side);

    /// 5, r0 -> 0, r0
    faces[0].side[0][0] = faces[5].side[0][0];
    faces[0].side[0][1] = faces[5].side[0][1];
    faces[0].side[0][2] = faces[5].side[0][2];

    /// 1, r0 -> 5, r0
    faces[5].side[0][0] = faces[1].side[0][0];
    faces[5].side[0][1] = faces[1].side[0][1];
    faces[5].side[0][2] = faces[1].side[0][2];

    /// 4, r0 -> 1, r0
    faces[1].side[0][0] = faces[4].side[0][0];
    faces[1].side[0][1] = faces[4].side[0][1];
    faces[1].side[0][2] = faces[4].side[0][2];

    /// aux   -> 4, r0
    faces[4].side[0][0] = aux[0];
    faces[4].side[0][1] = aux[1];
    faces[4].side[0][2] = aux[2];

}

void up_rev(cube *faces) {
    int aux[] = {faces[0].side[0][0], faces[0].side[0][1],
            faces[0].side[0][2]};

    rotate_ccw(faces[2].side);

    /// 4, r0 -> 0, r0
    faces[0].side[0][0] = faces[4].side[0][0];
    faces[0].side[0][1] = faces[4].side[0][1];
    faces[0].side[0][2] = faces[4].side[0][2];

    /// 1, r0 -> 4, r0
    faces[4].side[0][0] = faces[1].side[0][0];
    faces[4].side[0][1] = faces[1].side[0][1];
    faces[4].side[0][2] = faces[1].side[0][2];

    /// 5, r0 -> 1, r0
    faces[1].side[0][0] = faces[5].side[0][0];
    faces[1].side[0][1] = faces[5].side[0][1];
    faces[1].side[0][2] = faces[5].side[0][2];

    /// aux   -> 5, r0
    faces[5].side[0][0] = aux[0];
    faces[5].side[0][1] = aux[1];
    faces[5].side[0][2] = aux[2];

}

void down(cube *faces) {
    int aux[] = {faces[0].side[2][0], faces[0].side[2][1],
            faces[0].side[2][2]};

    rotate_cw(faces[3].side);

    /// 4, r2 -> 0, r2
    faces[0].side[2][0] = faces[4].side[2][0];
    faces[0].side[2][1] = faces[4].side[2][1];
    faces[0].side[2][2] = faces[4].side[2][2];

    /// 1, r2 -> 4, r2
    faces[4].side[2][0] = faces[1].side[2][0];
    faces[4].side[2][1] = faces[1].side[2][1];
    faces[4].side[2][2] = faces[1].side[2][2];

    /// 5, r2 -> 1, r2
    faces[1].side[2][0] = faces[5].side[2][0];
    faces[1].side[2][1] = faces[5].side[2][1];
    faces[1].side[2][2] = faces[5].side[2][2];

    /// aux   -> 5, r2
    faces[5].side[2][0] = aux[0];
    faces[5].side[2][1] = aux[1];
    faces[5].side[2][2] = aux[2];

}

void down_rev(cube *faces) {
    int aux[] = {faces[0].side[2][0], faces[0].side[2][1],
            faces[0].side[2][2]};

    rotate_ccw(faces[3].side);

    /// 5, r2 -> 0, r2
    faces[0].side[2][0] = faces[5].side[2][0];
    faces[0].side[2][1] = faces[5].side[2][1];
    faces[0].side[2][2] = faces[5].side[2][2];

    /// 1, r2 -> 5, r2
    faces[5].side[2][0] = faces[1].side[2][0];
    faces[5].side[2][1] = faces[1].side[2][1];
    faces[5].side[2][2] = faces[1].side[2][2];

    /// 4, r2 -> 1, r2
    faces[1].side[2][0] = faces[4].side[2][0];
    faces[1].side[2][1] = faces[4].side[2][1];
    faces[1].side[2][2] = faces[4].side[2][2];

    /// aux   -> 4, r2
    faces[4].side[2][0] = aux[0];
    faces[4].side[2][1] = aux[1];
    faces[4].side[2][2] = aux[2];

}

void right(cube *faces) {
    int aux[] = {faces[2].side[0][2], faces[2].side[1][2],
            faces[2].side[2][2]};

    rotate_cw(faces[5].side);

    /// 0, c2 -> 2, c2
    faces[2].side[0][2] = faces[0].side[0][2];
    faces[2].side[1][2] = faces[0].side[1][2];
    faces[2].side[2][2] = faces[0].side[2][2];

    /// 3, c2 -> 0, c2
    faces[0].side[0][2] = faces[3].side[0][2];
    faces[0].side[1][2] = faces[3].side[1][2];
    faces[0].side[2][2] = faces[3].side[2][2];

    /// 1, c0 -> 3, c2
    faces[3].side[0][2] = faces[1].side[2][0];
    faces[3].side[1][2] = faces[1].side[1][0];
    faces[3].side[2][2] = faces[1].side[0][0];

    /// aux   -> 1, c0
    faces[1].side[2][0] = aux[0];
    faces[1].side[1][0] = aux[1];
    faces[1].side[0][0] = aux[2];
}

void right_rev(cube *faces) {
    int aux[] = {faces[2].side[0][2], faces[2].side[1][2],
            faces[2].side[2][2]};

    rotate_ccw(faces[5].side);

    /// 1, c0 -> 2, c2
    faces[2].side[2][2] = faces[1].side[0][0];
    faces[2].side[1][2] = faces[1].side[1][0];
    faces[2].side[0][2] = faces[1].side[2][0];

    /// 3, c2 -> 1, c0
    faces[1].side[2][0] = faces[3].side[0][2];
    faces[1].side[1][0] = faces[3].side[1][2];
    faces[1].side[0][0] = faces[3].side[2][2];

    /// 0, c2 -> 3, c2
    faces[3].side[0][2] = faces[0].side[0][2];
    faces[3].side[1][2] = faces[0].side[1][2];
    faces[3].side[2][2] = faces[0].side[2][2];

    /// aux   -> 0, c2
    faces[0].side[0][2] = aux[0];
    faces[0].side[1][2] = aux[1];
    faces[0].side[2][2] = aux[2];

}

void left(cube *faces) {
    int aux[] = {faces[2].side[0][0], faces[2].side[1][0],
            faces[2].side[2][0]};

    rotate_cw(faces[4].side);

    /// 1, c2 -> 2, c0
    faces[2].side[2][0] = faces[1].side[0][2];
    faces[2].side[1][0] = faces[1].side[1][2];
    faces[2].side[0][0] = faces[1].side[2][2];

    /// 3, c0 -> 1, c2
    faces[1].side[2][2] = faces[3].side[0][0];
    faces[1].side[1][2] = faces[3].side[1][0];
    faces[1].side[0][2] = faces[3].side[2][0];

    /// 0, c0 -> 3, c0
    faces[3].side[2][0] = faces[0].side[2][0];
    faces[3].side[1][0] = faces[0].side[1][0];
    faces[3].side[0][0] = faces[0].side[0][0];

    /// aux   -> 0, c0
    faces[0].side[2][0] = aux[2];
    faces[0].side[1][0] = aux[1];
    faces[0].side[0][0] = aux[0];

}

void left_rev(cube *faces) {
    int aux[] = {faces[2].side[0][0], faces[2].side[1][0],
            faces[2].side[2][0]};

    rotate_ccw(faces[4].side);

    /// 0, c0 -> 2, c0
    faces[2].side[0][0] = faces[0].side[0][0];
    faces[2].side[1][0] = faces[0].side[1][0];
    faces[2].side[2][0] = faces[0].side[2][0];

    /// 3, c0 -> 0, c0
    faces[0].side[0][0] = faces[3].side[0][0];
    faces[0].side[1][0] = faces[3].side[1][0];
    faces[0].side[2][0] = faces[3].side[2][0];

    /// 1, c2 -> 3, c0
    faces[3].side[0][0] = faces[1].side[2][2];
    faces[3].side[1][0] = faces[1].side[1][2];
    faces[3].side[2][0] = faces[1].side[0][2];

    /// aux   -> 1, c2
    faces[1].side[2][2] = aux[0];
    faces[1].side[1][2] = aux[1];
    faces[1].side[0][2] = aux[2];

}

/*

Functia "simulate_move" apeleaza functia corespunzatoare
mutarii dorite.

Are drep parametrii indicele mutarii (a fost pastrata
ordinea prezentarii din enuntul problemei) si pointerul
de tip "cube".

*/

void simulate_move(int i, cube *faces) {
    switch (i) {
        case 0:
            front(faces);
            break;
        case 1:
            front_rev(faces);
            break;
        case 2:
            back(faces);
            break;
        case 3:
            back_rev(faces);
            break;
        case 4:
            up(faces);
            break;
        case 5:
            up_rev(faces);
            break;
        case 6:
            down(faces);
            break;
        case 7:
            down_rev(faces);
            break;
        case 8:
            right(faces);
            break;
        case 9:
            right_rev(faces);
            break;
        case 10:
            left(faces);
            break;
        case 11:
            left_rev(faces);
    }
}

/*

Functia "main" este responsabila pentru citirea codificarii
culorilor si prelucrarea acestora pentru adaugarea in 
"codes". In acelasi timp, face legatura intre codificarea
mutarilor si functia responsabila pentru fiecare in parte.
In final, afiseaza ultima stare a cubului rubic, dupa 
realizarea tuturor mutarilor.

*/

int main() {

    char *s, *p, *read_Moves, codes[6][code_length],
        moves[][3]={"F","F'", "B", "B'", "U", "U'",
            "D", "D'", "R", "R'", "L", "L'"};
	int i_Code = 0, number_ofMoves, i, j;
	cube faces[6];
	
    s = (char *)malloc(6 * code_length * sizeof(char));
    fgets(s, 6 * code_length, stdin);

    p = strtok(s, " ");
    while ( p != NULL) {
        if (p[strlen(p)-1] > 'z' || p[strlen(p)-1] < 'a')
            p[strlen(p)-1] = '\0';
        strcpy(codes[i_Code++], p);
        p = strtok( NULL, " ");
    }
	
    read_faces(faces, codes);

    scanf("%d", &number_ofMoves);

    read_Moves = (char *)malloc(300 * sizeof(char));

    getchar();
    fgets(read_Moves, 300, stdin);

    p = strtok(read_Moves, " ");

    while (p != NULL) {
        if (strlen(p) == 3 || (strlen(p) == 2 && p[1] != '\''))
            p[strlen(p)-1] = '\0';

        for (i = 0; i < 12; i++) {
            if (strcmp(p, moves[i]) == 0)
                simulate_move(i, faces);
        }

        p = strtok(NULL, " ");
    }


    for (i = 0; i < 6; i++) {
        for (j = 0; j < 3; j++)
                printf("%s.%s.%s\n", 
					codes[faces[i].side[j][0]],
                      codes[faces[i].side[j][1]], 
						codes[faces[i].side[j][2]]);
    }

	free(s);
	free(read_Moves);
	
    return 0;
}

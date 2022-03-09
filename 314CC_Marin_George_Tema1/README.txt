Problema I - Anagrame
~ 2h

Principiul solutiei este urmatorul:

1. Citirea perechilor intr-o structura ce memoreaza si gradul determinat
cu ajutorul functiei "compute_grade".

2. Sortarea structurii in functiei de gradul calculat anterior, cu ajutorul
functiei "sort_grade".

3. Afisarea structurii ordonate, cu ajutorul functiei "out".

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Problema II - Sah
~ 2h

Principiul solutiei este urmatorul:

1. Citirea coordonatelor nebunilor intr-o structura echivalenta 
coordonatelor in sistem ortogonal xoy.

2. Determinarea numarului de perechi de nebuni ce se ataca, utilizand
panta dintre cele doua puncte din plan, ale caror coordonate sunt 
(a.x, a.y), respectiv (b.x, b.y). Daca panta este 1 sau -1, inseamna ca
cei doi nebuni se afla pe diagonala, deci se ataca -> numarul perechilor
va creste.

3. Daca numarul perechilor de nebuni este mai mare decat 1, vom afisa "NU".
In caz contrar, va fi apelata functia "move_bishop", care va cauta o
pozitie favorabila pentru oricare dintre cei doi nebuni. Pentru a face acest
lucru, vom cauta perechea de nebuni care se ataca, pe care o pastram in 
doua variabile de tip "xoy", a si b. 

In continuare, vom utiliza o matrice pentru a marca pozitiile tuturor 
celorlalti nebuni ca fiind ocupate (-1), alaturi de diagonalele pe care 
acestia se pot deplasa (-1). Am preferat aceasta metoda pentru a nu verifica
inutil, pentru fiecare noua pozitie aparent favorabila, daca va fi atacata
de restul nebunilor. Astfel, fiecare X determinat de un nebun (cele doua 
diagonale pe care se poate deplasa) este marcat ca fiind ocupat.

De marcarea pozitiilor se ocupa functia "fill" - am preferat implementarea
cu cele 4 directii salvate sub forma unui vector de tip "xoy" tocmai pentru
a evita lucrul greoi cu indicii. Cand "out_ofBounds" returneaza 1, nu se mai
continua pe directia curenta.

Cautarea unei pozitii favorabile este realizata astfel - este parcursa 
matricea anterior formata si pentru fiecare pozitie "libera" se verifica
daca este accesibila de oricare dintre cei doi nebuni fixati la inceput.
Daca nu este accesibila pentru oricare dintre ei, inseamna ca poate deveni
pozitia celuilalt nebun, deci am gasit o solutie -> vom afisa "DA". In caz
contrar, vom afisa "NU".

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Problema III - Rubik's Cube
~ 6h

Principiul solutiei este urmatorul:

1. Citirea codificarii culorilor utlizate si adaugarea acestora intr-un
vector de siruri de caractere. Acesta va fi utilizat pentru a putea
transforma prescurtarile in numere de la 0 la 5.

2. Citirea fetelor - se citeste cate un rand intreg si cele 3 culori 
se adauga in matricea fetei respective (18 randuri, 6 fete, 3 randuri pe
fiecare fata, de unde vin [i/3] si [i%3]). Cum s a fost alocat dinamic,
se elibereaza memoria la finalul functiei "read_faces".

3. Citirea miscarilor si identificarea lor, prin comparatia cu elementele
vectorului moves. Cand se gaseste echivalentul, se apeleaza functia 
"simulate_move" ce, la randul sau, apeleaza miscarea corespunzatoare
(miscarile sunt indexate in ordinea in care sunt specificate in enuntul
problemei).

4. Simularea efectiva a miscarilor.

5. Afisarea cubului rezultat, revenind la codificarea pe care o avem
memorata intr-un vector de siruri de caractere, codes.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Problema IV - X si 0
~ 2h

Principiul solutiei este urmatorul:

1. Citirea numerelor ce urmeaza sa fie transformate in liniile matricii.
Apeland doua functii "dec_to_bin" si "s_to_row", numerele sunt trecute
din baza 10 in baza 2, pastrate fiind intr-un sir de caractere, s, ale
carui caractere vor fi transformate in "int" ('0' devine 0, cifra) si
adaugate pe liniile matricii.

2. Determinarea matricei transpuse, cu ajutorul functiei "transpose" si
calcularea A*A(t), respectiv A*A = A^2. Am reutilizat, astfel, functia
"product", ce realizeza inmultirea a doua matrici.

3. Scorul este calculat intocmai cum procedeul este descris in enunt:
"Andrei va calcula scorul X si 0 impartind matricea in 4 parti egale".
Astfel, am realizat functia "small_sum_X_0", ce calculeaza scorul
pentru o matrice de 4 x 4 (functia este apelata de 4 ori pentru 
fiecare dintre matricile A, A*A(t) si A^2). Am copiat 
cele 4 portiuni ale matricei de 8 x 8 in matrici de 4 x 4, pe careS
am apelat functia anterior mentionata. "sum_X_0", ceruta in enunt,
are rolul de a copia zonele de 4 x 4 si a aduna scorul total.

4. Afisareaa matricii conform criteriilor enuntate in cerinta:
scor, A > A*A(t) > A^2
// RADULESCU ROBERT STEFAN 315 CC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int id;
    char *nume;
} cartier;

typedef struct {
    int id;
    int adresa[18];
    int idCartier;
    int strada;
    int numar;
    int prioritate;
    float greutate;
    char *mesaj;
    int codificare_mesaj;
} pachet;

typedef struct {
    int id;
    int nrPachete;
    int vector_pachete[50];
} postas;

void citire(int *nrC, int *nrP, cartier cartiere[], pachet pachete[]) {
    int i,j;
    scanf("%d", nrC);
      
    for ( i = 0; i < *nrC; i++) {
        char aux[50];  // vector auxiliar pentru alocare dinamica a numelui
        scanf("%s", aux);
        cartiere[i].nume = malloc((strlen(aux) + 1) * sizeof(char));
        strcpy(cartiere[i].nume, aux);
        cartiere[i].id = i;
    }

    scanf("%d", nrP);

    for ( j = 0; j < *nrP; j++) {
        for ( i = 0; i < 18; i++)
            scanf("%d", &pachete[j].adresa[i]);

        scanf("%d", &pachete[j].prioritate);
        scanf("%f", &pachete[j].greutate);
        getchar();      // consuma new-lineu ramas in buffer
        char aux[100];  // vector auxiliar pentru alocarea spatiului mesajului
        fgets(aux, sizeof(aux), stdin);

        pachete[j].mesaj = malloc((strlen(aux) + 1) * sizeof(char));
        strcpy(pachete[j].mesaj, aux);
        pachete[j].id = j;
    }
}

// afisare task 1

void afisare_1(int nrC, int nrP, cartier cartiere[], pachet pachete[]){
    int i, j;
    for (i = 0; i < nrC; i++)
        printf("%d %s\n", cartiere[i].id, cartiere[i].nume);

    for (i = 0; i < nrP; i++)
    {
        printf("%d\n", pachete[i].id);
        for ( j = 0; j < 18; j++)
        {
            printf("%d", pachete[i].adresa[j]);
            if (j < 17) // verifica daca se ajunge la ultimul termen incat sa nu mai puna un spatiu la sfarsit
                printf(" ");
        }
        printf("\n");
        printf("%d %.3f\n", pachete[i].prioritate, pachete[i].greutate);
        printf("%s", pachete[i].mesaj);
    }
}

void binar(int nrP, pachet pachete[])
{
    int i,j;
    for ( i = 0; i < nrP; i++)
    {
        int k1 = 1, k2 = 1, k3 = 1;

        // calculez idCariter(adresa[0-4])
        for (j = 4; j >= 0; j--) {
            if (pachete[i].adresa[j] == 1)
                pachete[i].idCartier += k1;
            k1 *= 2;
        }

        // calculez strada(adresa[5-9])
        for ( j = 9; j > 4; j--) {
            if (pachete[i].adresa[j] == 1)
                pachete[i].strada += k2;
            k2 *= 2;
        }

        // calculez numar(adresa[10-17])
        for ( j = 17; j > 9; j--) {
            if (pachete[i].adresa[j] == 1)
                pachete[i].numar += k3;
            k3 *= 2;
        }
    }
}

// afisare task 2

void afisare_2(int nrP, pachet pachete[]) {
    int i;
    for ( i = 0; i < nrP; i++) {
        printf("%d\n", pachete[i].id);
        printf("%d %d %d\n", pachete[i].idCartier, pachete[i].strada, pachete[i].numar);
    }
}

void distribuire_pachete(int nrC, cartier cartiere[], int nrP, pachet pachete[], postas postas[]) {
    int i,j;
    for ( i = 0; i < nrC; i++) {
        postas[i].id = cartiere[i].id;
        postas[i].nrPachete = 0;
        int k = 0; // nr pozitia pentru vector_pachete
        for ( j = 0; j < nrP; j++)
            if (postas[i].id == pachete[j].idCartier) {
                postas[i].nrPachete++;
                postas[i].vector_pachete[k] = j;  // atribuie id ul pachetului fiecarui postas
                k++;
            }
    }
}

// afisare pentru task 3

void afisare_3(int nrC, postas postas[]) {
    int i,j;
    for (i = 0; i < nrC; i++) {
        printf("%d %d\n", postas[i].id, postas[i].nrPachete);
        if (postas[i].nrPachete != 0) {
            for ( j = 0; j < (postas[i].nrPachete - 1); j++)
                printf("%d ", postas[i].vector_pachete[j]);
            printf("%d\n", postas[i].vector_pachete[postas[i].nrPachete - 1]);
        }
    }
}

void ordonare_pachete(int nrC, postas postas[], pachet pachete[]) {
    int i,j,k;
    for ( i = 0; i < nrC; i++) {

        // verifica daca postasul are mai multe pachete pentru a putea fi ordonate
        if (postas[i].nrPachete > 1)
        {
            // am folosit bubble sort ,sortand prima data greutatile tuturor pachetelor iar apoi prioritatile
            for ( j = 0; j < postas[i].nrPachete - 1; j++)
                for ( k = 0; k < postas[i].nrPachete - j - 1; k++)
                    // compar pachetele dupa greutate
                    if (pachete[postas[i].vector_pachete[k]].greutate < pachete[postas[i].vector_pachete[k + 1]].greutate) { 
                        // schimbam ordinea pachetelor
                        int aux = postas[i].vector_pachete[k];
                        postas[i].vector_pachete[k] = postas[i].vector_pachete[k + 1];
                        postas[i].vector_pachete[k + 1] = aux;
                    }

            for ( j = 0; j < postas[i].nrPachete - 1; j++)
                for ( k = 0; k < postas[i].nrPachete - j - 1; k++)
                    // compar pachetele dupa prioritate
                    if (pachete[postas[i].vector_pachete[k]].prioritate < pachete[postas[i].vector_pachete[k + 1]].prioritate) { 
                        // schimbam ordinea pachetelor
                        int aux = postas[i].vector_pachete[k];
                        postas[i].vector_pachete[k] = postas[i].vector_pachete[k + 1];
                        postas[i].vector_pachete[k + 1] = aux;
                    }
        }
    }
}

// functie pentru stergerea semnelor 

void eliminare_semne(int nrP, pachet pachete[]) {
    char semne[] = ".,?!:"; // sir cu semnele pe care trebuie sa le elimin
    char spatiu[] = " ";
    int i,j,k;
    for ( i = 0; i < nrP; i++) {
        // elimin newline-ul de la sfarsitul mesajului

        if (pachete[i].mesaj[strlen(pachete[i].mesaj) - 1] == '\n') {
            pachete[i].mesaj[strlen(pachete[i].mesaj) - 1] = '\0';
        }
        char final[1000] = "";                     // string care va primi mesajul final
        char *aux = strtok(pachete[i].mesaj, " "); // impartim mesajul in cuvinte

        while (aux != NULL) { 
            // aloc spatiu pentru cuvantul fara semne
            char *cuvant_fara_semne = malloc((strlen(aux) + 1) * sizeof(char));
            int len = 0; // lungimea cuvantului

            for ( j = 0; j < strlen(aux); j++) // parcurgere cuvant
            {
                int este_semn = 0;

                // parcurgere pentru fiecare semn
                for ( k = 0; k < strlen(semne); k++) {
                    // verifica daca exista cuvinte care sunt despartite DOAR printr un semn si va pune un spatiu in locul semnului
                    if (aux[j] == semne[k] && (aux[j - 1] != spatiu[0] || aux[j + 1] != spatiu[0]))
                        este_semn = 2;

                    else if (aux[j] == semne[k]) {
                        este_semn = 1;
                        break;
                    }
                }
                if (este_semn == 2)
                    cuvant_fara_semne[len++] = spatiu[0]; // pune spatiu in locul semnului in cazul explicat mai sus
             
                else if (!este_semn) // daca nu este semn adauga litera 
                {
                    cuvant_fara_semne[len] = aux[j];
                    len++;
                }
            }

            cuvant_fara_semne[len] = '\0'; // adaug nul la sfarsitul cuvantului

            strcat(final, cuvant_fara_semne);
            strcat(final, " "); // adaug spatiu intre cuvinte
            free(cuvant_fara_semne);

            aux = strtok(NULL, " "); // trecem la urmatorul cuvant
        }

        free(pachete[i].mesaj); // eliberam memoria initiala a mesajului
        pachete[i].mesaj = malloc((strlen(final) + 1) * sizeof(char));
        strcpy(pachete[i].mesaj, final); // inlocuim cu mesajul nou fara semne
    }
}

void inversare_cuvinte(int nrP, pachet pachete[]) {
    int i,j;
    for ( i = 0; i < nrP; i++) {

        char *cuvinte[100];                        // vector pentru stocarea cuvintelor
        int nr_cuvinte = 0;                        // nr de cuvinte
        char *aux = strtok(pachete[i].mesaj, " "); // imparte mesajul in cuviinte
        while (aux != NULL) { 
            // aloc memorie pentru fiecare cuvant
            cuvinte[nr_cuvinte] = malloc((strlen(aux) + 1) * sizeof(char));
            strcpy(cuvinte[nr_cuvinte], aux);

            nr_cuvinte++;
            aux = strtok(NULL, " "); // trec la cuvantul urmator
        }
        char final[1000] = ""; // string pentru mesajul modificat

        // construim mesajul in oridne inversa
        for ( j = nr_cuvinte - 1; j >= 0; j--) {
            strcat(final, cuvinte[j]);
            free(cuvinte[j]);
        }
        free(pachete[i].mesaj);
        pachete[i].mesaj = malloc((strlen(final) + 1) * sizeof(char));
        strcpy(pachete[i].mesaj, final);
    }
}
// functie pentru calcularea codului din mesaj
void calculeaza_cod(int nrP, pachet pachete[])  {
    int i,j;
    for ( i = 0; i < nrP; i++) {
        pachete[i].codificare_mesaj = 0;

        for ( j = 0; pachete[i].mesaj[j] != '\0'; j++) // parcurge fiecare caracter din mesaj si calculeaza codul
            pachete[i].codificare_mesaj += pachete[i].mesaj[j] * j;
        pachete[i].codificare_mesaj = pachete[i].codificare_mesaj % (pachete[i].strada * pachete[i].numar + 1);
    }
}
// afisare pentru task 5
void afisare_cod(int nrP, pachet pachete[], postas postas[], int nrC) {
    int i,j;
    for ( i = 0; i < nrC; i++) {
        printf("%d %d\n", postas[i].id, postas[i].nrPachete);
        if (postas[i].nrPachete != 0)
        {
            for ( j = 0; j < (postas[i].nrPachete); j++)
            {
                printf("%d ", postas[i].vector_pachete[j]);
                printf("%d\n", pachete[postas[i].vector_pachete[j]].codificare_mesaj);
            }
        }
    }
}
// functie pentru gasirea factorilor primi
void factori_primi(int id, int factori[], int *nr_factori) {
    int i;
    *nr_factori = 0;

    if (id == 0) // daca id ul este 0 adaugam 0 ca factor
    {
        factori[*nr_factori] = 0;
        *nr_factori += 1;
    }
    if (id == 1) // daca id ul este 1 adaugam 1 ca factor
    {
        factori[*nr_factori] = 1;
        *nr_factori += 1;
    }

    // gasim factorii primi
    for (i = 2; i <= id; i++)
    {
        if (id % i == 0)
        {
            factori[*nr_factori] = i;
            *nr_factori += 1;
            while (id % i == 0)
            {
                id /= i;
            }
        }
    }
}

void modifica_cod(int *cod, int factori[], int nr_factori) {
    int binar[32] = {0}, temp = *cod, k = 0,i;

    // convertire cod in binar
    while (temp != 0) {
        binar[k] = temp % 2;
        k++;
        temp /= 2;
    }

    for ( i = 0; i < nr_factori; i++) // partcurgem fiecare factor
    {
        int poz = factori[i]; // pozitia in binar indicata de factorul prim
        if (poz < k) {
            // inversam bitul
            if (binar[poz] == 0)
                binar[poz] = 1;
            else
                binar[poz] = 0;
        }
    }

    *cod = 0;

    // reconstruim codul
    for ( i = 0; i < k; i++) {
        *cod += binar[i] * pow(2, i);
    }
}

void verificare_nr(int id, postas postas[], pachet pachete[]) {
    int factori[32], nr_factori,i;

    factori_primi(id, factori, &nr_factori); // gasim factorii primi ai id-ului

    for ( i = 0; i < postas[id].nrPachete; i++) {
        int lungime = 0;
        int ok = 0; // verifica daca secventa e gasita
        int aux = id;

        // calculam lungimea numerica a idului
        if (aux == 0) {
            lungime = 1;
        }
        else {
            while (aux > 0) {
                lungime++;
                aux /= 10;
            }
        }
        int cod = pachete[postas[id].vector_pachete[i]].codificare_mesaj;

        // cauta id ul in codul pachetului
        while (cod > 0) {
            int secventa = cod % (int)pow(10, lungime); // extragem o secventa din cod de lungimea idului

            if (secventa == id) {
                ok = 1;
                break;
            }
            cod /= 10; // trecem la urmatoarea secventa
        }

        // modifica codul
        if (ok == 1) {
            modifica_cod(&pachete[postas[id].vector_pachete[i]].codificare_mesaj, factori, nr_factori);
        }
    }
}

// functie aproape identica cu verificare_nr insa retine numarul de pachete nemodificate
void task_7(int id, postas postas[], pachet pachete[], float *nr_pachete_nemodificate) {
    int factori[32], nr_factori,i;
    *nr_pachete_nemodificate = postas[id].nrPachete;
    factori_primi(id, factori, &nr_factori);

    for (i = 0; i < postas[id].nrPachete; i++) {
        int lungime = 0;
        int ok = 0;
        int aux = id;

        if (aux == 0) {
            lungime = 1;
        }
        else {
            while (aux > 0)
            {
                lungime++;
                aux /= 10;
            }
        }
        int cod = pachete[postas[id].vector_pachete[i]].codificare_mesaj;

        while (cod > 0) {
            int secventa = cod % (int)pow(10, lungime);
            if (secventa == id)
            {
                ok = 1;
                break;
            }
            cod /= 10;
        }
        if (ok == 1) {
            modifica_cod(&pachete[postas[id].vector_pachete[i]].codificare_mesaj, factori, nr_factori);
            *nr_pachete_nemodificate -= 1;  // retine nr de pachete nemodificate
        }
    }
}

int main() {
    int nrC, nrP, task,i;
    float nr_pachete_modificate = 0;
    cartier cartiere[100];
    pachet pachete[100];
    postas postas[100];
    scanf("%d", &task);  // citire task
    switch (task)       // instructiune pentru fiecare task
      {
    case 1:
        citire(&nrC, &nrP, cartiere, pachete);
        afisare_1(nrC, nrP, cartiere, pachete);
        break;
    case 2:
        citire(&nrC, &nrP, cartiere, pachete);
        binar(nrP, pachete);
        afisare_2(nrP, pachete);
        break;
    case 3:
        citire(&nrC, &nrP, cartiere, pachete);
        binar(nrP, pachete);
        distribuire_pachete(nrC, cartiere, nrP, pachete, postas);
        afisare_3(nrC, postas);
        break;
    case 4:
        citire(&nrC, &nrP, cartiere, pachete);
        binar(nrP, pachete);
        distribuire_pachete(nrC, cartiere, nrP, pachete, postas);
        ordonare_pachete(nrC, postas, pachete);
        afisare_3(nrC, postas);
        break;
    case 5:
        citire(&nrC, &nrP, cartiere, pachete);
        binar(nrP, pachete);
        distribuire_pachete(nrC, cartiere, nrP, pachete, postas);
        ordonare_pachete(nrC, postas, pachete);
        eliminare_semne(nrP, pachete);
        inversare_cuvinte(nrP, pachete);
        calculeaza_cod(nrP, pachete);
        afisare_cod(nrP, pachete, postas, nrC);

        break;
    case 6:
        citire(&nrC, &nrP, cartiere, pachete);
        binar(nrP, pachete);
        distribuire_pachete(nrC, cartiere, nrP, pachete, postas);
        ordonare_pachete(nrC, postas, pachete);
        eliminare_semne(nrP, pachete);
        inversare_cuvinte(nrP, pachete);
        calculeaza_cod(nrP, pachete);
        for ( i = 0; i < nrC; i++)
            verificare_nr(i, postas, pachete);
        afisare_cod(nrP, pachete, postas, nrC);
        break;
    case 7:
        citire(&nrC, &nrP, cartiere, pachete);
        binar(nrP, pachete);
        distribuire_pachete(nrC, cartiere, nrP, pachete, postas);
        ordonare_pachete(nrC, postas, pachete);
        eliminare_semne(nrP, pachete);
        inversare_cuvinte(nrP, pachete);
        calculeaza_cod(nrP, pachete);
        for (i = 0; i < nrC; i++) {
            task_7(i, postas, pachete, &nr_pachete_modificate);
            if (postas[i].nrPachete != 0)
                printf("%d %0.3f\n", i, nr_pachete_modificate / postas[i].nrPachete);
            else
                printf("%d 0.000\n", i);
        }
        break;
    }

    return 0;
}

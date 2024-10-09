#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lists.h"
/*COSTACHE David-Mihai - 313CC*/
/*Aceasta functie creeaza un vagon
nou de fiecare data cand este nevoie*/
wagon *generete_car(char s){
    wagon *car = (wagon *)malloc(sizeof(wagon));
    car->symbol = s;
    car->next = car->prev = NULL;
    return car;
}

/*Aceasta functie initializeaza trenul in memorie*/
void init_train(train **t){
    (*t) = (train *)malloc(sizeof(train));
    (*t)->sentinel = (wagon*) malloc(sizeof(wagon));
    wagon *first = generete_car('#');
    (*t)->sentinel->next = (*t)->sentinel->prev = first;
    first->prev = first->next = (*t)->sentinel;
    (*t)->mechanic = first;
    (*t)->len = 1;
}

/*Functia muta mecanicul la dreapta*/
void move_left (train *t){ 
    if (t->mechanic == t->sentinel->next) {
        t->mechanic = t->sentinel->prev;
    } else {
        t->mechanic = t->mechanic->prev;
    }
}

 /*Daca mecanicul se afla in ultimul vagon
se creeaza un vagon nou, in caz contrar,
doar se muta mecanicul mai la dreapta*/
void move_right (train *t) { 
    if (t->mechanic == t->sentinel->prev) { 
        wagon *car = generete_car('#');   
        t->sentinel->prev = car;
        t->mechanic->next = car;
        car->prev = t->mechanic;
        car->next = t->sentinel;
        t->mechanic = car;
        t->len++;
        return;
    } else {
        t->mechanic = t->mechanic->next;
        return;
    }
}

void write(train *t, char c) {
    t->mechanic->symbol = c;
}

void clear_cell(train *t) {
    //Daca deja mecanicul este pe primul vagon,
    //se modifica doar caracterul, intrucat 
    //oricum trebuie readus la structura initiala
    if (t->sentinel->next == t->sentinel->prev) {
        t->mechanic->symbol = '#';
        return;
    }
    //daca nu, se sterge vagonul respectiv,
    //refacandu-se legaturile
    wagon *temp = t->mechanic;
    wagon *prev = t->mechanic->prev;
    t->mechanic->prev->next = t->mechanic->next;
    t->mechanic->next->prev = t->mechanic->prev;
    t->mechanic = t->sentinel->prev;
    t->len--;
    free(temp);
    if (prev == t->sentinel) {
        t->mechanic = t->sentinel->prev;
    } else {
        t->mechanic = prev;
    }
}

void clear_all(train *t) {
    //intrucat trenul trebuie adus la forma
    //initiala, controlorul merge pe al doilea
    //vagon si incepe distrugerea vagoanelor
    //pana ajunge la santinela
    wagon *inspector = t->sentinel->next->next;
    while (inspector != t->sentinel) {
        wagon *temp = inspector;
        inspector = inspector->next;
        free(temp);
    }
    // se refac legaturile intre primul vagon
    // si santinela
    t->sentinel->prev = t->sentinel->next;
    t->sentinel->next->next = t->sentinel;
    t->mechanic = t->sentinel->next;
    t->mechanic->symbol = '#';
}


void show(train *t, FILE *f) {
    wagon *inspector = t->sentinel->next;
    while (inspector != t->sentinel) {
        if (inspector == t->mechanic) {
            fprintf(f, "|%c|", t->mechanic->symbol);
        }
        else {
            fprintf(f, "%c", inspector->symbol);
        }
        inspector = inspector->next;
    }
    fprintf(f, "\n");
}

void show_current(train *t, FILE *f) {
    fprintf(f, "%c\n", t->mechanic->symbol);
}


void insert_left(train *t, char c, FILE *f) {
    if(t->mechanic == t->sentinel->next) {
        fprintf(f, "ERROR\n");
        return;
    }
    wagon *car = generete_car(c);
    car->prev = t->mechanic->prev;
    car->next = t->mechanic;
    t->mechanic->prev->next = car;
    t->mechanic->prev = car;
    t->mechanic = car;
    t->len++;
    return;
}


void insert_right(train *t, char c) {
    //se va crea un vagon nou si se vor
    //reface legaturile cu prev-ul mecanicului
    // si cu next-ul acestuia
    wagon *car = generete_car(c);
    t->mechanic->next->prev = car;
    car->next = t->mechanic->next;
    t->mechanic->next = car;
    car->prev = t->mechanic;
    t->mechanic = car;
    t->len++;
    return;
}

/*Functia stocheaza intr-un sir alocat dinamic
toate caracterele, sarind peste santinela
, iar ma apoi se verifica, cu
strstr, daca exista un sir inclus in aux.
Pentru a obtine pozitia de inceput m am folosit
de scaderea a doi pointeri care sunt de acelasi tip,
in acelasi sir.*/
void search(train *t, char *s, FILE *f) {
    if (t->sentinel->next == t->sentinel->prev) {
            fprintf(f, "ERROR\n");
            return;
        }
    wagon *iter = t->mechanic->next;
    char *aux =(char *)malloc(sizeof(char) * (t->len + 2));
    int index = 0;
    aux[index++] = t->mechanic->symbol;
    while(iter != t->mechanic) {
        if(iter == t->sentinel && iter->next != t->mechanic) {
        iter = iter->next; 
        }
        aux[index++] = iter->symbol;
        iter = iter->next;
    }
    aux[index] = '\0';
    char *p = strstr(aux,s);
    if (!p) {
        fprintf(f, "ERROR\n");
        free(aux);
        return;
    }
    else {
        int poz = p - aux;
        wagon *iter = t->mechanic;
        while(poz > 0) {
            iter = iter->next;
            if (iter == t->sentinel) {
                poz++;
            }
        poz--;
        }
        t->mechanic = iter;
    }
    free(aux);
}

/*Functia merge pe acelasi principiu ca celalalte doua,
doar ca aici a fost mai usor, nemaifiind nevoie sa trec
de santinela, insa a fost nevoie sa deduc o formula pentru
pozitie. */
void search_left(train *t, char *s, FILE *f) {
    wagon *iter = t->mechanic;
    char *aux = (char *)malloc(sizeof(char) * (t->len + 1));
    int poz = 0;
    while(iter != t->sentinel) {
        aux[poz++] = iter->symbol;
        iter = iter->prev; 
    }
    //terminatorul de sir
    aux[poz] = '\0';
    char *p = strstr(aux, s);
    if (!p) {
        fprintf(f, "ERROR\n");
        free(aux);
        return;
    }
    else {
        p+= strlen(s);
        int poz = p - aux - 2;
        wagon *iter = t->mechanic->prev;
        //cand ajunge la 0 se va afla la locul potrivit
        while(iter != t->sentinel && poz > 0) {
            poz--;
            iter = iter->prev;
        }
        t->mechanic = iter;
    }
    free(aux);
}

/*Functia este la fel cu celelalte doua*/
void search_right(train *t, char *s, FILE *f) {
    wagon *iter = t->mechanic;
    char *aux = (char *)malloc(sizeof(char) * (t->len + 1));
    int poz = 0;
    while (iter != t->sentinel) {
        aux[poz++] = iter->symbol;
        iter = iter->next;
    }
    aux[poz] = '\0';
    char* p = strstr(aux, s);
    if(!p) {
        fprintf(f, "ERROR\n");
        free(aux);
        return;
    } else {
        int poz = p - aux + strlen(s) - 1;
        wagon *iter = t->mechanic;
        while (poz > 0 && iter != t->sentinel) {
            poz--;
            iter = iter->next;
        }
        t->mechanic = iter;
    }
    free(aux);
}

/*Functia este apelata atunci cand este data o
comanda execute.*/
void execute(train *t, char *s, FILE *f) {
    //p extrage primul cuvant
    char *p = strtok(s," \n");
    //cat timp nu s-a ajuns la sfarsit de linie
    while(p != NULL) {
        if (strcmp(p, "WRITE") == 0) {
            p = strtok(NULL, "\n");
            char c = *p;
            write(t, c);
            return;
        }
        if (strcmp(p, "MOVE_RIGHT") == 0) {
            move_right(t);
            return;
        }
        if (strcmp(p, "MOVE_LEFT") == 0) {
            move_left(t);
        }
        if (strcmp(p, "INSERT_LEFT") == 0) {
            p = strtok(NULL, "\n");
            char c = *p;
            insert_left(t, c, f);
            return;
        }
        if (strcmp(p, "INSERT_RIGHT") == 0) {
            p = strtok(NULL, "\n");
            char c = *p;
            insert_right(t, c);
            return;
        }
        if (strcmp(p, "CLEAR_CELL") == 0) {
            clear_cell(t);
            return;
        }
        if (strcmp(p, "CLEAR_ALL") == 0)  {
            clear_all(t);
            return;
        }
        if (strcmp(p, "SEARCH") == 0) {
            p = strtok(NULL, "\n");
            search(t, p, f);
            return;
        }
        if (strcmp(p, "SEARCH_LEFT") == 0) {
            p = strtok(NULL, "\n");
            search_left(t, p, f);
            return;
        }
        if (strcmp(p, "SEARCH_RIGHT") == 0) {
            p = strtok(NULL, "\n");
            search_right(t, p, f);
            return;
        }
        //in caz de nu a fost match
        //se trece la urmatorul cuvant
        p = strtok(NULL, "\n");
    }
}

/*Pentru a nu exista leak-uri, functia dezaloca
tot trenul si vagoanele din el, apoi santinela, care
era alocata in "init_train", si in final, structura in
sine.*/
void free_memory(train **t) {
    wagon *iter = (*t)->sentinel->next;
    while (iter != (*t)->sentinel) {
        wagon *temp = iter;
        iter = iter->next;
        free(temp);
    }
    free((*t)->sentinel);
    free(*t);
}
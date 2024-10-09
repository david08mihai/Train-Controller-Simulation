#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lists.h"
#include "queue.h"

int main() {
    FILE *f = fopen("tema1.in", "r");
    //in caz de fisierul nu a fost creat
    //se iese din program, pentru a nu 
    //surveni alte probleme
    if (!f) {
        exit(-1);
    }
    FILE *out = fopen("tema1.out", "w");
    int n, i;
    train *bullet_train;
    queue *Queue;
    //initializare, prin referinta, a cozii
    //si a trenului
    initq(&Queue);
    init_train(&bullet_train);
    fscanf(f, "%d", &n);
    char c;
    //se ia '\n'-ul lasat de la comanda de
    //la linia 18
    fscanf(f, "%c", &c);
    //citirea a n comenzi
    for (i = 0; i < n; ++i) {
        //command declarat pe 20 de caractere,
        //intrucat nu se stiu dimensiunile 
        //comenzilor
        char command[20] = {0};
        fgets(command, 20, f);
        //eliminarea '\n'-ului de la final
            command[strlen(command) - 1] = '\0';
        if (strcmp(command, "SHOW") == 0) {
            show(bullet_train, out);
        } else if (!strcmp(command, "SHOW_CURRENT")) {
            show_current(bullet_train, out);
        } else if (!strcmp(command, "SWITCH")) {
            SWITCH(Queue);
        } else if (!strcmp(command, "EXECUTE")){
            //scoaterea din coada si executia
                char *s =pop_queue(Queue);
                execute(bullet_train, s, out);
                free(s);
        } else {
            add_queue(Queue, command);
        }
    }
    freeq(&Queue);
    fclose(f);
    fclose(out);
    free_memory(&bullet_train);
    return 0;
}
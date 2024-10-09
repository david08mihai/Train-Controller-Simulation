#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "lists.h"
/*COSTACHE David-Mihai - 313CC*/

/*Alocarea cozii*/
void initq(queue **q) {
    (*q) = (queue *) malloc(sizeof(queue));
    (*q)-> head = (*q)-> tail = NULL;
    (*q)-> len = 0;
}

/*Functie pentru a pune intr-un element
din coada sirul primit ca parametru;
Alocarea se face exact pe numarul de caractere 
din sir.*/
node *createnode(char *s) {
    node *Node =(node *) malloc(sizeof(node));
    Node->next = Node->prev = NULL ;
    Node->data = (char *) malloc((strlen(s) + 1) * sizeof(char));
    strcpy(Node->data, s);
    return Node;
}

/*Adaugare unui sir in coada*/
void add_queue(queue *q, char *s){
    if (!q) return;
    if (!q->tail || !q->head) {
        node *Node = createnode(s);
        q->head = q->tail = Node;
        q->len++;
        return;
    }
    node *Node = createnode(s);
    q->tail->next = Node;
    Node->prev = q->tail;
    q->tail = Node;
    q->len++;
    return;
}

/*Am avut nevoie de functie in timpul
implementarii pentru a putea vedea
daca elementele sunt adaugate in coada*/
void printQ(queue *q) {
    node *iter = q->head;
    while (iter){
        printf("'%s'", iter->data);
        iter = iter->next;
    }
    printf("\n");
}


char* pop_queue(queue *q) {
    node *temp = q->head;
    if(temp) {
        char *s = strdup(temp->data);
        q->head = q->head->next;
        free(temp->data);
        free(temp);
        q->len--;
        return s;
    }
    return NULL;
}

void freeq(queue **q){
    node *iter = (*q)->head;
    while (iter) {
        node *temp = iter; 
        iter = iter->next;
        free(temp->data);
        free(temp);
    }
    free(*q);
}

void SWITCH(queue *q) {
    node *prev = NULL;
    node *next = NULL;
    node *current = q->head;
    while(current) {
        next = current->next;
        current->next = prev;
        current->prev = next;
        prev = current;
        current = next;
    }
    node *temp = q->head;
    q->head = q->tail;
    q->tail = temp;
}

#ifndef QUEUE_H
#define QUEUE_H

typedef struct node {
    char *data;
    struct node *next;
    struct node *prev;
} node;

typedef struct queue {
    node *head, *tail;
    int len;
} queue;

node* createnode(char *s);

void add_queue(queue *q, char *s);

void printQ(queue *q);

void initq(queue **q);

char* pop_queue(queue *q);

void freeq(queue **q);

void SWITCH(queue *q);

#endif
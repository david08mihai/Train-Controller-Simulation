#ifndef LISTS_H
#define LISTS_H

typedef struct wagon {
    char symbol;
    struct wagon *next;
    struct wagon *prev;
} wagon;

typedef struct train {
    int len;
    wagon* sentinel;
    wagon* mechanic;
} train;


wagon * generete_car(char s);

void init_train(train **t);

void move_left (train *t);

void move_right (train *t);

void write(train *t, char c);

void clear_cell(train *t);

void clear_all(train *t);

void show(train *t, FILE *f);

void show_current(train *t, FILE *f);

void insert_left(train *t, char c, FILE *f);

void insert_right(train *t, char c);

void search(train *t, char *s, FILE *f);

void search_left(train *t, char *s, FILE *f);

void search_right(train *t, char *s, FILE *f);

void execute(train *t, char *s, FILE *f);

void free_memory(train **t);




#endif
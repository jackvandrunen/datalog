#ifndef DLRESOLVER_H
#define DLRESOLVER_H

#include "dlstack.h"

#define ATOMLEN 32

typedef struct ParMap ParMap;
typedef struct Functor Functor;
typedef struct Variable Variable;
typedef struct Argument Argument;
typedef struct Partial Partial;

struct ParMap {
    int parent;
    int child;
};

struct Functor {
    char name[ATOMLEN];
    int parc;
    char ***facts;
    Partial ***partials;
};

struct Variable {
    char name[ATOMLEN];
    char value[ATOMLEN];
};

struct Argument {
    int free;
    Variable *variable;
};

struct Partial {
    Functor *child;
    Argument *childArgs;
    int mapc;
    ParMap *mapping;
};

int resolve(Functor *func, Argument *args, QueryStack *stack);
int solveConjunction(Partial **partials, Argument *args, QueryStack *stack);
int evaluate(int parc, Argument *args, char **facts);

#endif

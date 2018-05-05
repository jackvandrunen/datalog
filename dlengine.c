#include "dltoken.h"
#include "dlresolver.h"
#include "dlengine.h"
#include <stdlib.h>
#include <string.h>

Functor *getOrAddFunc(Functor ***state, char *predicate, int parc)
{
    int i;
    for (i = 0; (*state)[i] != NULL; i++)
        if (!strcmp((*state)[i]->name, predicate) && (*state)[i]->parc == parc)
            return (*state)[i];
    *state = (Functor **)realloc(*state, sizeof(Functor) * (i + 2));
    (*state)[i] = (Functor *)malloc(sizeof(Functor));
    strcpy((*state)[i]->name, predicate);
    (*state)[i]->parc = parc;
    (*state)[i]->facts = (char ***)calloc(1, sizeof(char **));
    (*state)[i]->partials = (Partial ***)calloc(1, sizeof(Partial **));
    *state[i + 1] = NULL;
    return *state[i];
}

void addFact(Functor *func, char **params)
{
    int i = 0;
    while (func->facts[i] != NULL)
        ++i;
    func->facts = (char ***)realloc(func->facts, sizeof(char **) * (i + 2));
    func->facts[i] = params;
    func->facts[i + 1] = NULL;
}

void executeFact(Functor ***state, Token *statement) {
    Token *predicate = dequeueTQ(&(statement->children));
    char **paramList = unravel(dequeueTQ(&(statement->children)));
    int parc = 0;
    while (paramList[parc] != NULL)
        ++parc;
    Functor *func = getOrAddFunc(state, predicate->value, parc);
    addFact(func, paramList);
    deleteToken(predicate);
}

void executeStatement(Functor ***state, Token *statement)
{
    statement = dequeueTQ(&(statement->children));
    switch (statement->nt)
    {
        case FACT:
            executeFact(state, statement);
            break;
        case RULE:
            executeRule(state, statement);
            break;
        case GOAL:
            executeGoal(state, statement);
            break;
        default:
            break;
    }
}

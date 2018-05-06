#include "dltoken.h"
#include "dlresolver.h"
#include "dlengine.h"
#include <stdlib.h>
#include <string.h>

void flattenTree(TokenQueue *dest, TokenQueue *q)
{
    Token *current = dequeueTQ(q);
    enqueueTQ(dest, current);
    if ((current = dequeueTQ(q)))
    {
        flattenTree(dest, &(current->children));
        deleteToken(current);
    }
}

TokenQueue unravel(Token *t)
{
    TokenQueue result = {NULL, NULL};
    flattenTree(&result, &(t->children));
    deleteToken(t);
    return result;
}

char **factList(TokenQueue *params)
{
    int len = sizeTQ(params);
    char **result = (char **)malloc(sizeof(char *) * (len + 1));
    for (int i = 0; i < len; i++)
    {
        Token *current = dequeueTQ(params);
        result[i] = current->value;
        free(current);  // We want to preserve the allocated string
    }
    result[len] = NULL;
    return result;
}

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

void addFact(Functor *func, TokenQueue *params)
{
    int i = 0;
    while (func->facts[i] != NULL)
        ++i;
    func->facts = (char ***)realloc(func->facts, sizeof(char **) * (i + 2));
    func->facts[i] = factList(params);
    func->facts[i + 1] = NULL;
}

void executeFact(Functor ***state, Token *statement) {
    Token *predicate = dequeueTQ(&(statement->children));
    TokenQueue paramList = unravel(dequeueTQ(&(statement->children)));
    Functor *func = getOrAddFunc(state, predicate->value, sizeTQ(&paramList));
    addFact(func, &paramList);
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

#ifndef DLENGINE_H
#define DLENGINE_H

char **unravel(Token *t);
Functor *getOrAddFunc(Functor ***state, char *predicate, int parc);

void addFact(Functor *func, char **params);
void executeFact(Functor ***state, Token *statement);

void executeRule(Functor ***state, Token *statement);

void executeGoal(Functor ***state, Token *statement);

void executeStatement(Functor ***state, Token *statement);

#endif

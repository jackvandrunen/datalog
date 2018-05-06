#ifndef DLENGINE_H
#define DLENGINE_H

void flattenTree(TokenQueue *dest, TokenQueue *q);
TokenQueue unravel(Token *t);
Functor *getOrAddFunc(Functor ***state, char *predicate, int parc);

void addFact(Functor *func, TokenQueue *params);
void executeFact(Functor ***state, Token *statement);

void executeRule(Functor ***state, Token *statement);

void executeGoal(Functor ***state, Token *statement);

void executeStatement(Functor ***state, Token *statement);

#endif

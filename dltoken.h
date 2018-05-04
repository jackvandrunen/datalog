#ifndef DLTOKEN_H
#define DLTOKEN_H

typedef enum Nonterminal
{
    PROGRAM,
    STATEMENT,
    FACT,
    PARAMLIST,
    RULE,
    HEAD,
    VARLIST,
    BODY,
    PARTIAL,
    ARGLIST,
    ARGUMENT,
    GOAL,
    VARIABLE,
    PREDICATE,
    PARAMETER
} Nonterminal;

typedef struct Token Token;
typedef struct TokenQueueNode TokenQueueNode;
typedef struct TokenQueue TokenQueue;

struct TokenQueueNode
{
    Token *value;
    TokenQueueNode *next;
};

struct TokenQueue
{
    TokenQueueNode *front;
    TokenQueueNode *rear;
};

struct Token
{
    Nonterminal nt;
    char *value;
    TokenQueue children;
};

TokenQueueNode *enqueueTQ(TokenQueue *q, Token *t);
Token *dequeueTQ(TokenQueue *q);
Token *newToken(Nonterminal nt, char *str, int offset, TokenQueue *children);

#endif

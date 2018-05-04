#include "dltoken.h"
#include <stdlib.h>
#include <string.h>

TokenQueueNode *enqueueTQ(TokenQueue *q, Token *t)
{
    TokenQueueNode *result = (TokenQueueNode *)malloc(sizeof(TokenQueueNode));
    result->value = t;
    result->next = NULL;
    if (q->front == NULL)
        q->front = result;
    if (q->rear != NULL)
        q->rear->next = result;
    q->rear = result;
    return result;
}

Token *dequeueTQ(TokenQueue *q)
{
    TokenQueueNode *front;
    Token *result;
    if (q->front == NULL)
        return NULL;
    front = q->front;
    result = front->value;
    q->front = front->next;
    if (q->rear == front)
        q->rear = NULL;
    free(front);
    return result;
}

Token *newToken(Nonterminal nt, char *str, int offset, TokenQueue *children)
{
    Token *result = (Token *)malloc(sizeof(Token));
    char *value = (char *)malloc(sizeof(char) * (offset + 1));
    strncpy(value, str, offset);
    value[offset] = '\0';
    result->nt = nt;
    result->value = value;
    result->children = *children;
    return result;
}

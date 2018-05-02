#ifndef DLSTACK_H
#define DLSTACK_H

typedef struct QueryStack QueryStack;

struct QueryStack {
    int i;
    int atPartials;
    QueryStack *next;
};

QueryStack *newQS();
QueryStack *pushQS(QueryStack *stack);
void popQS(QueryStack *stack);

#define BOTTOM(s) s != NULL && s->next == NULL
#define NEXT(s) s->next

#endif

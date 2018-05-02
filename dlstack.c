#include "dlstack.h"
#include <stdlib.h>

QueryStack *newQS()
{
    QueryStack *result = (QueryStack *)malloc(sizeof(QueryStack));
    result->i = -1;
    result->atPartials = 0;
    result->next = NULL;
    return result;
}

QueryStack *pushQS(QueryStack *stack)
{
    QueryStack *result = newQS();
    if (stack == NULL)
        return result;
    return stack->next = result;
}

void popQS(QueryStack *stack)
{
    if (stack == NULL)
        return;
    if (stack->next == NULL)
        return free(stack);
    if (stack->next->next != NULL)
        popQS(stack->next);
    free(stack->next);
    stack->next = NULL;
}

#include "dlresolver.h"
#include "dlstack.h"
#include <string.h>

int evaluate(int parc, Argument *args, char **facts)
{
    for (int i = 0; i < parc; i++)
        if (args[i].free)
            strcpy(args[i].variable->value, facts[i]);
        else if (strcmp(args[i].variable->value, facts[i]))
            return 0;
    return 1;
}

int solveConjunction(Partial **partials, Argument *args, QueryStack *stack)
{
    Partial *partial = partials[0];
    QueryStack *newStack;
    if (BOTTOM(stack))
    {
        for (int i = 0; i < partial->mapc; i++)
        {
            partial->childArgs[partial->mapping[i].child].free = args[partial->mapping[i].parent].free;
            partial->childArgs[partial->mapping[i].child].variable = args[partial->mapping[i].parent].variable;
        }
        newStack = pushQS(stack);
    }
    else
        newStack = NEXT(stack);
    while (resolve(partial->child, partial->childArgs, newStack))
        if (partials[1] != NULL)
        {
            if (solveConjunction(partials + 1, args, newStack))
                return 1;
        }
        else
            return 1;
    popQS(stack);
    return 0;
}

int resolve(Functor *func, Argument *args, QueryStack *stack)
{
    if (!stack->atPartials)
    {
        for (stack->i++; func->facts[stack->i] != NULL; stack->i++)
            if (evaluate(func->parc, args, func->facts[stack->i]))
                return 1;
        stack->i = 0;
        stack->atPartials = 1;
    }
    if (stack->atPartials)
        for ( ; func->partials[stack->i] != NULL; stack->i++)
            if (solveConjunction(func->partials[stack->i], args, stack))
                return 1;
    return 0;
}

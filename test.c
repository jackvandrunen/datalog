#include "dlresolver.h"
#include "dlstack.h"
#include <stdio.h>
#include <string.h>

int main()
{
    char *gt1[2] = {"bill", "mary"};
    char *gt2[2] = {"mary", "john"};
    char **pgt[3] = {gt1, gt2, NULL};
    Partial **pp[1] = {NULL};
    Functor parent = {"parent", 2, pgt, pp};

    ParMap a1p[2] = {{0, 0}, {1, 1}};
    Argument a1q[2] = {{1, NULL}, {1, NULL}};
    Partial a1 = {&parent, a1q, 2, a1p};

    Variable a2z = {"Z", ""};
    ParMap a21p[1] = {{0, 0}};
    Argument a21q[2] = {{1, NULL}, {1, &a2z}};
    Partial a21 = {&parent, a21q, 1, a21p};

    ParMap a22p[1] = {{1, 1}};
    Argument a22q[2] = {{0, &a2z}, {1, NULL}};
    Partial a22 = {&parent, a22q, 1, a22p};

    char **agt[1] = {NULL};
    Partial *ap1[2] = {&a1, NULL};
    Partial *ap2[3] = {&a21, &a22, NULL};
    Partial **ap[3] = {ap1, ap2, NULL};
    Functor ancestor = {"ancestor", 2, agt, ap};

    Variable ground = {"_", ""};
    Variable child = {"X", ""};
    Argument query[2] = {{0, &ground}, {1, &child}};

    QueryStack *stack;

    printf("parent(bill, mary).\n");
    printf("parent(mary, john).\n");
    printf("\n");
    printf("ancestor(X, Y) :- parent(X, Y).\n");
    printf("ancestor(X, Y) :- parent(X, Z), ancestor(Z, Y).\n");

    strcpy(ground.value, "john");
    printf("\n?- ancestor(%s, X).\n", ground.value);
    stack = newQS();
    if (!resolve(&ancestor, query, stack))
        printf("No\n");
    else do
        printf("%s = %s\n", child.name, child.value);
    while (resolve(&ancestor, query, stack));
    popQS(stack);

    strcpy(ground.value, "mary");
    printf("\n?- ancestor(%s, X).\n", ground.value);
    stack = newQS();
    if (!resolve(&ancestor, query, stack))
        printf("No\n");
    else do
        printf("%s = %s\n", child.name, child.value);
    while (resolve(&ancestor, query, stack));
    popQS(stack);

    strcpy(ground.value, "bill");
    printf("\n?- ancestor(%s, X).\n", ground.value);
    stack = newQS();
    if (!resolve(&ancestor, query, stack))
        printf("No\n");
    else do
        printf("%s = %s\n", child.name, child.value);
    while (resolve(&ancestor, query, stack));
    popQS(stack);

    return 0;
}

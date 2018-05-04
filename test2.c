#include "dltoken.h"
#include "dlparser.h"
#include <stdio.h>

void readStdin(char *buf, int max)
{
    int i;
    int stop = max - 1;
    for (i = 0; i < stop; i++)
        if ((buf[i] = getchar()) == EOF)
            break;
    buf[i] = '\0';
}

void printIndent(int indent)
{
    for (int i = 0; i < indent; i++)
        putchar(' ');
}

void printQueue(TokenQueue *q, int indent)
{
    Token *current;
    while ((current = dequeue(q)))
    {
        printIndent(indent);
        printf("%2d %s\n", current->nt, current->value);
        printQueue(&(current->children), indent + 1);
    }
}

int main()
{
    TokenQueue parsed = {NULL, NULL};
    char program[10240];
    readStdin(program, 10240);
    parseProgram(&parsed, program);
    printQueue(&parsed, 0);
    return 0;
}

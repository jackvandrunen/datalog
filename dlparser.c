#include "dltoken.h"
#include "dlparser.h"
#include <string.h>

int parseEND(char *str)
{
    return !str[0];
}

int parseWHITESPACE(char *str)
{
    return strspn(str, " \t\r\n");
}

int parseSTR(char *str, const char *needle)
{
    int result = strlen(needle);
    if (!strncmp(str, needle, result))
        return result;
    return 0;
}

int parseWSSTR(char *str, const char *needle)
{
    int len = strlen(needle);
    int result = parseWHITESPACE(str);
    if (!strncmp(str + result, needle, len))
    {
        result += len;
        return result + parseWHITESPACE(str + result);
    }
    return 0;
}

int parseProgram(TokenQueue *prevTokens, char *str)
{
    int result, i;
    TokenQueue children;
    if ((result = i = parseStatement(&children, str)))
    {
        if ((result += parseEND(str + i)) != i)
            FOUND(PROGRAM);
        if ((result += parseProgram(&children, str + i)) != i)
            FOUND(PROGRAM);
    }
    return 0;
}

int parseStatement(TokenQueue *prevTokens, char *str)
{
    int result, i;
    TokenQueue children;
    result = i = parseWHITESPACE(str);
    if ((result += parseFact(&children, str + i)) != i)
    {
        result += parseWHITESPACE(str + result);
        FOUND(STATEMENT);
    }
    if ((result += parseRule(&children, str + i)) != i)
    {
        result += parseWHITESPACE(str + result);
        FOUND(STATEMENT);
    }
    if ((result += parseGoal(&children, str + i)) != i)
    {
        result += parseWHITESPACE(str + result);
        FOUND(STATEMENT);
    }
    return 0;
}

int parseFact(TokenQueue *prevTokens, char *str)
{
    int result, i;
    TokenQueue children;
    if ((result = i = parsePredicate(&children, str)))
    {
        i = result += parseWHITESPACE(str + result);
        if ((result += parseSTR(str + i, "(")) != i)
        {
            i = result += parseWHITESPACE(str + result);
            if ((result += parseParamList(&children, str + i)) != i)
            {
                i = result += parseWHITESPACE(str + result);
                if ((result += parseSTR(str + i, ")")) != i)
                {
                    i = result += parseWHITESPACE(str + result);
                    if ((result += parseSTR(str + i, ".")) != i)
                        FOUND(FACT);
                }
            }
        }
    }
    return 0;
}

int parseParamList(TokenQueue *prevTokens, char *str)
{
    int result, i;
    TokenQueue children;
    if ((result = i = parseParameter(&children, str)))
        if ((result += parseWSSTR(str + i, ",")) != i)
        {
            i = result;
            if ((result += parseParamList(&children, str + i)) != i)
                FOUND(PARAMLIST);
        }
    return 0;
}

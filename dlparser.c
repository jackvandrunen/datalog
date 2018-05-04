#include "dltoken.h"
#include "dlparser.h"
#include <string.h>

int parseEND(char *str)
{
    return !str[0];
}

int parseWHITESPACE(char *str)
{
    int result, i;
    result = i = strspn(str, " \t\r\n");
    if ((result += parseComment(str + i)) != i)
        return result + parseWHITESPACE(str + result);
    return result;
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

int parseCHAR(char *str, const char *needle)
{
    int len = strlen(needle);
    for (int i = 0; i < len; i++)
        if (str[0] == needle[i])
            return 1;
    return 0;
}

int parseNCHAR(char *str, const char *needle)
{
    int len = strlen(needle);
    for (int i = 0; i < len; i++)
        if (str[0] == needle[i])
            return 0;
    return 1;
}

int parseProgram(TokenQueue *prevTokens, char *str)
{
    int result, i;
    TokenQueue children = {NULL, NULL};
    if ((result = i = parseStatement(&children, str)))
    {
        if ((result += parseEND(str + i)) != i)
        {
            FOUND(PROGRAM);
        }
        if ((result += parseProgram(&children, str + i)) != i)
        {
            FOUND(PROGRAM);
        }
    }
    return 0;
}

int parseStatement(TokenQueue *prevTokens, char *str)
{
    int result, i;
    TokenQueue children = {NULL, NULL};
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
    TokenQueue children = {NULL, NULL};
    if ((result = i = parsePredicate(&children, str)))
    {
        i = result;
        if ((result += parseWSSTR(str + i, "(")) != i)
        {
            i = result;
            if ((result += parseParamList(&children, str + i)) != i)
            {
                i = result;
                if ((result += parseWSSTR(str + i, ")")) != i)
                {
                    i = result;
                    if ((result += parseWSSTR(str + i, ".")) != i)
                    {
                        FOUND(FACT);
                    }
                }
            }
        }
    }
    return 0;
}

int parseParamList(TokenQueue *prevTokens, char *str)
{
    int result, i;
    TokenQueue children = {NULL, NULL};
    if ((result = i = parseParameter(&children, str)))
    {
        if ((result += parseWSSTR(str + i, ",")) == i)
        {
            FOUND(PARAMLIST);
        }
        else
        {
            i = result;
            if ((result += parseParamList(&children, str + i)) != i)
            {
                FOUND(PARAMLIST);
            }
        }
    }
    return 0;
}

int parseRule(TokenQueue *prevTokens, char *str)
{
    int result, i;
    TokenQueue children = {NULL, NULL};
    if ((result = i = parseHead(&children, str)))
    {
        if ((result += parseWSSTR(str + i, ":-")) != i)
        {
            i = result;
            if ((result += parseBody(&children, str + i)) != i)
            {
                i = result;
                if ((result += parseWSSTR(str + i, ".")) != i)
                {
                    FOUND(RULE);
                }
            }
        }
    }
    return 0;
}

int parseHead(TokenQueue *prevTokens, char *str)
{
    int result, i;
    TokenQueue children = {NULL, NULL};
    if ((result = i = parsePredicate(&children, str)))
    {
        if ((result += parseWSSTR(str + i, "(")) != i)
        {
            i = result;
            if ((result += parseVarList(&children, str + i)) != i)
            {
                i = result;
                if ((result += parseWSSTR(str + i, ")")) != i)
                {
                    FOUND(HEAD);
                }
            }
        }
    }
    return 0;
}

int parseVarList(TokenQueue *prevTokens, char *str)
{
    int result, i;
    TokenQueue children = {NULL, NULL};
    if ((result = i = parseVariable(&children, str)))
    {
        if ((result += parseWSSTR(str + i, ",")) == i)
        {
            FOUND(VARLIST);
        }
        else
        {
            i = result;
            if ((result += parseVarList(&children, str + i)) != i)
            {
                FOUND(VARLIST);
            }
        }
    }
    return 0;
}

int parseBody(TokenQueue *prevTokens, char *str)
{
    int result, i;
    TokenQueue children = {NULL, NULL};
    if ((result = i = parsePartial(&children, str)))
    {
        if ((result += parseWSSTR(str + i, ",")) == i)
        {
            FOUND(BODY);
        }
        else
        {
            i = result;
            if ((result += parseBody(&children, str + i)) != i)
            {
                FOUND(BODY);
            }
        }
    }
    return 0;
}

int parsePartial(TokenQueue *prevTokens, char *str)
{
    int result, i;
    TokenQueue children = {NULL, NULL};
    if ((result = i = parsePredicate(&children, str)))
    {
        if ((result += parseWSSTR(str + i, "(")) != i)
        {
            i = result;
            if ((result += parseArgList(&children, str + i)) != i)
            {
                i = result;
                if ((result += parseWSSTR(str + i, ")")) != i)
                {
                    FOUND(PARTIAL);
                }
            }
        }
    }
    return 0;
}

int parseArgList(TokenQueue *prevTokens, char *str)
{
    int result, i;
    TokenQueue children = {NULL, NULL};
    if ((result = i = parseArgument(&children, str)))
    {
        if ((result += parseWSSTR(str + i, ",")) == i)
        {
            FOUND(ARGLIST);
        }
        else
        {
            i = result;
            if ((result += parseArgList(&children, str + i)) != i)
            {
                FOUND(ARGLIST);
            }
        }
    }
    return 0;
}

int parseArgument(TokenQueue *prevTokens, char *str)
{
    int result, i;
    TokenQueue children = {NULL, NULL};
    if ((result = i = parseParameter(&children, str)))
    {
        FOUND(ARGUMENT);
    }
    if ((result = i = parseVariable(&children, str)))
    {
        FOUND(ARGUMENT);
    }
    return 0;
}

int parseGoal(TokenQueue *prevTokens, char *str)
{
    int result, i;
    TokenQueue children = {NULL, NULL};
    if ((result = i = parseWSSTR(str, "?-")))
    {
        if ((result += parseBody(&children, str + i)) != i)
        {
            i = result;
            if ((result += parseWSSTR(str + i, ".")) != i)
            {
                FOUND(GOAL);
            }
        }
    }
    return 0;
}

int parseVariable(TokenQueue *prevTokens, char *str)
{
    int result;
    TokenQueue children = {NULL, NULL};
    if ((result = parseUidentifier(str)))
    {
        FOUND(VARIABLE);
    }
    return 0;
}

int parseUidentifier(char *str)
{
    int result;
    if ((result = parseUlet(str)))
    {
        result += parseUalnum(str + result);
        return result;
    }
    return 0;
}

int parseUlet(char *str)
{
    return parseCHAR(str, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

int parseUalnum(char *str)
{
    int result = 0;
    while (parseCHAR(str + result, "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"))
        ++result;
    return result;
}

int parsePredicate(TokenQueue *prevTokens, char *str)
{
    int result;
    TokenQueue children = {NULL, NULL};
    if ((result = parseLidentifier(str)))
    {
        FOUND(PREDICATE);
    }
    return 0;
}

int parseParameter(TokenQueue *prevTokens, char *str)
{
    int result;
    TokenQueue children = {NULL, NULL};
    if ((result = parseLidentifier(str)))
    {
        FOUND(PARAMETER);
    }
    return 0;
}

int parseLidentifier(char *str)
{
    int result;
    if ((result = parseLalnum(str)))
        return result;
    if ((result = parseString(str)))
        return result;
    return 0;
}

int parseLalnum(char *str)
{
    int result = 0;
    while (parseCHAR(str + result, "abcdefghijklmnopqrstuvwxyz0123456789_"))
        ++result;
    return result;
}

int parseString(char *str)
{
    int result, i;
    if ((result = i = parseSTR(str, "'")))
    {
        if ((result += parseStringChar(str + i)) != i)
        {
            i = result;
            if ((result += parseSTR(str + i, "'")) != i)
            {
                return result;
            }
        }
    }
    return 0;
}

int parseStringChar(char *str)
{
    int result = 0;
    int i = 0;
    while ((result += parseSafeChar(str + i)) != i)
        i = result;
    return result;
}

int parseSafeChar(char *str)
{
    if (parseNCHAR(str, "\\'"))
        return 1;
    if (parseSTR(str, "\\\\"))
        return 2;
    if (parseSTR(str, "\\'"))
        return 2;
    return 0;
}

int parseComment(char *str)
{
    int result, i;
    if ((result = i = parseSTR(str, "/*")))
    {
        if ((result += parseCommentChar(str + i)) != i)
        {
            i = result;
            if ((result += parseSTR(str + i, "*/")) != i)
            {
                return result;
            }
        }
    }
    return 0;
}

int parseCommentChar(char *str)
{
    int result = 0;
    int i = 0;
    while ((result += parseCChar(str + i)) != i)
        i = result;
    return result;
}

int parseCChar(char *str)
{
    if (str[0] && (parseNCHAR(str, "*") || parseNCHAR(str + 1, "/")))
        return 1;
    return 0;
}

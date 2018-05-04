#ifndef DLPARSER_H
#define DLPARSER_H

#define FOUND(nt) enqueue(prevTokens, newToken(nt, str, result, &children)); return result

int parseEND(char *str);
int parseWHITESPACE(char *str);
int parseCHAR(char *str, const char *needle);
int parseWSSTR(char *str, const char *needle);

int parseProgram(TokenQueue *prevTokens, char *str);
int parseStatement(TokenQueue *prevTokens, char *str);

int parseFact(TokenQueue *prevTokens, char *str);
int parseParamList(TokenQueue *prevTokens, char *str);

int parseRule(TokenQueue *prevTokens, char *str);
int parseHead(TokenQueue *prevTokens, char *str);
int parseVarList(TokenQueue *prevTokens, char *str);
int parseBody(TokenQueue *prevTokens, char *str);
int parsePartial(TokenQueue *prevTokens, char *str);
int parseArgList(TokenQueue *prevTokens, char *str);
int parseArgument(TokenQueue *prevTokens, char *str);

int parseGoal(TokenQueue *prevTokens, char *str);

int parseVariable(TokenQueue *prevTokens, char *str);
int parseUidentifier(TokenQueue *prevTokens, char *str);
int parseUlet(TokenQueue *prevTokens, char *str);
int parseUalnum(TokenQueue *prevTokens, char *str);

int parsePredicate(TokenQueue *prevTokens, char *str);
int parseParameter(TokenQueue *prevTokens, char *str);
int parseLidentifier(TokenQueue *prevTokens, char *str);
int parseLalnum(TokenQueue *prevTokens, char *str);
int parseString(TokenQueue *prevTokens, char *str);
int parseStringChar(TokenQueue *prevTokens, char *str);
int parseSafeChar(TokenQueue *prevTokens, char *str);

#endif

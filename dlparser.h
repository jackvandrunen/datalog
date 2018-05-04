#ifndef DLPARSER_H
#define DLPARSER_H

#define FOUND(nt) enqueueTQ(prevTokens, newToken(nt, str, result, &children)); return result

int parseEND(char *str);
int parseWHITESPACE(char *str);
int parseSTR(char *str, const char *needle);
int parseWSSTR(char *str, const char *needle);
int parseCHAR(char *str, const char *needle);
int parseNCHAR(char *str, const char *needle);

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
int parseUidentifier(char *str);
int parseUlet(char *str);
int parseUalnum(char *str);

int parsePredicate(TokenQueue *prevTokens, char *str);
int parseParameter(TokenQueue *prevTokens, char *str);
int parseLidentifier(char *str);
int parseLalnum(char *str);
int parseString(char *str);
int parseStringChar(char *str);
int parseSafeChar(char *str);

#endif

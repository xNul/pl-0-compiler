#include "lexical_analyzer.h"

void deleteLexerOut(LexerOut* lexerOut)
{
    deleteTokenList(&lexerOut->tokenList);
}
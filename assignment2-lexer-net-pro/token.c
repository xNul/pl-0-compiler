#include "token.h"
#include <stdio.h>
#include <stdlib.h>

void initTokenList(TokenList* tokenList)
{
    tokenList->tokens = NULL;
    tokenList->numberOfTokens = 0;
}

void addToken(TokenList* tokenList, Token token)
{
    // Increase number of tokens
    tokenList->numberOfTokens++;

    // Allocate space for new token
    tokenList->tokens = (Token*)realloc(tokenList->tokens, (tokenList->numberOfTokens) * sizeof(Token));

    // Add token to the end of the list
    tokenList->tokens[tokenList->numberOfTokens - 1] = token;
}

TokenList getCopy(TokenList src)
{
    TokenList copy;
    
    copy.numberOfTokens = src.numberOfTokens;

    if(src.tokens)
    {
        copy.tokens = (Token*)malloc(src.numberOfTokens * sizeof(Token));

        for(int i = 0; i < src.numberOfTokens; i++)
            copy.tokens[i] = src.tokens[i];
    }

    return copy;
}

void printTokenList(TokenList tokenList, FILE* out)
{
    if(out == NULL || tokenList.tokens == NULL)
        return;

    fprintf(out, "%10s   %12s\n", "Token Type", "Lexeme");

    for(int i = 0; i < tokenList.numberOfTokens; i++)
    {
        fprintf(out, "%10d   %12s\n", tokenList.tokens[i].id, tokenList.tokens[i].lexeme);
    }
}

void deleteTokenList(TokenList* tokenList)
{
    if(tokenList->tokens)
        free(tokenList->tokens);

    tokenList->tokens = NULL;
}
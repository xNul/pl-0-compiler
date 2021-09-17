#ifndef __TOKEN_H__
#define __TOKEN_H__

#include <stdio.h>

#define MAX_LEXEME_LENGTH 11

/**
 * The struct to store token information
 * */
typedef struct {
    int id; // numerical representation of the token
    char lexeme[MAX_LEXEME_LENGTH + 1]; // null terminated string
} Token;

/**
 * The struct to store list of tokens and keep track
 * of number of tokens included in the list
 * */
typedef struct {
    Token* tokens;
    int numberOfTokens;
} TokenList;

/**
 * Initializes the given TokenList
 * */
void initTokenList(TokenList*);

/**
 * Adds the given Token to the given TokenList
 * */
void addToken(TokenList*, Token);

/**
 * Creates and returns a copy of the given TokenList.
 * TokenList dynamically allocates memory for its list.
 * Therefore, shallow copying with assignment operator does not
 * .. guarantee any lifetime of the included tokens list, which
 * .. may cause dangling pointers.
 * */
TokenList getCopy(TokenList);

/**
 * Writes the given TokenList to the given FILE
 * */
void printTokenList(TokenList, FILE*);

/**
 * Makes the necessary deallocations on the TokenList
 * */
void deleteTokenList(TokenList*);

#endif
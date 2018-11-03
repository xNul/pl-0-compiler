#include "lexical_analyzer.h"
#include "data.h"
#include "token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Declares isalpa, isdigit, isalnum

/* ************************************************************************** */
/* Enumarations, Typename Aliases, Helpers Structs ************************** */
/* ************************************************************************** */

typedef enum {
    ALPHA,   // a, b, .. , z, A, B, .. Z
    DIGIT, // 0, 1, .. , 9
    SPECIAL, // '>', '=', , .. , ';', ':'
    INVALID  // Invalid symbol
} SymbolType;

/**
 * Following struct is recommended to use to keep track of the current state
 * .. of the lexer, and modify the state in other functions by passing pointer
 * .. to the state as argument.
 * */
typedef struct {
    int lineNum;         // the line number currently being processed
    int charInd;         // the index of the character currently being processed
    char* sourceCode;    // null-terminated source code string
    LexErr lexerError;   // LexErr to be filled when Lexer faces an error
    TokenList tokenList; // list of tokens
} LexerState;

/* ************************************************************************** */
/* Declarations ************************************************************* */
/* ************************************************************************** */

/**
 * Initializes the LexerState with the given null-terminated source code string.
 * Sets the other fields of the LexerState to their inital values.
 * Shallow copying is done for the source code field.
 * */
void initLexerState(LexerState*, char* sourceCode);

/**
 * Returns 1 if the given character is valid.
 * Returns 0 otherwise.
 * */
int isCharacterValid(char);

/**
 * Returns 1 if the given character is one of the special symbols of PL/0,
 * .. such as '/', '=', ':' or ';'.
 * Returns 0 otherwise.
 * */
int isSpecialSymbol(char);

/**
 * Returns the symbol type of the given character.
 * */
SymbolType getSymbolType(char);

/**
 * Checks if the given symbol is one of the reserved token.
 * If yes, returns the numerical value assigned to the corresponding token.
 * If not, returns -1.
 * For example, calling the function with symbol "const" returns 28.
 * */
int checkReservedTokens(char* symbol);

/**
 * Deterministic-finite-automaton to be entered when an alpha character is seen.
 * Simulating a state machine, consumes the source code and changes the state
 * .. of the lexer (LexerState) as required. Possibly, adds new tokens to the
 * .. token list field of the LexerState.
 * If an error is encountered, sets the LexErr field of LexerState, sets the
 * .. line number field and returns.
 * */
void DFA_Alpha(LexerState*);

/**
 * Deterministic-finite-automaton to be entered when a digit character is seen.
 * Simulating a state machine, consumes the source code and changes the state
 * .. of the lexer (LexerState) as required. Possibly, adds new tokens to the
 * .. token list field of the LexerState.
 * If an error is encountered, sets the LexErr field of LexerState, sets the
 * .. line number field and returns.
 * */
void DFA_Digit(LexerState*);

/**
 * Deterministic-finite-automaton to be entered when a special character is seen.
 * Simulating a state machine, consumes the source code and changes the state
 * .. of the lexer (LexerState) as required. Possibly, adds new tokens to the
 * .. token list field of the LexerState.
 * If an error is encountered, sets the LexErr field of LexerState, sets the
 * .. line number field and returns.
 * */
void DFA_Special(LexerState*);

/// Consumes the current identifier in the lexer state and returns a string of that identifier.
char* ConsumeIdentifier(LexerState* lexerState);


/* ************************************************************************** */
/* Definitions ************************************************************** */
/* ************************************************************************** */

void initLexerState(LexerState* lexerState, char* sourceCode)
{
    lexerState->lineNum = 0;
    lexerState->charInd = 0;
    lexerState->sourceCode = sourceCode;
    lexerState->lexerError = NONE;
    
    initTokenList(&lexerState->tokenList);
}

int isCharacterValid(char c)
{
    return isalnum(c) || isspace(c) || isSpecialSymbol(c);
}

int isSpecialSymbol(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' ||
           c == '(' || c == ')' || c == '=' || c == ',' ||
           c == '.' || c == '<' || c == '>' || c == ';' ||
           c == ':';
}

SymbolType getSymbolType(char c)
{
         if(isalpha(c))         return ALPHA;
    else if(isdigit(c))         return DIGIT;
    else if(isSpecialSymbol(c)) return SPECIAL;
    else                        return INVALID;
}

int checkReservedTokens(char* symbol)
{
    for(int i = firstReservedToken; i <= lastReservedToken; i++)
    {
        if( !strcmp(symbol, tokens[i]) )
        {
            // Symbol is the reserved token at index i.
            return i;
        }
    }

    // Symbol is not found among the reserved tokens
    return -1;
}


/**
 * Deterministic-finite-automaton to be entered when an alpha character is seen.
 * Simulating a state machine, consumes the source code and changes the state
 * .. of the lexer (LexerState) as required. Possibly, adds new tokens to the
 * .. token list field of the LexerState.
 * If an error is encountered, sets the LexErr field of LexerState, sets the
 * .. line number field and returns.
 * */
void DFA_Alpha(LexerState* lexerState)
{
    // There are two possible cases for symbols starting with alpha:
    // Case.1) A reversed token (a reserved word or 'odd')
    // Case.2) An ident

    char lexeme[MAX_IDENTIFIER_LENGTH+1];
    int i = 0;
    
    // In both cases, symbol should not exceed 11 characters.
    // Read 11 or less alpha-numeric characters
    
    for (i; (i < MAX_IDENTIFIER_LENGTH) && isalnum(lexerState->sourceCode[lexerState->charInd]); i++)
    {
        lexeme[i] = lexerState->sourceCode[lexerState->charInd];
        lexeme[i+1] = '\0';
        
        lexerState->charInd++;
    }
    
    // If it exceeds 11 alnums, fill LexerState error and return
    
    if ((i == MAX_IDENTIFIER_LENGTH) && isalnum(lexerState->sourceCode[lexerState->charInd]))
    {
        lexerState->lexerError = NAME_TOO_LONG;
        return;
    }
    
    // Otherwise, try to recognize if the symbol is reserved.
    //   If yes, tokenize by one of the reserved symbols
    //   If not, tokenize as ident.
    
    Token token;
    
    if (strcmp(tokens[oddsym], lexeme) == 0)
    {
        token.id = oddsym;
    }
    else
    {
      for (i=beginsym; i < elsesym+1; i++)
      {
          if (strcmp(tokens[i], lexeme) == 0)
          {
              token.id = i;
              break;
          }
      }
      
      if (i == elsesym+1)
          token.id = identsym;
    }
    
    // For adding a token to tokenlist, you could create a token, fill its 
    // .. fields as required and use the following call:
    // addToken(&lexerState->tokenList, token);
    
    strcpy(token.lexeme, lexeme);
    addToken(&lexerState->tokenList, token);

    return;
}


/**
 * Deterministic-finite-automaton to be entered when a digit character is seen.
 * Simulating a state machine, consumes the source code and changes the state
 * .. of the lexer (LexerState) as required. Possibly, adds new tokens to the
 * .. token list field of the LexerState.
 * If an error is encountered, sets the LexErr field of LexerState, sets the
 * .. line number field and returns.
 * */
void DFA_Digit(LexerState* lexerState)
{
    // There are three cases for symbols starting with number:
    // Case.1) It is a well-formed number
    // Case.2) It is an ill-formed number exceeding 5 digits - Lexer Error!
    // Case.3) It is an ill-formed variable name starting with digit - Lexer Error!

    char lexeme[MAX_NUM_DIGIT_LENGTH+1];
    int i = 0;
    
    for (i; (i < MAX_NUM_DIGIT_LENGTH) && isdigit(lexerState->sourceCode[lexerState->charInd]); i++)
    {
        lexeme[i] = lexerState->sourceCode[lexerState->charInd];
        lexeme[i+1] = '\0';
        
        lexerState->charInd++;
    }
    
    // Tokenize as numbersym only if it is case 1. Otherwise, set the required
    // .. fields of lexerState to corresponding LexErr and return.
    
    if ((i == MAX_NUM_DIGIT_LENGTH) && isdigit(lexerState->sourceCode[lexerState->charInd]))
    {
        lexerState->lexerError = NUM_TOO_LONG;
        return;
    }
    
    if (isalpha(lexerState->sourceCode[lexerState->charInd]))
    {
        lexerState->lexerError = NONLETTER_VAR_INITIAL;
        return;
    }

    // For adding a token to tokenlist, you could create a token, fill its 
    // .. fields as required and use the following call:
    // addToken(&lexerState->tokenList, token);
    
    Token token;
    token.id = numbersym;
    strcpy(token.lexeme, lexeme);
    addToken(&lexerState->tokenList, token);

    return;
}

void DFA_Special(LexerState* lexerState)
{
	char* currentIdentifier = ConsumeIdentifier(lexerState);

	// There are three cases for symbols starting with special:
	// Case.1: Beginning of a comment: "/*"
	// Case.2: Two character special symbol: "<>", "<=", ">=", ":="
	// Case.3: One character special symbol: "+", "-", "(", etc.

	// For case.1, you are recommended to consume all the characters regarding
	// .. the comment, and return. This way, lexicalAnalyzer() func can decide
	// .. what to do with the next character.
	if (strstr(currentIdentifier, "/*") != NULL)
	{
		int len = strlen(lexerState->sourceCode);
		// Iterate through the source code until we find the */ or reach EOF
		while (lexerState->charInd != len - 1)
		{
			// If we see the end of the comment, iterate once more and then break.
			if (lexerState->sourceCode[lexerState->charInd - 1] == '*' && lexerState->sourceCode[lexerState->charInd] == '/')
			{
				lexerState->charInd++;
				break;

			}
			else
			{
				lexerState->charInd++;
			}

		}
		return;
	}
	else
	{
		// For case.2 and case.3, you could consume the characters, add the 
		// .. corresponding token to the tokenlist of lexerState, and return.

		// Iterate through tokens to find the one we're holding in currentIdentifier
		int currentToken = 1;
		while (currentToken < lastReservedToken)
		{
			if (tokens[currentToken] != NULL && strcmp(tokens[currentToken], currentIdentifier) == 0)
			{
				break;
			}
			currentToken++;
		}
		Token token;
		token.id = currentToken;
		strcpy(token.lexeme, tokens[currentToken]);

		// Add the token to the lexer state
		addToken(&lexerState->tokenList, token);
	}
    return;
}

/// Takes the identifier currently being pointed to and returns it as a char*. Note that this method will advance the lexerState->charIndex.
char* ConsumeIdentifier(LexerState* lexerState)
{
	// Current evaluation
	char* characters = calloc(1, sizeof(char) * 1);
	// Consume until we reach a non ' ' char
	while (lexerState->sourceCode[lexerState->charInd] == ' ')
	{
		lexerState->charInd++;
	}
	// Before we filter out semicolons, check if it's the first item being checked.
	if (lexerState->sourceCode[lexerState->charInd] == ';')
	{
		lexerState->charInd++;
		return ";";
	}
  // Before we filter out commas, check if it's the first item being checked.
	if (lexerState->sourceCode[lexerState->charInd] == ',')
	{
		lexerState->charInd++;
		return ",";
	}
  // Before we filter out periods, check if it's the first item being checked.
	if (lexerState->sourceCode[lexerState->charInd] == '.')
	{
		lexerState->charInd++;
		return ".";
	}
	// While we see characters that are non ' ', '\n', '\0'
	while (lexerState->sourceCode[lexerState->charInd] != ' ' &&
		lexerState->sourceCode[lexerState->charInd] != '\0' &&
		lexerState->sourceCode[lexerState->charInd] != '\n' &&
		lexerState->sourceCode[lexerState->charInd] != '\r' &&
		// If we see a semicolon, it's valid syntax even if it's attached to the identifier. We must skip it and catch it in the symbol method.
		lexerState->sourceCode[lexerState->charInd] != ';' &&
		lexerState->sourceCode[lexerState->charInd] != ',' &&
    lexerState->sourceCode[lexerState->charInd] != '.')
	{
		int len = strlen(characters);
		characters = realloc(characters, (len + 1) * sizeof(char));
		characters[len] = lexerState->sourceCode[lexerState->charInd];
		characters[len + 1] = '\0';

		lexerState->charInd++;
	}

	return characters;
}

LexerOut lexicalAnalyzer(char* sourceCode)
{
    if(!sourceCode)
    {
        fprintf(stderr, "ERROR: Null source code string passed to lexicalAnalyzer()\n");
        
        LexerOut lexerOut;
        lexerOut.lexerError = NO_SOURCE_CODE;
        lexerOut.errorLine = -1;

        return lexerOut;
    }

    // Create & init lexer state
    LexerState lexerState;
    initLexerState(&lexerState, sourceCode);

    // While not end of file, and, there is no lexer error
    // .. continue lexing
    while( lexerState.sourceCode[lexerState.charInd] != '\0' &&
        lexerState.lexerError == NONE )
    {
        char currentSymbol = lexerState.sourceCode[lexerState.charInd];

        // Skip spaces or new lines until an effective character is seen
        while(currentSymbol == ' ' || currentSymbol == '\n' || currentSymbol == '\r')
        {
            // Advance line number if required
            if(currentSymbol == '\n')
                lexerState.lineNum++;

            // Advance to the following character
            currentSymbol = lexerState.sourceCode[++lexerState.charInd];
        }

        // After recognizing spaces or new lines, make sure that the EOF was
        // .. not reached. If it was, break the loop.
        if(lexerState.sourceCode[lexerState.charInd] == '\0')
        {
            break;
        }

        // Take action depending on the current symbol's type
        switch(getSymbolType(currentSymbol))
        {
            case ALPHA:
                DFA_Alpha(&lexerState);
                break;
            case DIGIT:
                DFA_Digit(&lexerState);
                break;
            case SPECIAL:
                DFA_Special(&lexerState);
                break;
            case INVALID:
                lexerState.lexerError = INV_SYM;
                break;
        }
    }

    // Prepare LexerOut to be returned
    LexerOut lexerOut;

    if(lexerState.lexerError != NONE)
    {
        // Set LexErr
        lexerOut.lexerError = lexerState.lexerError;

        // Set the number of line the error encountered
        lexerOut.errorLine = lexerState.lineNum;

        lexerOut.tokenList = lexerState.tokenList;
    }
    else
    {
        // No error!
        lexerOut.lexerError = NONE;
        lexerOut.errorLine = -1;

        // Copy the token list

        // The scope of LexerState ends here. The ownership of the tokenlist
        // .. is being passed to LexerOut. Therefore, neither deletion of the
        // .. tokenlist nor deep copying of the tokenlist is required.
        lexerOut.tokenList = lexerState.tokenList;
    }

    return lexerOut;
}
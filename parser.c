#include "token.h"
#include "data.h"
#include "symbol.h"
#include <string.h>
#include <stdlib.h>

/**
 * This pointer is set when by parser() func and used by printParsedToken() func.
 * 
 * You are not required to use it anywhere. The implemented part of the skeleton
 * handles the printing. Instead, You could use the supplied helper functions to
 * manipulate the output file.
 * */
FILE* _out;

/**
 * Token list iterator used by the parser. It will be set once entered to parser()
 * and reset before exiting parser().
 * 
 * It is better to use the given helper functions to make use of token list iterator.
 * */
TokenListIterator _token_list_it;

/**
 * Current level.
 * */
unsigned int currentLevel;

/**
 * Symbol table.
 * */
SymbolTable symbolTable;

/**
 * Returns the current token using the token list iterator.
 * If it is the end of tokens, returns token with id nulsym.
 * */
Token getCurrentToken();

/**
 * Returns the type of the current token. Returns nulsym if it is the end of tokens.
 * */
int getCurrentTokenType();

/**
 * Prints the given token on _out by applying required formatting.
 * */
void printCurrentToken();

/**
 * Advances the position of TokenListIterator by incrementing the current token
 * index by one.
 * */
void nextToken();

/**
 * Given an entry from non-terminal enumaration, prints it.
 * */
void printNonTerminal(NonTerminal nonTerminal);

/**
 * Functions used for non-terminals of the grammar
 * */
int program();
int block();
int const_declaration();
int var_declaration();
int proc_declaration();
int statement();
int condition();
int relop();
int expression();
int term();
int factor();

Token getCurrentToken()
{
    return getCurrentTokenFromIterator(_token_list_it);
}

int getCurrentTokenType()
{
    return getCurrentToken().id;
}

void printCurrentToken()
{
    fprintf(_out, "%8s <%s, '%s'>\n", "TOKEN  :", tokenNames[getCurrentToken().id], getCurrentToken().lexeme);
}

void nextToken()
{
    _token_list_it.currentTokenInd++;
}

void printNonTerminal(NonTerminal nonTerminal)
{
    fprintf(_out, "%8s %s\n", "NONTERM:", nonTerminalNames[nonTerminal]);
}

/**
 * Given the parser error code, prints error message on file by applying
 * required formatting.
 * */
void printParserErr(int errCode, FILE* fp)
{
    if(!fp) return;

    if(!errCode)
        fprintf(fp, "\nPARSING WAS SUCCESSFUL.\n");
    else
        fprintf(fp, "\nPARSING ERROR[%d]: %s.\n", errCode, parserErrorMsg[errCode]);
}

/**
 * Advertised parser function. Given token list, which is possibly the output of 
 * the lexer, parses the tokens. If encountered, return the error code.
 * 
 * Returning 0 signals successful parsing.
 * Otherwise, returns a non-zero parser error code.
 * */
int parser(TokenList tokenList, FILE* out)
{
    // Set output file pointer
    _out = out;

    /**
     * Create a token list iterator, which helps to keep track of the current
     * token being parsed.
     * */
    _token_list_it = getTokenListIterator(&tokenList);

    // Initialize current level to 0, which is the global level
    currentLevel = 0;

    // Initialize symbol table
    initSymbolTable(&symbolTable);

    // Write parsing history header
    fprintf(_out, "Parsing History\n===============\n");

    // Start parsing by parsing program as the grammar suggests.
    int err = program();

    // Print symbol table - if no error occured
    if(!err)
    {
        fprintf(_out, "\n\n");
        printSymbolTable(&symbolTable, _out);
    }

    // Reset output file pointer
    _out = NULL;

    // Reset the global TokenListIterator
    _token_list_it.currentTokenInd = 0;
    _token_list_it.tokenList = NULL;

    // Delete symbol table
    deleteSymbolTable(&symbolTable);

    // Return err code - which is 0 if parsing was successful
    return err;
}

int program()
{
    printNonTerminal(PROGRAM);

	int err = block();
	if (err) return err;

	if (getCurrentTokenType() != periodsym)
	{
		/*
			Expected a period.
			Return error.
		*/

		return 6;
	}

    return 0;
}

int block()
{
    printNonTerminal(BLOCK);
	if (getCurrentTokenType() == constsym)
	{
		int err = const_declaration();
		if (err) return err;
	}
	if (getCurrentTokenType() == varsym)
	{
			int err = var_declaration();
			if (err) return err;

	}
	while (getCurrentTokenType() == procsym)
	{

		int err = proc_declaration();
		if (err) return err;
	}

	// Check statement() for errors after running
	int err = statement();
	if (err) return err;

	return 0;
}

int const_declaration()
{
    printNonTerminal(CONST_DECLARATION);

	printCurrentToken(); // Printing the token is essential!
	nextToken(); // Go to the next token..

	if (getCurrentTokenType() != identsym)
	{
		//Error, Expected identifier
		return 3;
	}
	printCurrentToken(); // Printing the token is essential!
	nextToken(); // Go to the next token..

	if (getCurrentTokenType() != eqsym)
	{
		// error, identifier must be followed by =
		return 2;
	}

	printCurrentToken(); // Printing the token is essential!
	nextToken(); // Go to the next token..

	if (getCurrentTokenType() != numbersym)
	{
		// error, = must be followed by a number
		return 1;
	}

	printCurrentToken(); // Printing the token is essential!
	nextToken(); // Go to the next token..

	while (getCurrentTokenType() == commasym)
	{
		printCurrentToken(); // Printing the token is essential!
		nextToken(); // Go to the next token..

		if (getCurrentTokenType() != identsym)
		{
			// error expected identifier
			return 3;
		}

		printCurrentToken(); // Printing the token is essential!
		nextToken(); // Go to the next token..

		if (getCurrentTokenType() != eqsym)
		{
			// identifier must be followed by an = sign
			return 2;
		}

		printCurrentToken(); // Printing the token is essential!
		nextToken(); // Go to the next token..

		if (getCurrentTokenType() != numbersym)
		{
			// Error, = must be followed by a number
			return 1;
		}

		printCurrentToken(); // Printing the token is essential!
		nextToken(); // Go to the next token..
	}
	
	if (getCurrentTokenType() != semicolonsym)
	{
		// Error, semicolon or comma expected
		return 4;
	}
		

	printCurrentToken(); // Printing the token is essential!
	nextToken(); // Go to the next token..

    // Successful parsing.
    return 0;
}

// Semi implemented? This does not look used.
int var_declaration()
{
    printNonTerminal(VAR_DECLARATION);

	// GET TOKEN
	printCurrentToken(); // Printing the token is essential!
	nextToken(); // Go to the next token..

	if (getCurrentTokenType() != identsym)
	{
		// Error, expected identifier after const
		return 3;
	}

	// GET TOKEN
	printCurrentToken(); // Printing the token is essential!
	nextToken(); // Go to the next token..
	
	while (getCurrentTokenType() == commasym)
	{
		// GET TOKEN
		printCurrentToken(); // Printing the token is essential!
		nextToken(); // Go to the next token..

		if (getCurrentTokenType() != identsym)
		{
			// Expected identifier after comma
			return 3;
		}

		// GET TOKEN
		printCurrentToken(); // Printing the token is essential!
		nextToken(); // Go to the next token..
	}
	
	if (getCurrentTokenType() != semicolonsym)
	{
		// Error, expected semicolon or comma after identifier
		return 4;
	}
	// GET TOKEN
	printCurrentToken(); // Printing the token is essential!
	nextToken(); // Go to the next token..


    return 0;
}

int proc_declaration()
{
    printNonTerminal(PROC_DECLARATION);

	//Get Token
	printCurrentToken(); // Printing the token is essential!
	nextToken(); // Go to the next token..

	if (getCurrentTokenType() != identsym)
	{
		// Error, expected identifier after const, sym etc
		return 3;
	}

	// GET TOKEN
	printCurrentToken(); // Printing the token is essential!
	nextToken(); // Go to the next token..

	if (getCurrentTokenType() != semicolonsym)
	{
		// Expected semicolon after identifier
		return 5;
	}

	// GET TOKEN
	printCurrentToken(); // Printing the token is essential!
	nextToken(); // Go to the next token..

	// run function and check error
	int err = block();
	if (err) return err;

	if (getCurrentTokenType() != semicolonsym)
	{
		// Expected a semicolon or comma
		return 4;
	}

	// GET TOKEN
	printCurrentToken(); // Printing the token is essential!
	nextToken(); // Go to the next token..


    return 0;
}

int statement()
{
    printNonTerminal(STATEMENT);

	if (getCurrentTokenType() == identsym)
	{
		printCurrentToken(); // Printing the token is essential!
		nextToken(); // Go to the next token..
		if (getCurrentTokenType() != becomessym)
		{
			// We expected a becomessym
			// Assignment operator expected
			return 7;
		}
		printCurrentToken(); // Printing the token is essential!
		nextToken(); // Go to the next token..

		// Check for error in expression
		int err = expression();
		if (err) return err;
	}
	else if (getCurrentTokenType() == callsym)
	{
		printCurrentToken(); // Printing the token is essential!
		nextToken(); // Go to the next token..
		if (getCurrentTokenType() != identsym)
		{
			// We expected identsym
			// Expected identifier
			return 3;
		}
		printCurrentToken(); // Printing the token is essential!
		nextToken(); // Go to the next token..
	}
	else if (getCurrentTokenType() == beginsym)
	{
		printCurrentToken(); // Printing the token is essential!
		nextToken(); // Go to the next token..

		// Check for error in statement
		int err = statement();
		if (err) return err;

		while (getCurrentTokenType() == semicolonsym)
		{
			printCurrentToken(); // Printing the token is essential!
			nextToken(); // Go to the next token..

			int err = statement();
			if (err) return err;
		}
		if (getCurrentTokenType() != endsym) 
		{
			// Semicolon or } expected
			return 10;
		}

		printCurrentToken(); // Printing the token is essential!
		nextToken(); // Go to the next token..

	}
	else if (getCurrentTokenType() == ifsym)
	{
		printCurrentToken(); // Printing the token is essential!
		nextToken(); // Go to the next token..

		int err = condition();
		if (err) return err;

		if (getCurrentTokenType() != thensym)
		{
			// then expected
			return 9;
		}

		printCurrentToken(); // Printing the token is essential!
		nextToken(); // Go to the next token..
		
		err = statement();
		if (err) return err;
	}
	else if (getCurrentTokenType() == whilesym)
	{
		printCurrentToken(); // Printing the token is essential!
		nextToken(); // Go to the next token..

		int err = condition();
		if (err) return err;

		if (getCurrentTokenType != dosym)
		{
			// Expected do
			return 11;
		}
		printCurrentToken(); // Printing the token is essential!
		nextToken(); // Go to the next token..

		err = statement();
		if (err) return err;
	}

    return 0;
}

int condition()
{
    printNonTerminal(CONDITION);

	if (getCurrentTokenType() == oddsym)
	{
		printCurrentToken(); // Print the token
		nextToken(); // Go to next token

		// Check error
		int err = expression();
		if (err) return err;
	}
	else
	{
		int err = expression();
		if (err) return err;

		if (getCurrentTokenType() != relop())
		{
			// relational operator expected
			return 12;
		}

		printCurrentToken(); // Print the token
		nextToken(); // Go to next token

		// Parse expression again, returning error if immediate error
		err = expression();
		if (err) return err;
	}
	// Success
    return 0;
}

int relop()
{
    printNonTerminal(REL_OP);

    /*
		Possible cases are =, !=, <, <=, >, >=
	*/
	if (getCurrentTokenType() == eqsym)
	{
		printCurrentToken(); // Print the token
		nextToken(); // Go to next token

		// Success
		return 0;
	}
	else if (getCurrentTokenType() == neqsym)
	{
		printCurrentToken(); // Print the token
		nextToken(); // Go to next token
		
		// Success
		return 0;
	}
	else if (getCurrentTokenType() == lessym)
	{
		printCurrentToken(); // Print the token
		nextToken(); // Go to next token

		// Success
		return 0;
	}
	else if (getCurrentTokenType() == leqsym)
	{
		printCurrentToken(); // Print the token
		nextToken(); // Go to next token

		// Success
		return 0;
	}
	else if (getCurrentTokenType() == gtrsym)
	{
		printCurrentToken(); // Print the token
		nextToken(); // Go to next token

		// Success
		return 0;
	}
	else if (getCurrentTokenType() == geqsym)
	{
		printCurrentToken(); // Print the token
		nextToken(); // Go to next token

		// Success
		return 0;
	}
	else
	{
		/*
			A relational operator was expected
		*/
		return 12;
	}
}

int expression()
{
    printNonTerminal(EXPRESSION);

	if (getCurrentTokenType() == plussym || getCurrentTokenType() == minussym)
	{
		printCurrentToken(); // Print the token
		nextToken(); // Go to next token
	}
	// Get term error code
	int err = term();

	// If there was an error, return immediately
	if (err) return err;

	while (getCurrentTokenType() == plussym || getCurrentTokenType() == minussym)
	{
		printCurrentToken(); // Print the token
		nextToken(); // Go to next token

		// Get next term and check for error
		err = term();
		if (err) return err;
	}

    return 0;
}

int term()
{
    printNonTerminal(TERM);

	// Run the factor function
	int err = factor();
	if (err) return err;
	/*
		While current type is multsym or slashsym	
	*/
	while (getCurrentTokenType() == multsym || getCurrentTokenType() == slashsym)
	{
		printCurrentToken(); // Print the token
		nextToken(); // Go to next token

		// Get the code from factor. If error, return the error
		err = factor();
		if (err) return err;
	}
	// Success returns 0
    return 0;
}

/**
 * The below function is left fully-implemented as a hint.
 * */
int factor()
{
    printNonTerminal(FACTOR);

    /**
     * There are three possibilities for factor:
     * 1) ident
     * 2) number
     * 3) '(' expression ')'
     * */

    // Is the current token a identsym?
    if(getCurrentTokenType() == identsym)
    {
        // Consume identsym
        printCurrentToken(); // Printing the token is essential!
        nextToken(); // Go to the next token..

        // Success
        return 0;
    }
    // Is that a numbersym?
    else if(getCurrentTokenType() == numbersym)
    {
        // Consume numbersym
        printCurrentToken(); // Printing the token is essential!
        nextToken(); // Go to the next token..

        // Success
        return 0;
    }
    // Is that a lparentsym?
    else if(getCurrentTokenType() == lparentsym)
    {
        // Consume lparentsym
        printCurrentToken(); // Printing the token is essential!
        nextToken(); // Go to the next token..

        // Continue by parsing expression.
        int err = expression();

        /**
         * If parsing of expression was not successful, immediately stop parsing
         * and propagate the same error code by returning it.
         * */
        
        if(err) return err;

        // After expression, right-parenthesis should come
        if(getCurrentTokenType() != rparentsym)
        {
            /**
             * Error code 13: Right parenthesis missing.
             * Stop parsing and return error code 13.
             * */
            return 13;
        }

        // It was a rparentsym. Consume rparentsym.
        printCurrentToken(); // Printing the token is essential!
        nextToken(); // Go to the next token..
    }
    else
    {
        /**
          * Error code 24: The preceding factor cannot begin with this symbol.
          * Stop parsing and return error code 24.
          * */
        return 14;
    }

    return 0;
}

#include "token.h"
#include "data.h"
#include "symbol.h"
#include <string.h>
#include <stdlib.h>

/**
 * This pointer is set when by codeGenerator() func and used by printEmittedCode() func.
 * 
 * You are not required to use it anywhere. The implemented part of the skeleton
 * handles the printing. Instead, you are required to fill the vmCode properly by making
 * use of emit() func.
 * */
FILE* _out;

/**
 * Token list iterator used by the code generator. It will be set once entered to
 * codeGenerator() and reset before exiting codeGenerator().
 * 
 * It is better to use the given helper functions to make use of token list iterator.
 * */
TokenListIterator _token_list_it;

/**
 * Current level. Use this to keep track of the current level for the symbol table entries.
 * */
unsigned int currentLevel;

/**
 * Current scope. Use this to keep track of the current scope for the symbol table entries.
 * NULL means global scope.
 * */
Symbol* currentScope;

/**
 * Symbol table.
 * */
SymbolTable symbolTable;

/**
 * The array of instructions that the generated(emitted) code will be held.
 * */
Instruction vmCode[MAX_CODE_LENGTH];

/**
 * The next index in the array of instructions (vmCode) to be filled.
 * */
int nextCodeIndex;

/**
 * The id of the register currently being used.
 * */
int currentReg;

/**
 * Emits the instruction whose fields are given as parameters.
 * Internally, writes the instruction to vmCode[nextCodeIndex] and returns the
 * nextCodeIndex by post-incrementing it.
 * If MAX_CODE_LENGTH is reached, prints an error message on stderr and exits.
 * */
int emit(int OP, int R, int L, int M);

/**
 * Prints the emitted code array (vmCode) to output file.
 * 
 * This func is called in the given codeGenerator() function. You are not required
 * to have another call to this function in your code.
 * */
void printEmittedCodes();

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
 * Advances the position of TokenListIterator by incrementing the current token
 * index by one.
 * */
void nextToken();

/**
 * Functions used for non-terminals of the grammar
 * 
 * rel-op func is removed on purpose. For code generation, it is easier to parse
 * rel-op as a part of condition.
 * */
int program();
int block();
int const_declaration();
int var_declaration();
int proc_declaration();
int statement();
int condition();
int expression();
int term();
int factor();

/******************************************************************************/
/* Definitions of helper functions starts *************************************/
/******************************************************************************/

Token getCurrentToken()
{
    return getCurrentTokenFromIterator(_token_list_it);
}

int getCurrentTokenType()
{
    return getCurrentToken().id;
}

void nextToken()
{
    _token_list_it.currentTokenInd++;
}

/**
 * Given the code generator error code, prints error message on file by applying
 * required formatting.
 * */
void printCGErr(int errCode, FILE* fp)
{
    if(!fp || !errCode) return;

    fprintf(fp, "CODE GENERATOR ERROR[%d]: %s.\n", errCode, codeGeneratorErrMsg[errCode]);
}

int emit(int OP, int R, int L, int M)
{
    if(nextCodeIndex == MAX_CODE_LENGTH)
    {
        fprintf(stderr, "MAX_CODE_LENGTH(%d) reached. Emit is unsuccessful: terminating code generator..\n", MAX_CODE_LENGTH);
        exit(0);
    }
    
    vmCode[nextCodeIndex] = (Instruction){ .op = OP, .r = R, .l = L, .m = M};    

    return nextCodeIndex++;
}

void printEmittedCodes()
{
    for(int i = 0; i < nextCodeIndex; i++)
    {
        Instruction c = vmCode[i];
        fprintf(_out, "%d %d %d %d\n", c.op, c.r, c.l, c.m);
    }
}

/******************************************************************************/
/* Definitions of helper functions ends ***************************************/
/******************************************************************************/

/**
 * Advertised codeGenerator function. Given token list, which is possibly the
 * output of the lexer, parses a program out of tokens and generates code. 
 * If encountered, returns the error code.
 * 
 * Returning 0 signals successful code generation.
 * Otherwise, returns a non-zero code generator error code.
 * */
int codeGenerator(TokenList tokenList, FILE* out)
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

    // Initialize current scope to NULL, which is the global scope
    currentScope = NULL;

    // The index on the vmCode array that the next emitted code will be written
    nextCodeIndex = 0;

    // The id of the register currently being used
    currentReg = 0;

    // Initialize symbol table
    initSymbolTable(&symbolTable);

    // Start parsing by parsing program as the grammar suggests.
    int err = program();

    // Print symbol table - if no error occured
    if(!err)
    {
        // Print the emitted codes to the file
        printEmittedCodes();
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

// Already implemented.
int program()
{
    // Generate code for block
    int err = block();
    if(err) return err;

    // After parsing block, periodsym should show up
    if( getCurrentTokenType() == periodsym )
    {
        // Consume token
        nextToken();

        // End of program, emit halt code
        emit(SIO_HALT, 0, 0, 3);

        return 0;
    }
    else
    {
        // Periodsym was expected. Return error code 6.
        return 6;
    }
}

int block()
{
    int err = const_declaration();
		if (err) return err;

		err = var_declaration();
		if (err) return err;

		err = proc_declaration();
		if (err) return err;

    // Check statement() for errors after running
    err = statement();
    if (err) return err;

    return 0;
}

int const_declaration()
{
    Symbol currentSymbol;

    if (getCurrentTokenType() == constsym)
    {
        currentSymbol.type = CONST;
        currentSymbol.level = currentLevel;
      
        do
        {
            nextToken(); // Go to the next token..

            if (getCurrentTokenType() != identsym)
            {
                // error expected identifier
                return 3;
            }
            
            strcpy(currentSymbol.name, getCurrentToken().lexeme);

            nextToken(); // Go to the next token..

            if (getCurrentTokenType() != eqsym)
            {
                // identifier must be followed by an = sign
                return 2;
            }

            nextToken(); // Go to the next token..

            if (getCurrentTokenType() != numbersym)
            {
                // Error, = must be followed by a number
                return 1;
            }
            
            currentSymbol.value = strtod(getCurrentToken().lexeme, NULL);
            addSymbol(&symbolTable, currentSymbol);

            nextToken(); // Go to the next token..
        } while (getCurrentTokenType() == commasym);

        if (getCurrentTokenType() != semicolonsym)
        {
            // Error, semicolon or comma expected
            return 4;
        }

        nextToken(); // Go to the next token..
    }
    
    // Successful parsing.
    return 0;
}

int var_declaration()
{
    Symbol currentSymbol;
    
    if (getCurrentTokenType() == varsym)
    {
        currentSymbol.type = VAR;
        currentSymbol.level = currentLevel;

        do
        {
            // GET TOKEN
            nextToken(); // Go to the next token..

            if (getCurrentTokenType() != identsym)
            {
                // Expected identifier
                return 3;
            }

            strcpy(currentSymbol.name, getCurrentToken().lexeme);
            addSymbol(&symbolTable, currentSymbol);

            // GET TOKEN
            nextToken(); // Go to the next token..
        } while (getCurrentTokenType() == commasym);

        if (getCurrentTokenType() != semicolonsym)
        {
            // Error, expected semicolon or comma after identifier
            return 4;
        }
        
        // GET TOKEN
        nextToken(); // Go to the next token..
    }
    
    return 0;
}

int proc_declaration()
{
    Symbol currentSymbol;
    
    while (getCurrentTokenType() == procsym)
    {
        //Get Token
        nextToken(); // Go to the next token..

        currentSymbol.type = PROC;
        currentSymbol.level = currentLevel;

        if (getCurrentTokenType() != identsym)
        {
            // Error, expected identifier after const, sym etc
            return 3;
        }

        strcpy(currentSymbol.name, getCurrentToken().lexeme);
        addSymbol(&symbolTable, currentSymbol);

        // GET TOKEN
        nextToken(); // Go to the next token..

        if (getCurrentTokenType() != semicolonsym)
        {
            // Expected semicolon after identifier
            return 5;
        }

        // GET TOKEN
        nextToken(); // Go to the next token..

        currentLevel++;
        
        // run function and check error
        int err = block();
        if (err) return err;
        
        currentLevel--;

        if (getCurrentTokenType() != semicolonsym)
        {
            // Expected a semicolon
            return 5;
        }

        // GET TOKEN
        nextToken(); // Go to the next token..
    }
    
    return 0;
}

int statement()
{
    if (getCurrentTokenType() == identsym)
    {
        nextToken(); // Go to the next token..
        
        if (getCurrentTokenType() != becomessym)
        {
            // We expected a becomessym
            // Assignment operator expected
            return 7;
        }
        
        nextToken(); // Go to the next token..

        // Check for error in expression
        int err = expression();
        if (err) return err;
    }
    else if (getCurrentTokenType() == callsym)
    {
        nextToken(); // Go to the next token..
        
        if (getCurrentTokenType() != identsym)
        {
            // We expected identsym
            // Expected identifier
            return 8;
        }
        
        nextToken(); // Go to the next token..
    }
    else if (getCurrentTokenType() == beginsym)
    {
        nextToken(); // Go to the next token..

        // Check for error in statement
        int err = statement();
        if (err) return err;

        while (getCurrentTokenType() == semicolonsym)
        {
            nextToken(); // Go to the next token..

            int err = statement();
            if (err) return err;
        }
        
        if (getCurrentTokenType() != endsym) 
        {
            // Semicolon or end expected
            return 10;
        }

        nextToken(); // Go to the next token..
    }
    else if (getCurrentTokenType() == ifsym)
    {
        nextToken(); // Go to the next token..

        int err = condition();
        if (err) return err;

        if (getCurrentTokenType() != thensym)
        {
            // then expected
            return 9;
        }

        nextToken(); // Go to the next token..
        
        err = statement();
        if (err) return err;

        if (getCurrentTokenType() == elsesym)
        {
            nextToken(); // Go to the next token..

            err = statement();
            if (err) return err;
        }
    }
    else if (getCurrentTokenType() == whilesym)
    {
        nextToken(); // Go to the next token..

        int err = condition();
        if (err) return err;

        if (getCurrentTokenType() != dosym)
        {
            // Expected do
            return 11;
        }
        
        nextToken(); // Go to the next token..

        err = statement();
        if (err) return err;
    }
    else if (getCurrentTokenType() == writesym)
    {
        nextToken(); // Go to the next token..

        if (getCurrentTokenType() != identsym)
        {
            // Expected an identifier after a write
            return 3;
        }

        nextToken(); // Go to the next token..
    }
    else if (getCurrentTokenType() == readsym)
    {
        nextToken(); // Go to the next token..

        if (getCurrentTokenType() != identsym)
        {
            // Expected an identifier after a read
            return 3;
        }

        nextToken(); // Go to the next token..
    }
    
    return 0;
}

int condition()
{
    if (getCurrentTokenType() == oddsym)
    {
        nextToken(); // Go to next token

        // Check error
        int err = expression();
        if (err) return err;
    }
    else
    {
        int err = expression();
        if (err) return err;
        
        /*
        Possible cases are =, !=, <, <=, >, >=
        */
    
        if (getCurrentTokenType() == eqsym || getCurrentTokenType() == neqsym ||
            getCurrentTokenType() == lessym || getCurrentTokenType() == leqsym ||
            getCurrentTokenType() == gtrsym || getCurrentTokenType() == geqsym)
        {
            nextToken(); // Go to next token
        }
        else
        {
            /*
              A relational operator was expected
            */
            
            return 12;
        }

        // Parse expression again, returning error if immediate error
        err = expression();
        if (err) return err;
    }
    
    return 0;
}

int expression()
{
    int addop, err = 0;
    
    if (getCurrentTokenType() == plussym || getCurrentTokenType() == minussym)
    {
        addop = getCurrentTokenType();
        nextToken(); // Go to next token
        
        // Get next term and check for error
        err = term();
        if (err) return err;
        
        if (addop == minussym)
          // emit(NEG, <register dst>, <register src>, 0); // negate
    }
    else
    {
        // Get term error code
        err = term();
        
        // If there was an error, return immediately
        if (err) return err;
    }

    while (getCurrentTokenType() == plussym || getCurrentTokenType() == minussym)
    {
        addop = getCurrentTokenType();
        nextToken(); // Go to next token

        // Get next term and check for error
        err = term();
        if (err) return err;
        
        if (addop == plussym)
          // emit(ADD, <reg dst>, <reg src 1>, <reg src 2>) // addition
        else
          // emit(SUB, <reg dst>, <reg src 1>, <reg src 2>) // subtraction
    }
    
    return 0;
}

int term()
{
    // Run the factor function
    int err = factor();
    if (err) return err;
    
    /*
      While current type is multsym or slashsym	
    */
    
    while (getCurrentTokenType() == multsym || getCurrentTokenType() == slashsym)
    {
        nextToken(); // Go to next token

        // Get the code from factor. If error, return the error
        err = factor();
        if (err) return err;
    }
    
    // Success returns 0
    return 0;
}

int factor()
{
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
        nextToken(); // Go to the next token..

        // Success
        return 0;
    }
    // Is that a numbersym?
    else if(getCurrentTokenType() == numbersym)
    {
        // Consume numbersym
        nextToken(); // Go to the next token..

        // Success
        return 0;
    }
    // Is that a lparentsym?
    else if(getCurrentTokenType() == lparentsym)
    {
        // Consume lparentsym
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
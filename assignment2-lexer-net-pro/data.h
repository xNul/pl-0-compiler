#ifndef __DATA_H__
#define __DATA_H__

#define MAX_IDENTIFIER_LENGTH 11
#define MAX_NUM_DIGIT_LENGTH  5

// Numerical values assigned to each token
enum {
    nulsym     =  1, identsym =  2, numbersym    =  3,

    // Special symbols
                                                       plussym   =  4, minussym   =  5, 
    multsym    =  6, slashsym =  7, oddsym       =  8, eqsym     =  9, neqsym =     10, 
    lessym     = 11,  leqsym  = 12, gtrsym       = 13, geqsym    = 14,lparentsym  = 15,
    rparentsym = 16, commasym = 17, semicolonsym = 18, periodsym = 19, becomessym = 20, 
    
    // Reserved words
    beginsym = 21, endsym  = 22, ifsym    = 23, thensym = 24, whilesym = 25, 
    dosym    = 26, callsym = 27, constsym = 28, varsym  = 29, procsym  = 30, 
    writesym = 31, readsym = 32, elsesym  = 33
};

// Useful while iterating over tokens
const int firstReservedToken = plussym;
const int lastReservedToken  = elsesym;

// The string representation of each token, if applicable (identsym and numbersym excluded)
const char* tokens[] = {
    [nulsym] = "",

    // Special symbols (+ odd)
    [plussym]    =   "+", [minussym] = "-", [multsym]      =  "*", [slashsym]    = "/",
    [oddsym]     = "odd", [eqsym]    = "=", [neqsym]       = "<>", [lessym]      = "<",
    [leqsym]     =  "<=", [gtrsym]   = ">", [geqsym]       = ">=", [lparentsym]  = "(",
    [rparentsym] =   ")", [commasym] = ",", [semicolonsym] = ";",  [periodsym]   = ".",
    [becomessym] =  ":=", 

    // Reserved words
    [beginsym] = "begin", [endsym]  =  "end", [ifsym]   =        "if", [thensym] = "then",
    [whilesym] = "while", [dosym]   =   "do", [callsym] =      "call", 
    [constsym] = "const", [varsym]  =  "var", [procsym] = "procedure", 
    [writesym] = "write", [readsym] = "read", [elsesym] =      "else"
};

#endif
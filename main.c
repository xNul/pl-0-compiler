/**
 * COP3402 Fall 2018
 * Assignment 2: Lexical Analyzer
 * Necip Yildiran, yildiran@knights.ucf.edu
 * */
#include <stdio.h>
#include "lexical_analyzer.h"
#include "source_code.h"

int main(int argc, char **argv)
{
    FILE *inp, *outp;

    /**********************************/
    /* Parsing Command Line Arguments */
    /**********************************/
    if(argc != 3)
    {
        fprintf(stderr, "Usage: la.out (pl0_source_code_file) (lexical_analyzer_output_file)\n");

        fprintf(stderr, "\n       pl0_source_code_file: The path to the file containing the source code for the"
                        "\n            programming language PL/0.\n");

        fprintf(stderr, "\n       lexical_analyzer_output_file: The path to the file to write the lexical analyzer"
                        "\n            output, which contains the lexeme table and the symbol table.");

        return -1;
    }

    // open the input file for reading
    if( !(inp = fopen(argv[1], "r")) )
    {
        fprintf(stderr, "Could not open \"%s\"\n", argv[1]);
        return -1;
    }

    // open the output file for writing
    if( !(outp = fopen(argv[2], "w")) )
    {
        fprintf(stderr, "Could not open \"%s\"\n", argv[2]);

        // Before terminating, close the input file
        fclose(inp);

        return -1;
    }              

    /**********************************/
    /**** Call to lexical analyzer ****/
    /**********************************/
    // Read source code
    char *sourceCode = readSourceCode(inp);

    // Do lexical analysis
    LexerOut lexerOut = lexicalAnalyzer(sourceCode);

    if(lexerOut.lexerError != NONE)
    {
        // If error is encountered, print error message
        fprintf(outp, "ERROR: LexErr[%d] was encountered at line %d while "
                        "lexical analysis: ", 
                        lexerOut.lexerError, lexerOut.errorLine);
        switch(lexerOut.lexerError)
        {
            case NONLETTER_VAR_INITIAL:
                fprintf(outp, "Variable does not start with letter.");
                break;
            case NAME_TOO_LONG:
                fprintf(outp, "Name too long.");
                break;
            case NUM_TOO_LONG:
                fprintf(outp, "Number too long.");
                break;
            case INV_SYM:
                fprintf(outp, "Invalid symbol.");
                break;
        }
    }
    else
    {
        // If the execution of lexical analysis is successful, print success message
        // .. followed by the list of tokens
        fprintf(outp, "SUCCESS: No errors found in the source code.\n\n");

        printTokenList(lexerOut.tokenList, outp);
    }

    deleteLexerOut(&lexerOut);
    deleteSourceCode(sourceCode);

    /**********************************/
    /* Closing input and output files */
    /**********************************/

    // close the input and the output file stream
    fclose(inp);
    fclose(outp);

    return 0;
}

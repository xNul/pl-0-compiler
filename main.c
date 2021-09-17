#include <stdio.h>
#include "token.h"
#include "parser.h"

int main(int argc, char **argv)
{
    FILE *inp, *outp;

    /**********************************/
    /* Parsing Command Line Arguments */
    /**********************************/
    if(argc != 3)
    {
        fprintf(stderr, "Usage: parser.out (pl0_lexer_out) (parser_output_file)\n");

        fprintf(stderr, "\n       pl0_lexer_out: The path to the file containing the lexer out for the programming language PL/0.\n");

        fprintf(stderr, "\n       parser_output_file: The path to the file to write the parser output, which contains the parsing history, the symbol table and the error message if applicable.\n");
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
    /**** Call to parser ****/
    /**********************************/
    // Read the token list
    TokenList tokenList = readTokenList(inp);
    
    // Run parser
    int err = parser(tokenList, outp);

    // Print error - if there exists any
    printParserErr(err, outp);

    // Delete token list created by readTokenList()
    deleteTokenList(&tokenList);

    /**********************************/
    /* Closing input and output files */
    /**********************************/

    // close the input and the output file stream
    if(inp) fclose(inp);
    if(outp) fclose(outp);

    return 0;
}

#include "symbol.h"
#include <stdlib.h>

void initSymbolTable(SymbolTable* symbolTable)
{
    symbolTable->symbols = NULL;
    symbolTable->numberOfSymbols = 0;
}

void deleteSymbolTable(SymbolTable* symbolTable)
{
    if(!symbolTable) return;

    if(symbolTable->symbols)
        free(symbolTable->symbols);

    symbolTable->symbols = NULL;
    symbolTable->numberOfSymbols = 0;
}

Symbol* addSymbol(SymbolTable* symbolTable, Symbol symbol)
{
    if(!symbolTable) return NULL;

    symbolTable->numberOfSymbols++;

    symbolTable->symbols = (Symbol*)realloc(symbolTable->symbols, (symbolTable->numberOfSymbols) * sizeof(Symbol));

    symbolTable->symbols[symbolTable->numberOfSymbols - 1] = symbol;

    return &symbolTable->symbols[symbolTable->numberOfSymbols - 1];
}

void printSymbolTable(SymbolTable* symbolTable, FILE* out)
{
    if(!symbolTable || !out) return;

    fprintf(out, "Symbol Table\n============\n");

    for(int i = 0; i < symbolTable->numberOfSymbols; i++)
    {
        fprintf(out, "#%d\n", i);

        Symbol* symbol = &(symbolTable->symbols[i]);

        // print type
        switch(symbol->type)
        {
            case VAR:
                fprintf(out, 
                    "   Type: VAR\n"
                    "   Name: %s\n"
                    "  Level: %d\n",
                    symbol->name, symbol->level);
                    break;

            case CONST:
                fprintf(out, 
                    "   Type: CONST\n"
                    "   Name: %s\n"
                    "  Value: %d\n"
                    "  Level: %d\n",
                    symbol->name, symbol->value, symbol->level);
                    break;

            case PROC:
                fprintf(out, 
                    "   Type: PROC\n"
                    "   Name: %s\n"
                    "  Level: %d\n",
                    symbol->name, symbol->level);
                    break;
        }
        
        fprintf(out, "\n");
    }
}
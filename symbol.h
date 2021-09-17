#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <stdio.h>

/**
 * There are three possible types of symbols that can be an entry of a symbol table
 * */
typedef enum
{
    CONST,
    VAR,
    PROC
} SymbolType;

/**
 * Struct that holds information of a single symbol table entry.
 * The validity of fields are as follows:
 * type   : CONST, VAR, PROC
 * name   : CONST, VAR, PROC
 * value  : CONST, VAR
 * level  : CONST, VAR, PROC
 * */

typedef struct Symbol Symbol;

struct Symbol { 
	SymbolType type;
	char name[12];
	int value;
	unsigned int level;
};

/**
 * Symbol table.
 * */
typedef struct {
    Symbol* symbols;
    int numberOfSymbols;
} SymbolTable;

/**
 * Initializes the given symbol table to a empty symbol table.
 * */
void initSymbolTable(SymbolTable*);

/**
 * Destructs the symbol table by making necessary deallocations on the members
 * of the symbol table struct.
 * */
void deleteSymbolTable(SymbolTable*);

/**
 * Appends a copy of the given symbol to the given symbol table.
 * */
Symbol* addSymbol(SymbolTable*, Symbol);

/**
 * Given symbol table, prints the entries of symbol table to the given file.
 * */
void printSymbolTable(SymbolTable*, FILE*);

#endif
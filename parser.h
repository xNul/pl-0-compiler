#ifndef __PARSER_H__
#define __PARSER_H__

#include "token.h"

int parser(TokenList, FILE*);

void printParserErr(int errCode, FILE*);

#endif
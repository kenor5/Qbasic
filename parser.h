#ifndef PARSER_H
#define PARSER_H
#include <stack>
#include "exp.h"
#include "tokenizer.h"


Exp* parseStmt(Tokenizer &t);

int level(string str);


#endif // PARSER_H

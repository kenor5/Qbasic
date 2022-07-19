#ifndef TOKENIZER_H
#define TOKENIZER_H
#include <queue>
#include "exp.h"

enum char_type{chr, num, op, ilg, pat, eql};
enum token_type{NUM, VAR, OP, PA};

char_type getType(char ch);

class Tokenizer
{
public:
    Tokenizer();
    string getNext(char pre_chr);
    int getInt();
    string getString();
    bool hasTokens();
    void setInput(string str);
    token_type getTokenType(string str);
    void pushFront(string str);
    void trim();

    string str;
};

#endif // TOKENIZER_H

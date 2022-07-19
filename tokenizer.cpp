#include "tokenizer.h"

Tokenizer::Tokenizer()
{

}

void Tokenizer::trim()
{
    int index = 0;
    if(!str.empty())
    {
        while( (index = str.find(' ',index)) != string::npos)
        {
            str.erase(index,1);
        }
    }
}




char_type getType(char ch) {
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        return chr;

    if (
        ch == '+' ||
        ch == '-' ||
        ch == '*' ||
        ch == '/'
        )
        return op;

    if (ch == '(' ||
        ch == ')')
        return pat;

    if (ch == '=')
        return eql;

    if (ch >= '0' && ch <= '9')
        return num;

    return ilg;
}

string Tokenizer::getNext(char pre_chr) {
    int tmpLoc = 0;
    trim();
    char_type pre_type = getType(str[0]);
    while (true) {
        tmpLoc ++;
        if (tmpLoc >= str.size()) {
            break;
        }
        char_type cur_type = getType(str[tmpLoc]);
        if (cur_type != pre_type) {
            if (!((pre_type == chr && cur_type == num) || (str[tmpLoc-1] == '-'
                                                           && cur_type == num
                                                           && (pre_chr == ' '||
                                                               pre_chr == '('||
                                                               pre_chr == '='
                                                               )
                                                           )))
                break;
        }
        pre_type = cur_type;
    }

    string rtStr = str.substr(0, tmpLoc);
    str.erase(0, tmpLoc);
    return rtStr;
}

bool Tokenizer::hasTokens() {
    if (this->str[0] == ' ')
        str.erase(0, 1);
    return str.size() > 0;
}

int Tokenizer::getInt() {
    int tmpLoc = str.find_first_of(' ');
    int rtValue = stoi(str.substr(0, tmpLoc));
    str.erase(0, tmpLoc+1);

    return rtValue;
}

string Tokenizer::getString() {
    int tmpLoc = str.find_first_of(' ');
    string rtStr = str.substr(0, tmpLoc);
    str.erase(0, tmpLoc+1);
    return rtStr;
}

token_type Tokenizer::getTokenType(string str) {
    if (getType(str[0]) == chr) return VAR;
    if (getType(str[0]) == num) return NUM;
    if (str.size() > 1 && str[0] == '-' && getType(str[1]) == num) return NUM;
    if (getType(str[0]) == op || getType(str[0]) == eql) return OP;
    if (str[0] == '(' || str[0] == ')') return PA;
    return VAR;
}

void Tokenizer::pushFront(string str) {
    this->str = str + this->str;
}

void Tokenizer::setInput(string str) {
    this->str = str;
}

#include "parser.h"


Exp* parseStmt(Tokenizer &t) {
    stack<string> optr;
    stack<Exp *> oped;
    char pre_chr = ' ';
    while (t.hasTokens()) {

        string cur = t.getNext(pre_chr);
        pre_chr = cur[cur.length() - 1];
        token_type type = t.getTokenType(cur);
        if (type == NUM) {
            oped.push(new CnstExp(stoi(cur)));
        }else if (type == VAR) {
            oped.push(new IdExp(cur));
        }else if (type == OP) {

            while (!optr.empty() && level(optr.top()) >= level(cur)
                   && !(optr.top() == "**" && cur == "**")) {
                Exp* right = oped.top();
                oped.pop();
                Exp* left = oped.top();
                oped.pop();
                oped.push(new CpdExp(optr.top(), left, right));
                optr.pop();
            }
            optr.push(cur);
        }else if (type == PA) {
            if (cur == "(")
                optr.push(cur);
            else if (cur == ")") {
                while (1)  {
                    string tmp = optr.top();
                    optr.pop();
                    if (tmp == "(") break;

                    Exp* right = oped.top();
                    oped.pop();
                    Exp* left = oped.top();
                    oped.pop();
                    oped.push(new CpdExp(tmp, left, right));

                }
            }
        }
    }


    while (!optr.empty()) {
        Exp* right = oped.top();
        oped.pop();
        Exp* left = oped.top();
        oped.pop();
        oped.push(new CpdExp(optr.top(), left, right));
        optr.pop();
    }

    Exp* exp = oped.top();
    oped.pop();
    return exp;

}


int level(string str) {
    if (str == "*" || str == "/")
        return 3;
    else if (str == "+" || str == "-")
        return 2;
    else if (str == "**")
        return 4;
    else if (str == "=")
        return 1;

    return 0;
}

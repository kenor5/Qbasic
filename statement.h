#ifndef STATEMENT_H
#define STATEMENT_H
#include <string>
#include <QInputDialog>
#include "exp.h"
#include "tokenizer.h"
#include "parser.h"
using namespace std;

class Statement
{
public:
    Statement();
    virtual ~Statement();

    virtual void exec(EvlCtxt &state)=0;
    virtual string show()=0;

};



class LetStmt:public Statement {
public:
    LetStmt(Exp* exp);
    ~LetStmt()override=default;

    void exec(EvlCtxt &state) override;
    string show() override;
private:
        Exp* exp_tree;
};

class PrintStmt : public Statement {
public:
    PrintStmt(Exp *exp);
    ~PrintStmt() override=default;

    void exec(EvlCtxt &state) override;
    string show() override;

private:
    Exp* exp_tree;
};

class RemStmt : public Statement {
public:
    RemStmt(string str);
    ~RemStmt() override=default;

    void exec(EvlCtxt &state) override;
    string show() override;
private:
    string cxt;
};

class gotoStmt : public Statement {
public:
    gotoStmt(int line);
    ~gotoStmt() override=default;

    void exec(EvlCtxt &state) override;
    string show() override;
private:
    int dst;
};

class ifStmt : public Statement {
public:
    ifStmt(string str);
    ~ifStmt() override=default;

    void exec(EvlCtxt &state) override;
    string show() override;
private:
    int dst;
    string cdtn;
    Exp *exp_l, *exp_r;
    char op;
    bool tth;
};

class endStmt : public Statement {
public:
    endStmt();
    ~endStmt() override=default;

    void exec(EvlCtxt &state) override;
    string show() override;
};

class inputStmt :public Statement {

public:
    inputStmt(string name);
    ~inputStmt() override=default;

    void exec(EvlCtxt &state) override;
    string show() override;
private:
    string var;

};

#endif // STATEMENT_H

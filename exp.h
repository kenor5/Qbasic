#ifndef EXP_H
#define EXP_H
#include <string>
#include <map>
#include <iostream>
#include <queue>
#include <math.h>
#include "evalstate.h"

using namespace std;

class EvlCtxt;

enum ExpType { CNST, ID, CPD};

void error(string str);

class Exp {
public:

    Exp();
    virtual ~Exp();
    virtual int eval(EvlCtxt & cxt) = 0;
    virtual string toString() = 0;
    virtual ExpType type() = 0;
    virtual string show(int i = 1)=0;


    virtual int getCnstVal();
    virtual string getIdName();
    virtual string getOp();
    virtual Exp* getLc();
    virtual Exp* getRc();

    Exp *lc, *rc;
};

class CnstExp:public Exp{

public:
    CnstExp(int val);

    virtual int eval(EvlCtxt & cxt) override;
    virtual string toString() override;
    virtual ExpType type() override;
    string show(int i = 1) override;

    virtual int getCnstVal() override;

private:
    int value;
};

class IdExp:public Exp{
public:
    IdExp(string name);
    virtual int eval(EvlCtxt &cxt) override;
    virtual string toString() override;
    virtual ExpType type() override;
    string show(int i = 1) override;

    virtual string getIdName() override;
private:
    string name;
};

class CpdExp:public Exp {
public:
    CpdExp(string op, Exp* lc, Exp* rc);
    virtual ~CpdExp();

    virtual int eval(EvlCtxt &cxt) override;
    virtual string toString() override;
    virtual ExpType type() override;
    string show(int i = 1) override;

    virtual string getOp() override;
    virtual Exp* getRc() override;
    virtual Exp* getLc() override;

private:
    string op;

};



#endif // EXP_H

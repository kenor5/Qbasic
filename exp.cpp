#include "exp.h"
#include <stdio.h>

void error(string str) {

}

Exp::Exp(){lc = nullptr; rc = nullptr;}
Exp::~Exp()=default;
int Exp::getCnstVal(){return 0;}
string Exp::getIdName(){return "";}
string Exp::getOp(){return "";}
Exp* Exp::getLc(){return nullptr;}
Exp* Exp::getRc(){return nullptr;}


int CnstExp::eval(EvlCtxt &cxt) {
    return value;
}

int IdExp::eval(EvlCtxt &cxt) {
    if (!cxt.isDefined(name)) error(name + " is undefined");
    return cxt.getValue(name);
}

int CpdExp::eval(EvlCtxt &cxt) {
    int right = rc->eval(cxt);
    if (op == "=") {
        cxt.setValue(lc->getIdName(), right);
        return right;
    }

    int left = lc->eval(cxt);
    if (op == "+") return left + right;
    if (op == "-") return left - right;
    if (op == "*") return left * right;
    if (op == "**") return pow(left, right);
    if (op == "/") {
        if (right == 0) error("Division by 0");
        return left/right;
    }
    error("Illegal oerater in expression");
    return 0;

}



//CONSTANTEXP
CnstExp::CnstExp(int val) {
    value = val;
    lc = nullptr;
    rc = nullptr;
}

string CnstExp::toString() {
    return to_string(value);
}

ExpType CnstExp::type() {
    return CNST;
}

int CnstExp::getCnstVal() {
    return value;
}


string CnstExp::show(int i) {
    string rt = "";
    for (; i > 0; i --) {
        rt += "  ";
    }
    return rt + to_string(value) + "\n";
}
//IDENTIFIER
IdExp::IdExp(string name) {
    this->name = name;
    lc = nullptr;
    rc = nullptr;
}

string IdExp::toString(){
    return name;
}

ExpType IdExp::type() {
    return ID;
}

string IdExp::getIdName() {
    return name;
}

string IdExp::show(int i) {
    string rt = "";
    for (; i > 0; i--) {
        rt += "  ";
    }
    return rt + this->name + "\n";
}

//COMPOUND
CpdExp::CpdExp(string op, Exp* lc, Exp* rc) {
    this->op = op;
    this->lc = lc;
    this->rc = rc;
}

CpdExp::~CpdExp() {

}

string CpdExp::toString() {
    return "(" + lc->toString()+op+rc->toString() + ")";
}

ExpType CpdExp::type() {
    return CPD;
}

string CpdExp::getOp(){
    return op;
}

Exp* CpdExp::getLc() {
    return lc;
}

Exp* CpdExp::getRc() {
    return rc;
}

string CpdExp::show(int i) {
    queue<Exp *> tra;
    queue<int> blank;

    tra.push(this);
    blank.push(i);

    string rtvl = "";
    while (!tra.empty()) {
        Exp *tmp = tra.front();
        tra.pop();
        int bl = blank.front();
        blank.pop();

        if (tmp->type() == CPD) {
            if (tmp->lc) {
                tra.push(tmp->lc);
                blank.push(bl + 1);
            }

            if (tmp->rc) {
                tra.push(tmp->rc);
                blank.push(bl+1);
            }

            for (; bl > 0; -- bl) {
                rtvl += "  ";
            }
            rtvl += tmp->getOp() + "\n";

        }else if (tmp->type() == ID) {
            for (; bl > 0; -- bl) {
                rtvl += "  ";
            }
            rtvl += tmp->getIdName() + "\n";
        }else if (tmp->type() == CNST) {
            for (; bl > 0; -- bl) {
                rtvl += "  ";
            }
            rtvl += to_string(tmp->getCnstVal()) + "\n";
        }
    }
    return rtvl;
}

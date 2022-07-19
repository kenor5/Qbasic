#include "statement.h"

Statement::Statement() = default;

Statement::~Statement() = default;


LetStmt::LetStmt(Exp* exp) {
    exp_tree = exp;
}

void LetStmt::exec(EvlCtxt &state) {
    exp_tree->eval(state);
    state.jump = 0;
}

string LetStmt::show() {

    string rt = "LET ";
    rt += exp_tree->show();
    return rt;
}

PrintStmt::PrintStmt(Exp *exp) {
    exp_tree = exp;

}

void PrintStmt::exec(EvlCtxt &state) {
    int tmp = exp_tree->eval(state);
    state.output += to_string(tmp) + "\n";
    state.jump = 0;
}

string PrintStmt::show() {
    string rt = "PRINT\n";
    rt += exp_tree->show();
    return rt;
}

RemStmt::RemStmt(string str) {
    cxt = str;
}

void RemStmt::exec(EvlCtxt &state) {
    state.jump = 0;
}

string RemStmt::show() {

    string rt = "REM\n ";
    rt += this->cxt;
    rt += "\n";
    return rt;
}

gotoStmt::gotoStmt(int line) {
    dst = line;
}

void gotoStmt::exec(EvlCtxt &state) {
    state.setCurLine(dst);
    state.jump = 1;
}

string gotoStmt::show() {

    string rt = "GOTO\n ";
    rt += to_string(this->dst);
    rt += "\n";
    return rt;
}

inputStmt::inputStmt(string name) {
    this->var = name;
}

void inputStmt::exec(EvlCtxt &state) {
    state.jump = 0;
    int input_vlu = QInputDialog::getInt(nullptr,
                                         "input varVlu",
                                         "vlu");
    state.setValue(var, input_vlu);
}

string inputStmt::show() {

    string rt = "INPUT\n ";
    rt += this->var;
    rt += "\n";
    return rt;

}

endStmt::endStmt() {

}

void endStmt::exec(EvlCtxt &state) {
    state.setCurLine(-1);
    state.jump = 1;
}

string endStmt::show() {
    return "END\n";
}

ifStmt::ifStmt(string str){
    int i = 0;
    while (1) {
        i ++;
        if (str[i] == 'T' && str[1+i] == 'H' && str[2+i] == 'E' && str[3+i] == 'N')
            break;
    }
    cdtn = str.substr(0, i-1);
    dst = stoi(str.substr(i+5, str.npos));

    i = 0;
    while (1) {
        i++;
        if (cdtn[i] == '>' || cdtn[i] == '<' || cdtn[i] == '=')
            break;
    }
    op = cdtn[i];
    Tokenizer lft, rgt;
    lft.setInput(cdtn.substr(0, i));
    rgt.setInput(cdtn.substr(i+1, cdtn.npos));
    exp_l = parseStmt(lft);
    exp_r = parseStmt(rgt);


}

void ifStmt::exec(EvlCtxt &state) {

    int lft_value, rgt_value;
    lft_value = exp_l->eval(state);
    rgt_value = exp_r->eval(state);

    if (op == '>')
        tth = (lft_value > rgt_value);
    else if (op == '<')
        tth = (lft_value < rgt_value);
    else if (op == '=')
        tth = (lft_value == rgt_value);

    if (tth) {
        state.setCurLine(dst);
        state.jump = 1;
    }else
        state.jump = 0;

}


string ifStmt::show() {
    string rt = "IF THEN\n";

    rt += "  " + string(1, op) + "\n";
    rt += exp_l->show();
    rt += exp_r->show();
    rt += "  " + to_string(dst);
    rt += "\n";
    return rt;
}

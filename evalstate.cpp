#include "evalstate.h"

EvlCtxt::EvlCtxt() {
    jump = 0;
    output = "";
}

void EvlCtxt::clear() {
    this->jump = 0;
    this->cur_line = -1;
    this->vtable.clear();
    this->nxt_line.clear();
    this->output = "";
}

//EVALUATION
void EvlCtxt::setValue(string var, int value) {
    this->vtable[var] = value;
}

int EvlCtxt::getValue(string var) {
    if (this->isDefined(var)) {
        return vtable[var];
    }
    error("var is undefined");
    return 0;
}

bool EvlCtxt::isDefined(string var) {
    return vtable.find(var) != vtable.end();
}


int EvlCtxt::getNxtLine() {
    return nxt_line[cur_line];
}

void EvlCtxt::setCurLine(int line) {
    this->cur_line = line;
}

void EvlCtxt::show(){
    cout << "curLine: " << cur_line << endl;
    cout << "var: " << endl;
    for(auto i = vtable.begin(); i != vtable.end(); i++)
        cout << i->first << " " << i->second << endl;
    cout << endl;
    for(auto i = nxt_line.begin(); i != nxt_line.end(); i++)
        cout << i->first << " " << i->second << endl;
}

int EvlCtxt::getFirstLine() {
    return nxt_line.begin()->first;
}

#include "program.h"

Program::Program()
{

}

void Program::clear() {
    this->cxt.clear();
    code.clear();
}

Statement* Program::getStmt(int line) {
    if (cxt.find(line) != cxt.end())
        return cxt[line];
    else
         error("no line" + to_string(line));
    return nullptr;
}

void Program::init(EvlCtxt &state) {
    if (state.nxt_line.begin() != state.nxt_line.end()) {
        state.cur_line = state.getFirstLine();
    }else
        state.cur_line = -1;

    state.jump = 0;

}

string Program::show(EvlCtxt &state) {
    int cur_line = state.getFirstLine();
    string rtvlu = "";
    while (cur_line != -1) {
        rtvlu += to_string(cur_line) + " ";
        rtvlu += this->cxt[cur_line]->show();
        cur_line = state.getNxtLine();
        state.cur_line = cur_line;
    }

    return rtvlu;
}

void Program::insertStmt(int line, Statement *stmt, EvlCtxt &state) {
    auto i = cxt.begin();
    for(; i != cxt.end(); i++) {
        if (i->first > line)
            break;
    }
    if(i != cxt.end() || (i == cxt.end() && !cxt.empty()))
        i --;
    else {
        state.nxt_line[line] = -1;
        cxt[line] = stmt;
        return;
    }

    if (i->first != line) {
        state.nxt_line[line] = state.nxt_line[i->first];
        state.nxt_line[i->first] = line;
    }
    cxt[line] = stmt;
}

void Program::delStmt(int line, EvlCtxt &state) {
    if (cxt.find(line) != cxt.end()){
        cxt.erase(line);
        code.erase(line);
        auto i = state.nxt_line.begin();
        for (; i != state.nxt_line.end(); i++) {
            if (i->first == line)
                break;
        }
        if (i == state.nxt_line.begin())
        {
            state.nxt_line.erase(i);
            return;
        }
        i--;
        state.nxt_line[i->first] = state.nxt_line[state.nxt_line[i->first]];
        state.nxt_line.erase(++i);
    }

}

void Program::insertCode(int t, string cxt) {
    code[t] = cxt;
}

string Program::getCode(EvlCtxt &state) {
    string rtvlu = "";
    init(state);
    int cur = state.cur_line;
    while (cur != -1) {
        rtvlu += to_string(cur) + " ";
        rtvlu += code[cur] + "\n";
        cur = state.getNxtLine();
        state.cur_line = cur;
    }

    return rtvlu;
}

#ifndef EVALSTATE_H
#define EVALSTATE_H
#include <string>
#include <map>
#include "exp.h"
using namespace std;

class EvlCtxt{
public:
    EvlCtxt();

    int getNxtLine();
    int getFirstLine();
    void setCurLine(int line);
    void setValue(string var, int value);
    int getValue(string var);
    bool isDefined(string var);
    void show();
    void clear();

    map<string, int> vtable;

    map<int, int> nxt_line;
    int cur_line;
    bool jump;
    string output;
};

#endif // EVALSTATE_H

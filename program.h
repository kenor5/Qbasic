#ifndef PROGRAM_H
#define PROGRAM_H
#include <QString>
#include "statement.h"


class Program
{
public:
    Program();


    void insertStmt(int line, Statement* stmt, EvlCtxt &state);
    Statement* getStmt(int line);
    void delStmt(int line, EvlCtxt &state);
    void init(EvlCtxt &state);
    string show(EvlCtxt &state);
    string getCode(EvlCtxt &state);
    void insertCode(int t, string cxt);
    void clear();

private:
    map<int, Statement*> cxt;
    map<int, string> code;
};

#endif // PROGRAM_H

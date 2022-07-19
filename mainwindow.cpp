#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    code = "";
    parse_tree = "";
    output = "";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cmdLineEdit_editingFinished()
{
    QString cmd = ui->cmdLineEdit->text();
    ui->cmdLineEdit->setText("");

    ui->CodeDisplay->append(cmd);
}

void MainWindow::on_btnLoadCode_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("选择日志文件"),"",tr("TXT(*.txt)"));
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while(!file.atEnd())
        {

            QByteArray line = file.readLine();
            string tmp = QString(line).toStdString();
            if(tmp[tmp.length()-1] == '\n') tmp.pop_back();
            Tokenizer scanner;
            scanner.setInput(tmp);
            this->processLine(scanner);
         }
    }
    p.init(state);
    code = p.getCode(state);

    flush();
}



void MainWindow::processLine(Tokenizer &t) {
    int line_num = t.getInt();

    if (!t.hasTokens()) {
        p.delStmt(line_num, state);
        code = p.getCode(state);
        return;
    }
    p.insertCode(line_num, t.str);
    p.init(state);

    string cmd = t.getString();
//    cout << t.str<<"||"<<line_num << " " << cmd << endl;
    if (cmd == "LET") {
        Exp* exp = parseStmt(t);
        LetStmt *let = new LetStmt(exp);
        p.insertStmt(line_num, let, state);
    }else if (cmd == "PRINT") {
        Exp* exp = parseStmt(t);
        PrintStmt *print = new PrintStmt(exp);
        p.insertStmt(line_num, print, state);
    }else if (cmd == "REM") {
        p.insertStmt(line_num, new RemStmt(t.str), state);
    }else if (cmd == "INPUT") {
        p.insertStmt(line_num, new inputStmt(t.str), state);
    }else if (cmd == "IF") {
        p.insertStmt(line_num, new ifStmt(t.str), state);
    }else if (cmd == "END") {
        p.insertStmt(line_num, new endStmt(), state);
    }else if (cmd == "GOTO") {
        p.insertStmt(line_num, new gotoStmt(stoi(t.str)), state);
    }else error("bad cmd!");
    code = p.getCode(state);
}

void MainWindow::on_btnClearCode_clicked()
{

    p.clear();
    state.clear();
    code = "";
    output = "";
    parse_tree.clear();
    flush();
}

void MainWindow::on_cmdLineEdit_returnPressed()
{   try {
        p.init(state);
        QString txt = ui->cmdLineEdit->text();
        ui->cmdLineEdit->clear();

        if (txt == "clear" || txt == "CLEAR")
            on_btnClearCode_clicked();
        else if (txt == "run" || txt == "RUN")
            on_btnRunCode_clicked();
        else if (txt == "load" || txt == "LOAD")
            on_btnLoadCode_clicked();
        else if (txt == "QUIT" || txt == "quit")
            exit(0);
        else if (txt == "HELP" || txt == "help")
            cout << " ";
        else if (txt == "LIST" || txt == "list")
            this->parse_tree = p.show(state);
        else {
            try {
                Tokenizer tmp;
                tmp.setInput(txt.toStdString());
                processLine(tmp);
            } catch (exception e) {
                cerr << e.what();
            }
        }
        flush();
    } catch (QString error) {

    }
}

void MainWindow::on_btnRunCode_clicked()
{
    p.init(state);
    state.output = "";
    int cur_line = state.cur_line;

//    state.show();
    while (cur_line != -1) {
        auto stmt = p.getStmt(cur_line);
        stmt->exec(state);
        if (!state.jump)
            state.setCurLine(state.getNxtLine());

        cur_line = state.cur_line;
    }
    output = state.output;
    flush();
}

void MainWindow::flush() {
    ui->CodeDisplay->setText(QString::fromStdString(code));
    ui->textBrowser->setText(QString::fromStdString(output));
    ui->treeDisplay->setText(QString::fromStdString(parse_tree));
}

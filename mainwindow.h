#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "program.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void processLine(Tokenizer &t);
    void flush();

    string code, parse_tree, output;
    Program p;
    EvlCtxt state;

private slots:
    void on_cmdLineEdit_editingFinished();

    void on_btnLoadCode_clicked();

    void on_btnClearCode_clicked();

    void on_cmdLineEdit_returnPressed();

    void on_btnRunCode_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

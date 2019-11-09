#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTextEdit>
#include <QMenu>
#include <QMenuBar>
#include "Runner.h"
#include "Parser.h"
#include "Lexer.h"

#include "Command.h"
#include "Codelist.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMenu * menu;

    QTextEdit *command;


    QLabel *label3;
    CodeList * codelist;

    Lexer *lexer ;
    Parser *parser;
    Runner *runner;
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 800;

public  slots:
        void open_file();
        void save_file();

        void insert_codeline(QString s);
        void show_code();

        void  interpret();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

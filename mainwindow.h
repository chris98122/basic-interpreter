#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTextEdit>
#include <QMenu>
#include <QMenuBar>
#include "Console.h"

#include "Command.h"
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

    Console *input;
    QTextEdit *output;

    QTextEdit *command;

    QLabel *label2;
    QLabel *label1;

    QLabel *label3;

    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 800;

public  slots:
        void open_file();
        void save_file();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

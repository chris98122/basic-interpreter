#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMenu>
#include <QMenuBar>
#include "Console.h"
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
    Console *output;

    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;

public  slots:
        void open_file();
        void save_file();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

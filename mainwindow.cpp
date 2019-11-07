#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <QString>

#include <QTextEdit>
#include <QFileDialog>
#include "Console.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("basic interpreter");
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    input = new Console(this);

    menu= this->menuBar()->addMenu("&File");

    QAction* openfile = new QAction(menu);
    QAction* savefile = new QAction(menu);
    connect( openfile, SIGNAL(triggered()), this, SLOT(open_file()));
    connect( savefile, SIGNAL(triggered()), this, SLOT(save_file()));

    openfile->setText("open file");
    savefile->setText("save file");
    menu->addAction(  openfile);
    menu->addAction( savefile );

    label2 = new QLabel(this);
    label2->setText("input");


    label2->setGeometry(30, 260, 40,  60);

    input ->setGeometry(30, 300, 740, 260);

    input->write("1 ");


    label1 = new QLabel(this);
    label1->setText("output");


    label1->setGeometry(30, 20,  50,  60);

    output = new QTextEdit(this);
    output ->setGeometry(30, 60, 740, 200);
    output->setReadOnly(true);

    label3 = new QLabel(this);
    label3->setText("command");


    label3->setGeometry(30, 560,  80,  60);


    command = new Command(this);
    command ->setGeometry(30, 600, 740, 140);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open_file()
{

    QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("Allfile(*.*);"));
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the file!"<<endl;
    }

    this->input->clear();

    for(int i = 1;!file.atEnd();i++) {
        QByteArray line = file.readLine();
        QString str(line);
        this->input->write(line);
    }
}


void MainWindow::save_file()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr("save file"), "");
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    //读取console里面的text
    QStringList list = input->toPlainText().split("\n");
    for(int i = 0;i < list.size();i++) {
        out<<  list[i].mid(2)<< "\n";
    }
}

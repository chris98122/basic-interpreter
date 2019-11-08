#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <QString>
#include "Codelist.h"
#include <QTextEdit>
#include <QFileDialog>
#include "Command.h"

#include "Lexer.h"

#include "Parser.h"
#include <vector>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("basic interpreter");
    this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);


    menu= this->menuBar()->addMenu("&File");

    QAction* openfile = new QAction(menu);
    QAction* savefile = new QAction(menu);
    connect( openfile, SIGNAL(triggered()), this, SLOT(open_file()));
    connect( savefile, SIGNAL(triggered()), this, SLOT(save_file()));

    openfile->setText("open file");
    savefile->setText("save file");
    menu->addAction(  openfile);
    menu->addAction( savefile );


    label3 = new QLabel(this);
    label3->setText("command");


    label3->setGeometry(30, 10,  80,  60);


    command = new Command(this);
    command ->setGeometry(30, 50, 740, 740);


    codelist = new CodeList();
    connect( command, SIGNAL(newLineWritten(QString)), this,SLOT(  insert_codeline(QString)));
    connect( command, SIGNAL(showCode( )), this,SLOT(  show_code()));

    connect( command, SIGNAL(run( )), this,SLOT(interpret()));
    lexer = new Lexer();
    parser = new Parser();

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


    for(int i = 1;!file.atEnd();i++) {
        QByteArray line = file.readLine();
        QString str(line);
        this->command->append(line);
        this->insert_codeline(str);
    }
}

void MainWindow::insert_codeline(QString s)
{
    bool ok;
    int linenum = (s.split(" ")[0]).toInt(&ok);

    if(ok && linenum >0)
        this->codelist->insert_codeline(s);
   // else
        // this->interpreter->run(s);
}

void MainWindow::save_file()
{

    QString fileName = QFileDialog::getSaveFileName(this, tr("save file"), "");
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    //读取console里面的text
    QStringList list = command->toPlainText().split("\n");
    for(int i = 0;i < list.size();i++) {
        out<<  list[i] << "\n";
    }
}

void MainWindow:: show_code()
{
    qDebug()<<"SHOW CODE!"<<endl;

    codeline *p = this->codelist->head;
    p = p->next;
    while(p)
    {
        std::string * s =  p->code;

        std::string line = std::to_string( p->linenum) ;
        this->command->append(QString((line + " " + *s ).c_str()));
        p = p->next;
    }

}

void MainWindow::interpret()
{
    qDebug()<<"interpret!"<<endl;

    codeline *p = this->codelist->head;
    p=p->next;
    while(p)
    {

        std::string line = std::to_string( p->linenum) ;
        bool lex_ok  ;
        std::string error_meassgae;
        std::list<Token>*token_list = this->lexer->lex_a_line(line + " " + *(p->code) , &lex_ok,&error_meassgae);
        if(lex_ok)
        {
            //this->parser->parse(token_list);
        }
        else
        {
            this->command->append(QString(error_meassgae.c_str()));
        }
        p = p->next;
    }
}

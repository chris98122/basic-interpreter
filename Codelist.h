#ifndef CODELIST_H
#define CODELIST_H


#include <QObject>
#include <QTextEdit>
#include <QWidget>
#include <QString>
struct codeline
{
    int linenum;
    std::string *code;
    codeline *next;

    codeline(int linenum,std::string *code )
    {
        this->linenum = linenum;
        this->code =code;
        this->next = NULL;
    };
};

class CodeList
{
public:
     CodeList();
     ~ CodeList();

    codeline *head;

    void insert_codeline(QString s);


};


#endif // CODELIST_H

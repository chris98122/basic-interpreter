#include "Codelist.h"

#include <QString>

#include <QDebug>
#include <QStringList>
CodeList::CodeList()
{
    head = new codeline(0,NULL);
}
void CodeList::insert_codeline(QString qs)
{

    int linenum= (qs.split(" ")[0]).toInt();
    std::string *s = new std::string(qs.split(" ")[1].toStdString());

    assert( linenum > 0);
    codeline *p = head;


    while(p->next)
    {

        if(p->next->linenum == linenum)
        {
            //replace
            p->next->code = s ;
            return;
        }
       if(p->next->linenum > linenum)
       {
           codeline * q = p->next;
           p->next = new codeline(linenum,s);
           p->next->next =q;

           qDebug()<<"INSERT!"<<endl;
           return;
       }

       p = p->next;
    }
    p->next = new codeline(linenum,s);
    qDebug()<<"INSERT!"<<endl;


}

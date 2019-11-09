#include "Command.h"
#include <QKeyEvent>
#include <QTextLine>
#include <QTextCursor>

#include <QTextEdit>

#include <QString>
Command::Command(QWidget *parent) : QTextEdit(parent)
{
    this->is_inputting_variable=false;
}

void Command::write(QString msg)
{
    this->append(msg);
}


void Command::keyPressEvent(QKeyEvent *event)
{
   if (event->key() == Qt::Key_Return) {
       QTextCursor cursor = this->textCursor();
       cursor.movePosition(QTextCursor::End);
       cursor.select(QTextCursor::LineUnderCursor);
       QString lastLine = cursor.selectedText();

       if(lastLine.size())
            process(lastLine);
    }
    QTextEdit::keyPressEvent(event);
}
void Command::process( QString s)
{
    if(is_inputting_variable)
    {
        //把这个值看看是不是INT，不是就报错
        bool ok;
        int input= s.toInt(&ok);
        if(!ok)
        {
            this->write("Input Error! "+ s +" is not an Interger!");
            return;
        }
        //是就用 signal传给RUNNER让runnner继续跑
        input_finish(input);
        return;
    }

    if(!s.compare("RUN"))
    {
            qDebug("RUN");
            run();
            return;
    }
    if(!s.compare("LIST"))
    {
        showCode();
           return;
    }
     if(!s.compare("CLEAR"))
     {
       this->clear();
        return;
     }
     if(!s.compare("HELP"))
     {
         this->write("available commands:RUN,LIST,CLEAR,HELP,QUIT. ");
         this->write("RUN:This command starts program execution beginning at the lowest-numbered line. ");
         this->write("LIST:This command lists the steps in the program in numerical sequence.");
         this->write("CLEAR This command deletes the program so the user can start entering a new one.");
         this->write("QUIT:Typing QUIT exits from the BASIC interpreter by calling exit(0). ");
         return;
     }
     if(!s.compare("QUIT"))
     {
        exit(0);
     }

      newLineWritten(s);

}

void Command::set_is_inputtiing_variable()
{
    this->is_inputting_variable = true;
}

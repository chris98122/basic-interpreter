#include "Command.h"
#include "Console.h"
#include <QKeyEvent>
#include <QTextLine>
#include <QTextCursor>

#include <QTextEdit>
Command::Command(QWidget *parent) : QTextEdit(parent)
{

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
       newLineWritten(lastLine);
       process(lastLine);
    }
    QTextEdit::keyPressEvent(event);
}
void Command::process( QString s)
{
    if(!s.compare("RUN"))
    {
            qDebug("RUN");
    }
    if(!s.compare("LIST"))
    {
    }
     if(!s.compare("CLEAR"))
     {

     }
     if(!s.compare("HELP"))
     {
         this->write("available commands:RUN,LIST,CLEAR,HELP,QUIT. ");
         this->write("RUN:This command starts program execution beginning at the lowest-numbered line. ");
         this->write("LIST:This command lists the steps in the program in numerical sequence.");
         this->write("CLEAR This command deletes the program so the user can start entering a new one.");
         this->write("QUIT:Typing QUIT exits from the BASIC interpreter by calling exit(0). ");

     }
     if(!s.compare("QUIT"))
     {
        exit(0);
     }
}
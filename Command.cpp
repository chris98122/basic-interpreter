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
    }
    QTextEdit::keyPressEvent(event);
}

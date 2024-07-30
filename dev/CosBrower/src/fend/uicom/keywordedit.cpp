#include "keywordedit.h"

keywordEdit::keywordEdit(QWidget* parent)
    :QLineEdit(parent)
{

}

// 不允许复制粘贴密码
void keywordEdit::keyPressEvent(QKeyEvent *event)
{
    // 捕获按键
    if(event->modifiers() == Qt::ControlModifier)
    {
        if(event->key() == Qt::Key_C || event->key() == Qt::Key_V)
            return;
    }
    QLineEdit::keyPressEvent(event);
}

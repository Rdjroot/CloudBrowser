#pragma warning
#ifndef KEYWORDEDIT_H
#define KEYWORDEDIT_H

#include <QLineEdit>
#include<QKeyEvent>

// 禁用密码框复制粘贴，需要集成QLineEdit
class keywordEdit : public QLineEdit
{
    Q_OBJECT
public:
    keywordEdit(QWidget* parent= nullptr);

protected:
    void keyPressEvent(QKeyEvent* event);
};

#endif // KEYWORDEDIT_H

#ifndef UIKEYWORDEDIT_H
#define UIKEYWORDEDIT_H

#include <QLineEdit>
#include<QKeyEvent>

// 禁用密码框复制粘贴，需要集成QLineEdit
class UiKeywordEdit : public QLineEdit
{
    Q_OBJECT
public:
    UiKeywordEdit(QWidget* parent= nullptr);

protected:
    void keyPressEvent(QKeyEvent* event);
};

#endif // UIKEYWORDEDIT_H

#ifndef UIKEYWORDEDIT_H
#define UIKEYWORDEDIT_H

#include <QLineEdit>
#include<QKeyEvent>

/**
 * @brief 禁用密码框复制功能
 */
class UiKeywordEdit : public QLineEdit
{
    Q_OBJECT
public:
    UiKeywordEdit(QWidget* parent= nullptr);

protected:
    /**
     * @brief 重写，不允许复制密码
     * @param event
     */
    void keyPressEvent(QKeyEvent* event);
};

#endif // UIKEYWORDEDIT_H

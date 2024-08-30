#ifndef UIPUSHBUTTON_H
#define UIPUSHBUTTON_H

#include <QObject>
#include <QPushButton>

/**
 * @brief 按钮设置特效
 */
class UiPushButton : public QPushButton
{
    Q_OBJECT
public:
    UiPushButton(QWidget* parent = nullptr);

protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
};

#endif // UIPUSHBUTTON_H

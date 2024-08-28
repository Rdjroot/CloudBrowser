#ifndef UIPUSHBUTTON_H
#define UIPUSHBUTTON_H

#include <QObject>
#include <QPushButton>

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

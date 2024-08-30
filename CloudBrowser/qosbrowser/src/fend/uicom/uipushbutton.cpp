#include "uipushbutton.h"

UiPushButton::UiPushButton(QWidget* parent): QPushButton(parent)
{

}

void UiPushButton::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
    setCursor(Qt::PointingHandCursor);      // 把鼠标放到这里，会显示小手
}

void UiPushButton::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    setCursor(Qt::ArrowCursor);
}

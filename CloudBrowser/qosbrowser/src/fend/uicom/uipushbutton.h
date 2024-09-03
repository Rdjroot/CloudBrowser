#ifndef UIPUSHBUTTON_H
#define UIPUSHBUTTON_H

#include <QObject>
#include <QPushButton>

/**
 * @brief 全局按钮控件
 *
 * 放置特效（小手）
 *
 */
class UiPushButton : public QPushButton
{
    Q_OBJECT
public:
    UiPushButton(QWidget* parent = nullptr);

protected:
    /**
     * @brief 放置变小手特效
     * @param event
     */
    void enterEvent(QEvent *event) override;

    /**
     * @brief 离开变回箭头
     * @param event
     */
    void leaveEvent(QEvent *event) override;
};

#endif // UIPUSHBUTTON_H

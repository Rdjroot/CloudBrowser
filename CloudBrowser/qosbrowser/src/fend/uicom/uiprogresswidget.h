#ifndef UIPROGRESSWIDGET_H
#define UIPROGRESSWIDGET_H

#include <QElapsedTimer>
#include <QWidget>

namespace Ui {
class UiProgressWidget;
}

/**
 * @brief 数据传输进度条控件
 *
 */
class UiProgressWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UiProgressWidget(QWidget *parent = nullptr);
    ~UiProgressWidget();

    /**
     * @brief 设置总大小
     * @param minValue  最小值
     * @param maxValue  最大值
     */
    void setRange(qulonglong minValue, qulonglong maxValue);
    /**
     * @brief 设置进度条当前值
     * @param value
     */
    void setValue(qulonglong value);

    /**
     * @brief 传输停止
     */
    void stop();
    /**
     * @brief 进度条满
     * @param msg
     */
    void setFinished(const QString& msg);

    /**
     * @brief 发生错误
     * @param msg
     */
    void setError(const QString& msg);

private:
    Ui::UiProgressWidget *ui;

    // 用于测量时间间隔
    // 提供了一种高精度的方式来计算从某个时间点到现在所经过的时间
    QElapsedTimer m_time;
};

#endif // UIPROGRESSWIDGET_H

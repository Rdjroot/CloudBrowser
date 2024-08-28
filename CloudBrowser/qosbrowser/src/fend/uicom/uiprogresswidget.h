#ifndef UIPROGRESSWIDGET_H
#define UIPROGRESSWIDGET_H

#include <QElapsedTimer>
#include <QWidget>

namespace Ui {
class UiProgressWidget;
}

/**
 * @brief 进度条展示
 */
class UiProgressWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UiProgressWidget(QWidget *parent = nullptr);
    ~UiProgressWidget();

    void setRange(qulonglong minValue, qulonglong maxValue);
    void setValue(qulonglong value);

    void stop();
    void setFinished(const QString& msg);
    void setError(const QString& msg);

private:
    Ui::UiProgressWidget *ui;
    // 用于测量时间间隔。提供了一种高精度的方式来计算从某个时间点到现在所经过的时间
    QElapsedTimer m_time;
};

#endif // UIPROGRESSWIDGET_H

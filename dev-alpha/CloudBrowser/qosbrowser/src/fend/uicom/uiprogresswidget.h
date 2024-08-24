#ifndef UIPROGRESSWIDGET_H
#define UIPROGRESSWIDGET_H

#include <QElapsedTimer>
#include <QWidget>

namespace Ui {
class UiProgressWidget;
}

/**
 * @brief 传输进度条
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
    QElapsedTimer m_time;       // 计时
};

#endif // UIPROGRESSWIDGET_H

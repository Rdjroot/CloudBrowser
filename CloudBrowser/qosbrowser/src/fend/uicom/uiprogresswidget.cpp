#include "uiprogresswidget.h"
#include "qdebug.h"
#include "ui_uiprogresswidget.h"

#include <QTimer>

#include <src/helper/bytehelper.h>

UiProgressWidget::UiProgressWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiProgressWidget)
{
    ui->setupUi(this);
}

UiProgressWidget::~UiProgressWidget()
{
    delete ui;
}

/**
 * @brief 设置总大小
 * @param minValue  最小值
 * @param maxValue  最大值
 */
void UiProgressWidget::setRange(qulonglong minValue, qulonglong maxValue)
{
    m_time.restart();
    ui->progressBar->setRange(minValue, maxValue);
    ui->progressBar->setValue(0);       // 当前值
}

/**
 * @brief 设置进度条当前值
 * @param value
 */
void UiProgressWidget::setValue(qulonglong value)
{
    double seconds = m_time.elapsed()/1000.0; // 已经过去的时间
    ui->progressBar->setValue(value);

    static qulonglong lastValue = 0; // 上一次设置值时的上传或下载的字节数
    lastValue = value - lastValue;
    double speed = lastValue/seconds;
    QString speedStr = ByteHelper::toBeautifulStr(speed);
    ui->labelSpeed->setText(speedStr+"/s");

    int leftValue = ui->progressBar->maximum()-value; // 未下载的字节数
    if (speed > 0 && leftValue > 0)
    {
        int time = leftValue/speed;     // 预计剩余下载时间
        ui->labelTime->setText(QString::fromLocal8Bit("剩余%1s").arg(time));
    }
    else
    {
        ui->labelTime->setText("");
    }
}

/**
 * @brief 停止下载
 */
void UiProgressWidget::stop()
{
    m_time.invalidate();
    ui->labelSpeed->clear();
}

/**
 * @brief 进度条圆满
 * @param msg
 */
void UiProgressWidget::setFinished(const QString &msg)
{
    setValue(ui->progressBar->maximum());
    ui->labelTime->setText(msg);
    stop();
}

/**
 * @brief 发生错误          TODO: 我怀疑这里有bug，如果出错是否会造成卡死
 * @param msg
 */
void UiProgressWidget::setError(const QString &msg)
{
    stop();
    ui->labelTime->setText(msg);
}


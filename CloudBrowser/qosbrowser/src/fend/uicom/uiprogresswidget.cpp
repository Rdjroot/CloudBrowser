#include "uiprogresswidget.h"
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


void UiProgressWidget::setRange(qulonglong minValue, qulonglong maxValue)
{
    m_time.restart();               // 重启计时
    ui->progressBar->setRange(minValue, maxValue);
    ui->progressBar->setValue(0);       // 当前值
}


void UiProgressWidget::setValue(qulonglong value)
{
    double seconds = m_time.elapsed()/1000.0; // 已经过去的时间
    ui->progressBar->setValue(value);

    static qulonglong lastValue = 0;    // 上一次设置值时的上传或下载的字节数
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

void UiProgressWidget::stop()
{
    m_time.invalidate();        // 将时间置为非法
    ui->labelSpeed->clear();
}


void UiProgressWidget::setFinished(const QString &msg)
{
    setValue(ui->progressBar->maximum());
    ui->labelTime->setText(msg);
    stop();
}


void UiProgressWidget::setError(const QString &msg)
{
    stop();
    ui->labelTime->setText(msg);
}


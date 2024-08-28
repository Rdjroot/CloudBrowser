#ifndef UITOOLWIDGET_H
#define UITOOLWIDGET_H

#include <QWidget>
#include<QFileDialog>
#include<QDebug>
#include<QSignalMapper>
namespace Ui {
class UiToolWidget;
}

// 工具栏
class UiToolWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UiToolWidget(QWidget *parent = nullptr);
    ~UiToolWidget();

signals:
    void quitLogin();           // 退出登录
    void buttonClicked(const QString& text);        // 统一按键发出的信号

private slots:
    void on_btnUpload_clicked();

    void on_btnDownload_clicked();

    void on_btnQuit_clicked();

private:
    Ui::UiToolWidget *ui;
};

#endif // UITOOLWIDGET_H

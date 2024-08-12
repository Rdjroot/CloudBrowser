#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>
#include<QFileDialog>
#include<QDebug>
#include<QSignalMapper>
namespace Ui {
class ToolWidget;
}

// 工具栏
class ToolWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolWidget(QWidget *parent = nullptr);
    ~ToolWidget();

signals:
    void quitLogin();           // 退出登录
    void buttonClicked(const QString& text);        // 统一按键发出的信号

private slots:
    void on_btnUpload_clicked();

    void on_btnDownload_clicked();

    void on_btnQuit_clicked();

private:
    Ui::ToolWidget *ui;
};

#endif // TOOLWIDGET_H

#ifndef TOOLWIDGET_H
#define TOOLWIDGET_H

#include <QWidget>
#include<QFileDialog>
#include<QDebug>

namespace Ui {
class ToolWidget;
}

class ToolWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToolWidget(QWidget *parent = nullptr);
    ~ToolWidget();

signals:
    void quitLogin();

private slots:
    void on_btnUpload_clicked();

    void on_btnDownload_clicked();

private:
    Ui::ToolWidget *ui;
};

#endif // TOOLWIDGET_H

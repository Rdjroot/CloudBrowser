#ifndef BREADWIDGET_H
#define BREADWIDGET_H

#include <QWidget>

namespace Ui {
class BreadWidget;
}

// 界面存储桶
class BreadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BreadWidget(QWidget *parent = nullptr);
    ~BreadWidget();

private:
    Ui::BreadWidget *ui;
};

#endif // BREADWIDGET_H

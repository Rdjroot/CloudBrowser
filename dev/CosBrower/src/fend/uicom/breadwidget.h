#ifndef BREADWIDGET_H
#define BREADWIDGET_H

#include <QWidget>

namespace Ui {
class BreadWidget;
}

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

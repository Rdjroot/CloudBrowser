#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H

#include <QWidget>

namespace Ui {
class PageWidget;
}

class PageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PageWidget(QWidget *parent = nullptr);
    ~PageWidget();

private:
    Ui::PageWidget *ui;
};

#endif // PAGEWIDGET_H

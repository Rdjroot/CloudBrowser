#ifndef UIOBJECTSWIDGET_H
#define UIOBJECTSWIDGET_H

#include <QWidget>
#include<src/bend/man/mancloud.h>

namespace Ui {
class UiObjectsWidget;
}

// 右边展示内容模块
class UiObjectsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UiObjectsWidget(QWidget *parent = nullptr);
    ~UiObjectsWidget();

private:
    Ui::UiObjectsWidget *ui;
};

#endif // UIOBJECTSWIDGET_H

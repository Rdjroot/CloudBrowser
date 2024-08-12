#ifndef OBJECTSWIDGET_H
#define OBJECTSWIDGET_H

#include <QWidget>
#include<src/bend/man/mancloud.h>

namespace Ui {
class ObjectsWidget;
}

// 右边展示内容模块
class ObjectsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ObjectsWidget(QWidget *parent = nullptr);
    ~ObjectsWidget();

private:
    Ui::ObjectsWidget *ui;
};

#endif // OBJECTSWIDGET_H

#ifndef OBJECTSWIDGET_H
#define OBJECTSWIDGET_H

#include <QWidget>

namespace Ui {
class ObjectsWidget;
}

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

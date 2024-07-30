#include "objectswidget.h"
#include "ui_objectswidget.h"

ObjectsWidget::ObjectsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ObjectsWidget)
{
    ui->setupUi(this);
}

ObjectsWidget::~ObjectsWidget()
{
    delete ui;
}

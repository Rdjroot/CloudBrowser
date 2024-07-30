#include "breadwidget.h"
#include "ui_breadwidget.h"

BreadWidget::BreadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BreadWidget)
{
    ui->setupUi(this);
}

BreadWidget::~BreadWidget()
{
    delete ui;
}

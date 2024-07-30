#include "cosbrowser.h"
#include "ui_cosbrowser.h"

CosBrowser::CosBrowser(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CosBrowser)
{
    ui->setupUi(this);
}

CosBrowser::~CosBrowser()
{
    delete ui;
}


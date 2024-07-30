#include "uimain.h"
#include "ui_uimain.h"

UiMain::UiMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiMain)
{
    ui->setupUi(this);
}

UiMain::~UiMain()
{
    delete ui;
}

#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint);        // 去掉默认标题栏

    QPixmap icontt(":/image/image/icontt.png");
    ui->logoLabel->setPixmap(icontt.scaled(ui->logoLabel->size()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}


void LoginDialog::on_closeButton_clicked()
{
    close();
}

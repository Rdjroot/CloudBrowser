#include "uicreatebucketdialog.h"
#include "ui_uicreatebucketdialog.h"


UiCreateBucketDialog::UiCreateBucketDialog(QWidget *parent)
    : UiQosDialog(parent),
    ui(new Ui::UiCreateBucketDialog)
{
    ui->setupUi(body());
    ui->btnOk->setProperty("style_button", "main");
    connect(ui->btnOk,&UiPushButton::clicked, this, &UiCreateBucketDialog::accept);
    connect(ui->btnCancel, &UiPushButton::clicked, this, &UiCreateBucketDialog::reject);
}

UiCreateBucketDialog::~UiCreateBucketDialog()
{
    delete ui;
}


MyBucket UiCreateBucketDialog::getBucket()
{
    MyBucket bucket;
    bucket.name = ui->lineName->text().trimmed();
    bucket.location = ui->lineLocation->text().trimmed();
    return bucket;
}



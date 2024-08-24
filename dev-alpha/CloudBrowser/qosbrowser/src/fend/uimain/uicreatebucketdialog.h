#ifndef UICREATEBUCKETDIALOG_H
#define UICREATEBUCKETDIALOG_H

#include "src/fend/uicom/uiqosdialog.h"
#include "src/middle/models/cloudmodels.h"

namespace Ui {
class UiCreateBucketDialog;
}

class UiCreateBucketDialog : public UiQosDialog
{
    Q_OBJECT

public:
    explicit UiCreateBucketDialog(QWidget *parent = nullptr);
    ~UiCreateBucketDialog();

    MyBucket getBucket();

private:
    Ui::UiCreateBucketDialog *ui;
};

#endif // UICREATEBUCKETDIALOG_H

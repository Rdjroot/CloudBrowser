#ifndef UICREATEBUCKETDIALOG_H
#define UICREATEBUCKETDIALOG_H

#include "src/fend/uicom/uiqosdialog.h"
#include "src/middle/models/cloudmodels.h"

namespace Ui {
class UiCreateBucketDialog;
}

/**
 * @brief 创建桶的窗口
 */
class UiCreateBucketDialog : public UiQosDialog
{
    Q_OBJECT

public:
    explicit UiCreateBucketDialog(QWidget *parent = nullptr);
    ~UiCreateBucketDialog();

    /**
     * @brief 获取桶信息
     * @return 返回创建桶的内容
     */
    MyBucket getBucket();

private:
    Ui::UiCreateBucketDialog *ui;
};

#endif // UICREATEBUCKETDIALOG_H

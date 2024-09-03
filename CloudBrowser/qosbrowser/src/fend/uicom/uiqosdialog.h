#ifndef UIQOSDIALOG_H
#define UIQOSDIALOG_H

#include "uibasedialog.h"

namespace Ui {
class UiQosDialog;
}

/**
 * @brief 全局小窗口
 *
 * 用于报错信息、提示等
 *
 */
class UiQosDialog : public UiBaseDialog
{
    Q_OBJECT

public:
    explicit UiQosDialog(QWidget *parent = nullptr);
    ~UiQosDialog();

private:
    Ui::UiQosDialog *ui;
};

#endif // UIQOSDIALOG_H

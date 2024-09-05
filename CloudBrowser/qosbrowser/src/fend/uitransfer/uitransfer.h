#ifndef UITRANSFER_H
#define UITRANSFER_H

#include <QWidget>

#include <src/fend/uicom/uiqosdialog.h>

namespace Ui {
class UiTransfer;
}

/**
 * @brief 传输窗口
 *
 * 含上传、下载记录和进度
 *
 */
class UiTransfer : public UiQosDialog
{
    Q_OBJECT

public:
    explicit UiTransfer(QWidget *parent = nullptr);
    ~UiTransfer();

private:
    Ui::UiTransfer *ui;
};

#endif // UITRANSFER_H

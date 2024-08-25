#ifndef UIMAIN_H
#define UIMAIN_H

#include "src/middle/models/cloudmodels.h"
#include <QDebug>
#include <QWidget>

#include <src/fend/uicom/uiqosdialog.h>

namespace Ui {
class UiMain;
}

class UiLoginDialog;

// 主界面
class UiMain : public UiQosDialog {
    Q_OBJECT

public:
    explicit UiMain(QWidget *parent = nullptr);
    ~UiMain();

private slots:
    void onUnLogin();
    void onBucketsSuccess(const QList<MyBucket>& buckets);
    void onObjectsSuccess(const QList<MyObject>& objcets);
    void showTransfer();
    void onError(int api, const QString& msg, const QJsonValue &req);

private:
    Ui::UiMain *ui;
};

#endif // UIMAIN_H

#ifndef UIMAIN_H
#define UIMAIN_H

#include "src/fend/uitransfer/uitransfer.h"
#include "src/middle/models/cloudmodels.h"
#include <QDebug>
#include <QWidget>

#include <src/fend/uicom/uiqosdialog.h>

namespace Ui {
class UiMain;
}

class UiLoginDialog;

/**
 * @brief 云存储浏览器主界面
 *
 */
class UiMain : public UiQosDialog {
    Q_OBJECT

public:
    explicit UiMain(QWidget *parent = nullptr);
    ~UiMain();

private slots:
    /**
     * @brief 退出登录
     */
    void onUnLogin();

    /**
     * @brief 显示桶表窗体
     * @param buckets 桶列表
     */
    void onBucketsSuccess(const QList<MyBucket>& buckets);

    /**
     * @brief 显示对象表窗体
     * @param objcets 对象列表
     */
    void onObjectsSuccess(const QList<MyObject>& objcets);

    /**
     * @brief 文件传输窗口
     */
    void showTransfer();

    /**
     * @brief 弹出报错窗口
     * @param api 接口
     * @param msg 报错信息
     * @param req 请求头
     */
    void onError(int api, const QString& msg, const QJsonValue &req);

private:
    Ui::UiMain *ui;
    UiTransfer *m_transfer = nullptr;
};

#endif // UIMAIN_H

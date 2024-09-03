#ifndef UIMESSAGEBOX_H
#define UIMESSAGEBOX_H

#include "uiqosdialog.h"
#include <QWidget>

namespace Ui {
class UiMessageBox;
}

/**
 * @brief 自定义信息提示框
 *
 */
class UiMessageBox : public UiQosDialog
{
    Q_OBJECT

public:
    explicit UiMessageBox(QWidget *parent = nullptr);
    ~UiMessageBox();

    /**
     * @brief 展示提示窗口
     * @param title 标题
     * @param text 内容
     * @param btnTextList  按键list
     * @param weight 宽
     * @param height 高
     * @return 内容
     */
    QString showMessage(const QString& title,
                        const QString& text,
                        const QStringList &btnTextList = QStringList(QString::fromLocal8Bit("确定")),
                        const int weight = 400,
                        const int height = 50);

private:
    /**
     * @brief 创建窗体按钮
     * @param textList  信息列表
     */
    void createBtns(const QStringList& textList);

private:
    Ui::UiMessageBox *ui;
    QString m_text;
};

#endif // UIMESSAGEBOX_H

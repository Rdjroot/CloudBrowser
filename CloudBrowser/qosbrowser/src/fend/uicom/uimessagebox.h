#ifndef UIMESSAGEBOX_H
#define UIMESSAGEBOX_H

#include "uiqosdialog.h"
#include <QWidget>

namespace Ui {
class UiMessageBox;
}

class UiMessageBox : public UiQosDialog
{
    Q_OBJECT

public:
    explicit UiMessageBox(QWidget *parent = nullptr);
    ~UiMessageBox();

    QString showMessage(const QString& title,
                        const QString& text,
                        const QStringList &btnTextList = QStringList(QString::fromLocal8Bit("确定")));

private:
    void createBtns(const QStringList& textList);

private:
    Ui::UiMessageBox *ui;
    QString m_text;
};

#endif // UIMESSAGEBOX_H

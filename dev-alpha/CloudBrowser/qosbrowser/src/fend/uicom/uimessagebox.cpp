#include "uimessagebox.h"
#include "ui_uimessagebox.h"

#include <QPushButton>

UiMessageBox::UiMessageBox(QWidget *parent)
    : UiQosDialog(parent)
    , ui(new Ui::UiMessageBox)
{
    ui->setupUi(body());
}

UiMessageBox::~UiMessageBox()
{
    delete ui;
}

/**
 * @brief 展示提示框
 * @param title  标题
 * @param text   内容
 * @param btnTextList  可选按钮
 * @return
 */
QString UiMessageBox::showMessage(const QString &title, const QString &text, const QStringList &btnTextList)
{
    m_text = "";
    setTitle(title);
    ui->label->setText(text);
    createBtns(btnTextList);
    exec();
    return m_text;
}

/**
 * @brief 创建提示窗口按钮
 * @param textList
 */
void UiMessageBox::createBtns(const QStringList &textList)
{
    for(const auto& text: qAsConst(textList))
    {
        QPushButton* btn = new QPushButton(text, this);
        connect(btn, &QPushButton::clicked, [=](){
            m_text = text;
            accept();
        });
        ui->horizontalLayout->addWidget(btn);
    }
}

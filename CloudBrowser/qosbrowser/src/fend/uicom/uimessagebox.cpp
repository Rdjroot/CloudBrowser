#include "uimessagebox.h"
#include "ui_uimessagebox.h"
#include "src/fend/uicom/uipushbutton.h"
#include <QPushButton>

UiMessageBox::UiMessageBox(QWidget *parent) :
    UiQosDialog(parent),
    ui(new Ui::UiMessageBox)
{
    ui->setupUi(body());
}

UiMessageBox::~UiMessageBox()
{
    delete ui;
}

QString UiMessageBox::showMessage(const QString &title, const QString &text, const QStringList &btnTextList, const int weight, const int height)
{
    // 确保每次调用都清空之前的内容
    m_text.clear();
    resize(weight, height);     // 重新设置大小
    setTitle(title);
    ui->label->setText(text);
    // 创建按钮
    createBtns(btnTextList);
    // 显示对话框并等待用户交互
    exec();
    return m_text;
}

void UiMessageBox::createBtns(const QStringList &textList)
{
    for(const auto& text: qAsConst(textList)) {
        UiPushButton* btn = new UiPushButton(this);
        btn->setText(text);
        connect(btn, &UiPushButton::clicked, [=]() {
            m_text = text;
            accept();
        });
        ui->horizontalLayout->addWidget(btn);
    }
}

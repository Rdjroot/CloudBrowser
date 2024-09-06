#include "uiqosdialog.h"
#include "ui_uibasedialog.h"
#include "ui_uiqosdialog.h"
#include "src/config/globals.h"

UiQosDialog::UiQosDialog(QWidget *parent)
    : UiBaseDialog(parent)
    , ui(new Ui::UiQosDialog)
{
    ui->setupUi(body());
    setLogo(GLOBAL::PATH::LOGO_PATH);   // 设置图标
    setTitle("CloudBrowser");           // 设置程序名称
    m_ui->labelLogo->setFixedSize(40,40);
    m_ui->labelTitle->setProperty("style_font", "h4");
    this->setWindowIcon(QIcon(":/static/img/icontt.ico"));
    resize(400, 50);                    // 设置大小
}

UiQosDialog::~UiQosDialog()
{
    delete ui;
}

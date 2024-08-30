#include "uiqosdialog.h"
#include "ui_uibasedialog.h"
#include "ui_uiqosdialog.h"
#include "src/config/globals.h"

UiQosDialog::UiQosDialog(QWidget *parent)
    : UiBaseDialog(parent)
    , ui(new Ui::UiQosDialog)
{
    ui->setupUi(body());
    setLogo(GLOBAL::PATH::LOGO_PATH);
    setTitle("CloudBrowser");
    m_ui->labelLogo->setFixedSize(40,40);
    m_ui->labelTitle->setProperty("style_font", "h4");
    resize(400, 50);
}

UiQosDialog::~UiQosDialog()
{
    delete ui;
}

#include "toolwidget.h"
#include "ui_toolwidget.h"

ToolWidget::ToolWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolWidget)
{
    ui->setupUi(this);
    connect(ui->btnQuit, &QPushButton::clicked, this, &ToolWidget::quitLogin);
}

ToolWidget::~ToolWidget()
{
    delete ui;
}

void ToolWidget::on_btnUpload_clicked()
{
    // 上传单个文件
    QString path = QFileDialog::getOpenFileName(this, "上传","./");

    // 上传多个文件
    QStringList pathList = QFileDialog::getOpenFileNames(this,"上传","./");

    // 上传指定类型文件
    QStringList pathListDIY = QFileDialog::getOpenFileNames(
                this,
                "上传",
                "./",
                "hpp (*.h*.cpp);;MakeFile (*.Release *.Debug)");

    // 上传 文件夹
    QString pathFoloder = QFileDialog::getExistingDirectory(
                this,
                "上传",
                "./");
}

void ToolWidget::on_btnDownload_clicked()
{
    // 下载文件
    QString path = QFileDialog::getSaveFileName(this, "下载","./");
}

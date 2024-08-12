#include "toolwidget.h"
#include "src/middle/signals/mansignals.h"
#include "ui_toolwidget.h"

ToolWidget::ToolWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolWidget)
{
    ui->setupUi(this);
    // connect(ui->btnQuit, &QPushButton::clicked, this, &ToolWidget::quitLogin);

    // QSignalMapper *mapper = new QSignalMapper(this);                // 设置mapper
    // QList<QPushButton*> buttonList = findChildren<QPushButton*>();      // 查找这个界面所有的按钮
    // for(auto *btn: buttonList)
    // {
    //     connect(btn, SIGNAL(clicked()),mapper,SLOT(map()));
    //     mapper->setMapping(btn, btn->text());               // 键值对：{按钮对象的指针，按钮上的文字}
    // }

    // // 当任意一个按钮被点击时，buttonClicked(QString)信号会携带按钮的文字作为参数进行发送
    // // buttonClicked(QString)这里是被转为了信号
    // connect(mapper,SIGNAL(mapped(QString)),this,SIGNAL(buttonClicked(QString)));
}

ToolWidget::~ToolWidget()
{
    delete ui;
}

void ToolWidget::on_btnUpload_clicked()
{
    // 上传单个文件
    QString path = QFileDialog::getOpenFileName(this, "上传","./");

//    // 上传多个文件
//    QStringList pathList = QFileDialog::getOpenFileNames(this,"上传","./");

//    // 上传指定类型文件
//    QStringList pathListDIY = QFileDialog::getOpenFileNames(
//                this,
//                "上传",
//                "./",
//                "hpp (*.h*.cpp);;MakeFile (*.Release *.Debug)");

//    // 上传 文件夹
//    QString pathFoloder = QFileDialog::getExistingDirectory(
//                this,
//                "上传",
//                "./");
}

void ToolWidget::on_btnDownload_clicked()
{
    // 下载文件
    QString path = QFileDialog::getSaveFileName(this, "下载","./");
}

// 退出登录
void ToolWidget::on_btnQuit_clicked()
{
    emit MS->unLogin();
}


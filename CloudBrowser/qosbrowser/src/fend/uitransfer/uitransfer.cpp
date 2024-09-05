#include "uitransfer.h"
#include "src/config/common.h"
#include "ui_uitransfer.h"

UiTransfer::UiTransfer(QWidget *parent) :
    UiQosDialog(parent),
    ui(new Ui::UiTransfer)
{
    ui->setupUi(body());
    setTitle(STR("传输列表"));  // 标题
    setFixedSize(600, 450);     // 大小
}

UiTransfer::~UiTransfer()
{
    delete ui;
}

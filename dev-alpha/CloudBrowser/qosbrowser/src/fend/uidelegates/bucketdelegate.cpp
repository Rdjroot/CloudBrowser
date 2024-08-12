#include "bucketdelegate.h"
#include <QComboBox>
#include<QDebug>

BucketDelegate::BucketDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{

}

// 创建下拉框中的内容
QWidget *BucketDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // 下拉框可选项
    QComboBox* box = new QComboBox(parent);         // 下拉框选择完即会销毁
    box->addItem("ap-beijing");
    box->addItem("ap-shanghai");
    box->addItem("ap-guangzhou");
    box->setFrame(false);
//    QObject::connect(box, SIGNAL(destroyed(QObject*)),this, SLOT(comboxDestroy(QObject*)));
    return box;
}

// 设置选中的文本内容
void BucketDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    // 设置文本
    QComboBox* box = static_cast<QComboBox*>(editor);
    QString text = index.data(Qt::EditRole).toString();
    box->setCurrentText(text);
}

// 获取内容
void BucketDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    // 设置模型的数据
    QComboBox* box = static_cast<QComboBox*>(editor);
    model->setData(index, box->currentText());
}

// 下拉框选择完即会销毁，这里是用于测试的
void BucketDelegate::comboxDestroy(QObject *)
{
    qDebug() << "comboBox Destyoed";
}

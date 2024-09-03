#include "uibreadwidget.h"
#include "ui_uibreadwidget.h"
#include <QDebug>

UiBreadWidget::UiBreadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiBreadWidget)
{
    ui->setupUi(this);
    ui->listView->setModel(m_model);
    ui->listView->setFlow(QListView::LeftToRight);
    ui->listView->setCursor(Qt::PointingHandCursor); // 放置变小手

    connect(ui->listView, &QListView::clicked, this,
            &UiBreadWidget::onItemClicked);
    setPath("");
    setFixedHeight(30); // 设置窗体高度
}

UiBreadWidget::~UiBreadWidget()
{
    delete ui;
}

void UiBreadWidget::setPath(const QString &path)
{
    setPath(path.split("/", Qt::SkipEmptyParts));
}

void UiBreadWidget::setPath(const QStringList &names)
{
    // 传入的目录名称不能为空
    if (names.size() == 0) {
        return;
    }
    clear();
    m_rootName = names[0];
    for (const QString &name : names) {
        addNameButton(name.trimmed()); // 按个添加button
    }
}

void UiBreadWidget::clear()
{
    m_model->clear();
}

QString UiBreadWidget::currentPath() const
{
    return getPath();
}

QString UiBreadWidget::rootName() const
{
    return m_rootName;
}

bool UiBreadWidget::isEmpty() const
{
    return (ui->listView->model()->rowCount() == 0);
}

bool UiBreadWidget::isRoot() const
{
    return getPath() == m_rootName;
}

void UiBreadWidget::addNameButton(const QString &name)
{
    if(name == "")
        return;
    QStandardItem *item = new QStandardItem;
    item->setText(name);

    if(!isEmpty())
    {
        item->setIcon(QIcon(":/static/img/right.png")); // 向右箭头
    }

    m_model->appendRow(item);
}

void UiBreadWidget::onItemClicked(const QModelIndex &index)
{
    QStandardItem* newItem = m_model->itemFromIndex(index);
    QStandardItem* oldItem = currentItem();

    if(newItem == oldItem)
    {
        QString oldPath = getPath(oldItem);
        emit refresh(oldPath);
    }
    else{
        QString newPath = getPath(newItem);
        emit pathChanged(newPath);
    }
}

QStandardItem *UiBreadWidget::currentItem() const
{
    return m_model->item(m_model->rowCount()-1);
}

QString UiBreadWidget::getPath(QStandardItem *item) const
{
    if(!item)
    {
        item = currentItem();
    }

    int idx = item->row();
    QStringList pathList;
    for(int i = 0; i <= idx; i++)
    {
        QStandardItem* b = m_model->item(i);
        if(b){
            pathList << b->text();
        }
    }
    return pathList.join("/");
}

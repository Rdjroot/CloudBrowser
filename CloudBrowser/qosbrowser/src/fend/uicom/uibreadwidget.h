#ifndef UIBREADWIDGET_H
#define UIBREADWIDGET_H

#include <QStandardItem>
#include <QWidget>

namespace Ui {
class UiBreadWidget;
}

/**
 * @brief 面包屑导航，显示进入到存储桶几层目录下了
 */
class UiBreadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UiBreadWidget(QWidget *parent = nullptr);
    ~UiBreadWidget();

    // 设置路径， 可通过完整路径设置，也可通过名称列表设置
    void setPath(const QString& path);
    void setPath(const QStringList& names);
    void clear();

    // 获取当前路径
    QString currentPath() const;
    // 获取根目录名称
    QString rootName() const;

    // 判断当前路径是否为空
    bool isEmpty() const;
    // 判断路径是否根目录
    bool isRoot() const;

signals:
    void refresh(const QString& path);
    void pathChanged(const QString& newPath);

private:
    // 添加一块面包屑，即添加一个按钮
    void addNameButton(const QString& name);
    // 当点击某个面包屑时，把它后面的面包屑全部删除
    void onItemClicked(const QModelIndex &index);
    // 当前item，即为叶子结点
    QStandardItem *currentItem() const;
    // 根据item获取，item到根节点的路径
    QString getPath(QStandardItem *item=nullptr) const;

private:
    Ui::UiBreadWidget *ui;
    /**
     * 根目录必须存在，使用m_rootName存储根目录，用model存储所有目录名称列表
     */
    QString m_rootName;
    QStandardItemModel* m_model = new QStandardItemModel();
};

#endif // UIBREADWIDGET_H

#ifndef UITABLEITEMDELEGATE_H
#define UITABLEITEMDELEGATE_H

#include <QAbstractItemView>
#include <QObject>
#include <QStyledItemDelegate>

/**
 * @brief 自定义视图代理类
 *
 * 自定义表格悬停特效
 *
 */
class UiTableItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    UiTableItemDelegate(QAbstractItemView *table,QObject *parent = nullptr);

    /**
     * @brief 鼠标悬停 整行高亮
     * @param painter 绘图工具
     * @param option  绘制选项
     * @param index   iTem索引
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    //指明被代理的View,方便获取整行的item
    QAbstractItemView *m_table;
};

#endif // UITABLEITEMDELEGATE_H

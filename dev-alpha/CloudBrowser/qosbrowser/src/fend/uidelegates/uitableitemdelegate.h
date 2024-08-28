#ifndef UITABLEITEMDELEGATE_H
#define UITABLEITEMDELEGATE_H

#include <QAbstractItemView>
#include <QObject>
#include <QStyledItemDelegate>

class UiTableItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
     UiTableItemDelegate(QAbstractItemView *table,QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    //指明被代理的View,方便获取整行的item
    QAbstractItemView *m_table;
};

#endif // UITABLEITEMDELEGATE_H

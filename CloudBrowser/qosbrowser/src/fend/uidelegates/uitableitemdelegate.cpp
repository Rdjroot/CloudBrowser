#include "uitableitemdelegate.h"

UiTableItemDelegate::UiTableItemDelegate(QAbstractItemView *table, QObject *parent):
    QStyledItemDelegate(parent),
    m_table(table)
{

}

void UiTableItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    // 鼠标悬停 && 索引有效
    if(option.state.testFlag(QStyle::State_MouseOver) && index.isValid())
    {
        // 获取当前行的所有项的矩形区域
        QAbstractItemModel *m = m_table->model();
        int row = index.row();
        int columnCount = m->columnCount();

        for(int i = 0; i < columnCount; i++)
        {
            QModelIndex idx = m->index(row, i);
            QStyleOptionViewItem op = option;
            op.index = idx;
            // 对这些区域进行绘制
            op.rect = m_table->visualRect(idx);
            QStyledItemDelegate::paint(painter, op, idx);
        }
        return ;
    }
    return QStyledItemDelegate::paint(painter, option, index);
}

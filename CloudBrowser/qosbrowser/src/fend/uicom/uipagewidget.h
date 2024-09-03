#ifndef UIPAGEWIDGET_H
#define UIPAGEWIDGET_H

#include <QWidget>

namespace Ui {
class UiPageWidget;
}

/**
 * 底部翻页控件
 *
 */
class UiPageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UiPageWidget(QWidget *parent = nullptr);
    ~UiPageWidget();

    // 总条数
    int totalRow() const;
    // 单页最大行数
    int maxRow() const;
    // 当前页数
    int currentPage() const;
    // 总页数
    int pageCount() const;
    // 是否为首页
    int isFirstPage() const;
    // 是否为末页
    int isLastPage() const;

    // 设置总条数，以下两个方法会触发reset
    void setTotalRow(int newTotalRow);

    // 设置单页最大显示行数
    void setMaxRow(int rows);

    // 设置单页显示行数选择列表，属于初始化部分
    void setMaxRowList(const QList<int> rowList);

signals:
    // 页码发生变化， start-起始索引 len-每页最大条数
    void pageNumChanged(int start, int maxlen);

public slots:
    // 翻下一页
    void next();
    // 回到前一页
    void pre();
    // 跳转页面
    void jumpTo(int page);

private slots:
    // 选择页码
    void onCurrentPageSelected(const QString& text);
    // 选择每页最大行数
    void onMaxRowsItemSelected(const QString& text);

private:
    // 设置行数显示方式
    void setPageCount();
    // 重置为首页
    void reset();
    // 切换页面
    void switchPage(int newCurrentPage);

private:
    Ui::UiPageWidget *ui;
    int m_totalRow = 0;         // 总条数
    int m_currentPage = 1;      // 当前页码
    int m_maxRow = 10;          // 单页最大行数
};

#endif // UIPAGEWIDGET_H

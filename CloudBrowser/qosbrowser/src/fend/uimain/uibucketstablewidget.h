#ifndef UIBUCKETSTABLEWIDGET_H
#define UIBUCKETSTABLEWIDGET_H

#include "src/middle/models/cloudmodels.h"
#include <QWidget>

namespace Ui {
class UiBucketsTableWidget;
}

class UiBucketsTableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UiBucketsTableWidget(QWidget *parent = nullptr);
    ~UiBucketsTableWidget();

private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

    void onBucketsSuccess(const QList<MyBucket> &buckets);
    void onPageNumChanged(int start, int maxLen);

    void on_btnCreateBucket_clicked();
    void onDelBucket();
    void on_btnRefresh_clicked();

private:
    Ui::UiBucketsTableWidget *ui;
};

#endif // UIBUCKETSTABLEWIDGET_H

#ifndef UIDOWNLOAD_H
#define UIDOWNLOAD_H

#include "src/fend/uicom/uiprogresswidget.h"
#include <QWidget>

namespace Ui {
class UiDownload;
}

class UiDownload : public QWidget {
    Q_OBJECT

public:
    explicit UiDownload(QWidget *parent = nullptr);
    ~UiDownload();

private slots:
    void onStartDownload(const QString &jobId, const QString &key,
                         const QString &localPath, qulonglong total);
    void onDownloadProcess(const QString &jobId, qulonglong transferedSize, qulonglong totalSize);
    void onDownloadSuccess(const QString &jobId);
    void onError(int api, const QString &msg, const QJsonValue &req);

private:
    UiProgressWidget *findTableWidgetItem(const QString& jobId);
    void initHeader();
private:
    Ui::UiDownload *ui;
};

#endif // UIDOWNLOAD_H

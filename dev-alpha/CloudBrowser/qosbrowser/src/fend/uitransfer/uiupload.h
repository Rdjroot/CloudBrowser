#ifndef UIUPLOAD_H
#define UIUPLOAD_H

#include <QJsonValue>
#include <QWidget>

namespace Ui {
class UiUpload;
}
class UiProgressWidget;
class UiUpload : public QWidget
{
    Q_OBJECT

public:
    explicit UiUpload(QWidget *parent = nullptr);
    ~UiUpload();

private slots:
    void onStartUpload(const QString& jobId, const QString& key, const QString& localPath);
    void onUploadProcess(const QString& jobId, qulonglong transferedSize, qulonglong totalSize);
    void onUploadSuccess(const QString& jobId);
    void onError(int api, const QString& msg, const QJsonValue &req);

private:
    UiProgressWidget *findTableWidgetItem(const QString& jobId);
    void initHeader();

private:
    Ui::UiUpload *ui;
};

#endif // UIUPLOAD_H

#ifndef MANSIGNALS_H
#define MANSIGNALS_H

#include <QObject>

#define MS ManSignals::instance()

/**
 * @brief 信号中心
 */
class ManSignals : public QObject
{
    Q_OBJECT
public:
    explicit ManSignals(QObject *parent = nullptr);
    static ManSignals* instance();

signals:
    void loginSuccess();
    void error(int api, const QString& msg);

    void unLogin();
};

#endif // MANSIGNALS_H

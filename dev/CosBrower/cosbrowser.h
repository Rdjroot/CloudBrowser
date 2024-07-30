#ifndef COSBROWSER_H
#define COSBROWSER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class CosBrowser; }
QT_END_NAMESPACE

class CosBrowser : public QWidget
{
    Q_OBJECT

public:
    CosBrowser(QWidget *parent = nullptr);
    ~CosBrowser();

private:
    Ui::CosBrowser *ui;
};
#endif // COSBROWSER_H

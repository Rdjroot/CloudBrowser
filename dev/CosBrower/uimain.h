#ifndef UIMAIN_H
#define UIMAIN_H

#include <QWidget>

namespace Ui {
class UiMain;
}

class UiMain : public QWidget
{
    Q_OBJECT

public:
    explicit UiMain(QWidget *parent = nullptr);
    ~UiMain();

private:
    Ui::UiMain *ui;
};

#endif // UIMAIN_H

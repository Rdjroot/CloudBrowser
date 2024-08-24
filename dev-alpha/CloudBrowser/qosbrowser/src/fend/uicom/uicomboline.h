#ifndef UICOMBOLINE_H
#define UICOMBOLINE_H

#include <QLineEdit>
#include <QListView>
#include <QStringListModel>


/**
 * 联想提示框
 */
class UiComboLine : public QLineEdit
{
    Q_OBJECT
public:
    UiComboLine(QWidget* parent = nullptr);
    UiComboLine(const QStringList& words, QWidget* parent = nullptr);

    // 设置提示列表
    void setWords(const QStringList& words);
    void setWords(const QList<int> words);
    void setWords(int start = 1, int len=10);

    // 获取提示列表
    QStringList getWords();

signals:
    // 提示列表被选中
    void itemSelected(const QString& text);

protected:
    void mousePressEvent(QMouseEvent*) override;
};

#endif // UICOMBOLINE_H

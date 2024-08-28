#include "uicomboline.h"
#include "src/fend/uidelegates/uitableitemdelegate.h"
#include <QCompleter>
#include <QListView>

UiComboLine::UiComboLine(QWidget *parent): QLineEdit(parent)
{
    UiComboLine(QStringList(), parent);
}

UiComboLine::UiComboLine(const QStringList &words, QWidget *parent): QLineEdit(parent)
{
    setWords(words);
}

void UiComboLine::setWords(const QStringList &words)
{
    QCompleter* com = new QCompleter(words, this);
    QAbstractItemView *view = com->popup();

    // 显示候选词的列表，隐藏滚动条
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 设置为自定义的item代理
    view->setItemDelegate(new UiTableItemDelegate(view));
    view->setCursor(Qt::PointingHandCursor);

    // 客户选中关键词后捕获发送
    connect(com, QOverload<const QString &>::of(&QCompleter::activated),
            [=](const QString &text){
                emit itemSelected(text);
    });

    // 设置自动补全器
    setCompleter(com);
    // 设置 QCompleter 的过滤模式为 Qt::MatchContains，
    // 这意味着当用户输入部分内容时，
    // 自动补全器会显示所有包含该输入内容的候选词，而不仅仅是以该内容开头的词。
    com->setFilterMode(Qt::MatchContains);
}

void UiComboLine::setWords(const QList<int> words)
{
    QStringList strs;
    for(int i : words)
    {
        strs << QString::number(i);
    }
    setWords(strs);
}

void UiComboLine::setWords(int start, int len)
{
    QStringList strs;
    for(int i = start; i <= len; i++)
    {
        strs << QString::number(i);
    }
    setWords(strs);
}

QStringList UiComboLine::getWords()
{
    QStringList strs;
    if(completer())     // 判断是否设置了completer
    {
        QAbstractItemModel* m = completer()->model();
        for(int i = 0; i< m->rowCount();i++)
        {
            strs << m->index(i,0).data().toString();    // 获取补全器里所有内容
        }
    }
    return strs;
}

void UiComboLine::mousePressEvent(QMouseEvent *e)
{
    if(completer())
    {
        completer()->complete();    // 触发后的展示模式
    }
    QLineEdit::mousePressEvent(e);
}

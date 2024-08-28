#include "uipagewidget.h"
#include "qdebug.h"
#include "qmath.h"
#include "ui_uipagewidget.h"

UiPageWidget::UiPageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiPageWidget)
{
    ui->setupUi(this);
    connect(ui->btnNext, &UiPushButton::clicked, this, &UiPageWidget::next);
    connect(ui->btnPre, &UiPushButton::clicked, this, &UiPageWidget::pre);

    ui->lineMaxRows->setAlignment(Qt::AlignHCenter);    // 文本摆放方式
    ui->lineMaxRows->setReadOnly(true);
    connect(ui->lineMaxRows, &UiComboLine::itemSelected, this, &UiPageWidget::onMaxRowsItemSelected);

    ui->lineCurrentPage->setAlignment(Qt::AlignHCenter);
    ui->lineCurrentPage->setReadOnly(true);
    connect(ui->lineCurrentPage, &UiComboLine::itemSelected, this, &UiPageWidget::onCurrentPageSelected);

    ui->btnNext->setDisabled(true);
    ui->btnPre->setDisabled(true);
}

UiPageWidget::~UiPageWidget()
{
    delete ui;
}

int UiPageWidget::totalRow() const
{
    return m_totalRow;
}

int UiPageWidget::maxRow() const
{
    return m_maxRow;
}

int UiPageWidget::currentPage() const
{
    return m_currentPage;
}

int UiPageWidget::pageCount() const
{
    if(m_totalRow == 0)
    {
        return 1;
    }
    // 每页显示条目
    return qCeil(m_totalRow/float(m_maxRow));
}

int UiPageWidget::isFirstPage() const
{
    return currentPage() == 1;
}

int UiPageWidget::isLastPage() const
{
    return currentPage() == pageCount();
}

void UiPageWidget::setTotalRow(int newTotalRow)
{
    m_totalRow = newTotalRow;
    ui->label->setText(QString::fromLocal8Bit("共%1条，每页").arg(newTotalRow));
    reset();
}

void UiPageWidget::setMaxRow(int rows)
{
    QStringList words = ui->lineMaxRows->getWords();
    for(const auto& num: qAsConst(words))
    {
        if(num.toInt() == rows)
        {
            m_maxRow = rows;
            reset();
            break;
        }
    }
}

void UiPageWidget::setMaxRowList(const QList<int> rowList)
{
    ui->lineMaxRows->setWords(rowList);
    if(rowList.size() > 0)
    {
        ui->lineMaxRows->setText(QString::number(rowList[0]));
        setMaxRow(rowList[0]);
    }
}

void UiPageWidget::next()
{
    jumpTo(currentPage()+1);
}

void UiPageWidget::pre()
{
    jumpTo(currentPage()-1);
}

void UiPageWidget::jumpTo(int page)
{
    if(page != currentPage())
    {
        switchPage(page);
    }
}

void UiPageWidget::onCurrentPageSelected(const QString &text)
{
    if(m_currentPage != text.toInt())
        jumpTo(text.toInt());
}

void UiPageWidget::onMaxRowsItemSelected(const QString &text)
{
    setMaxRow(text.toInt());
}

void UiPageWidget::setPageCount()
{
    int count = pageCount();
    ui->labelPageCount->setText("/" + QString::number(count));
    ui->lineCurrentPage->setWords(1, count);
    ui->lineCurrentPage->setText("1");
}

void UiPageWidget::reset()
{
    setPageCount();
    switchPage(1);      // 重置为首页
}

void UiPageWidget::switchPage(int newCurrentPage)
{
    m_currentPage = newCurrentPage;
    ui->lineCurrentPage->setText(QString::number(newCurrentPage));
    ui->btnPre->setDisabled(isFirstPage());
    ui->btnNext->setDisabled(isLastPage());

    int start = (newCurrentPage -1)*maxRow();
    int left = (totalRow())-start;
    int len = left < maxRow() ? left: maxRow();
    qDebug() << QString("switchPage %1,%2").arg(start).arg(len);
    emit pageNumChanged(start,len);
}

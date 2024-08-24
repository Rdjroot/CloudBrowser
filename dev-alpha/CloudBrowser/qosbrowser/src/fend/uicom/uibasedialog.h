#ifndef UIBASEDIALOG_H
#define UIBASEDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class UiBaseDialog; }
QT_END_NAMESPACE

/**
 * @brief 基础页面框架
 */
class UiBaseDialog : public QDialog
{
    Q_OBJECT

public:
    UiBaseDialog(QWidget *parent = nullptr);
    ~UiBaseDialog();

    /**
     * @brief 设置标题
     * @param title 标题文本
    */
    void setTitle(const QString& title);

    /**
     * @brief 设置logo
     * @param path logo图片路径
    */
    void setLogo(const QString& path);

    /**
     * @brief 添加最小化按钮
     * @param path 按钮图片路径
     * @param hoverPath 按钮悬浮图片路径
    */
    void addMinButton(const QString& path, const QString& hoverPath);

    /**
     * @brief 添加最大化按钮
     * @param maxPath 最大化按钮图片路径
     * @param maxPathHover 最大化按钮悬浮图片路径
     * @param normalPath 还原按钮图片路径
     * @param normalPathHover 还原按钮悬浮图片路径
    */
    void addMaxButton(const QString& maxPath, const QString& maxPathHover,
                      const QString& normalPath, const QString& normalPathHover);

    /**
     * @brief 添加一个新的按钮
     * @param path 按钮图片路径
     * @param hoverPath 按钮悬浮图片路径
     * @return 新增的按钮指针
    */
    QPushButton* addButton(const QString&path, const QString& hoverPath);

    /**
     * @brief 设置按钮图片
     * @param btn 按钮指针
     * @param path 按钮图片路径
     * @param hoverPath 按钮悬浮图片路径
    */
    void setButtonImage(QPushButton* btn, const QString& path, const QString& hoverPath);

    /**
     * @brief 设置所有按钮为统一大小
     * @param w 大小
    */
    void setAllButtonSize(int w = 20);

    /**
     * @brief 设置可见性
     */
    void setKeyDisabled();

    /**
     * @brief 添加标题栏分隔线
     * @param w 宽度
     */
    void addTitleLine(int w=2);

protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    // 拦截回车、Esc或另一个回车键的事件
    bool eventFilter(QObject *obj, QEvent * event);
    QWidget* body();

private:
    void addCloseButton(const QString& path, const QString& hoverPath);
    void addWidget(QWidget* w);

protected:
    Ui::UiBaseDialog *m_ui;

private:
    QPoint m_start;
    int m_sz = 20;
};
#endif // UIBASEDIALOG_H

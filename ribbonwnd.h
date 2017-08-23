#ifndef RIBBONWND_H
#define RIBBONWND_H

#include <QDialog>

class QAbstractItemModel;
namespace Ui {
class RibbonWnd;
}

class RibbonWnd : public QDialog
{
    Q_OBJECT

public:
    explicit RibbonWnd(int depth_, QWidget *parent = 0);
    void setModel(QAbstractItemModel *model);

    QFontMetrics getRibbonFontMetrics();
    ~RibbonWnd();

public slots:
    void toggle();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    int depth;
    Ui::RibbonWnd *ui;
    QPoint drag_pos;
};

#endif // RIBBONWND_H

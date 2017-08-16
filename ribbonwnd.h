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
    explicit RibbonWnd(QWidget *parent = 0);
    void setModel(QAbstractItemModel *model);
    ~RibbonWnd();

public slots:
    void toggle();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::RibbonWnd *ui;
    QPoint drag_pos;
};

#endif // RIBBONWND_H

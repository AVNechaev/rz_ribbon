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

private:
    Ui::RibbonWnd *ui;
};

#endif // RIBBONWND_H

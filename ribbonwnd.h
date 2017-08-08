#ifndef RIBBONWND_H
#define RIBBONWND_H

#include <QDialog>

namespace Ui {
class RibbonWnd;
}

class RibbonWnd : public QDialog
{
    Q_OBJECT

public:
    explicit RibbonWnd(QWidget *parent = 0);
    ~RibbonWnd();

public slots:
    void toggle();

private:
    Ui::RibbonWnd *ui;
};

#endif // RIBBONWND_H

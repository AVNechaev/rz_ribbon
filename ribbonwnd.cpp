#include "ribbonwnd.h"
#include "ui_ribbonwnd.h"

RibbonWnd::RibbonWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RibbonWnd)
{
    ui->setupUi(this);
}

RibbonWnd::~RibbonWnd()
{
    delete ui;
}

void RibbonWnd::toggle()
{
    if(isVisible())
        hide();
    else
        show();
}

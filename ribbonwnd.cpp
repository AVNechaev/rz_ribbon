#include "ribbonwnd.h"
#include "ui_ribbonwnd.h"

RibbonWnd::RibbonWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RibbonWnd)
{
    ui->setupUi(this);
    setStyleSheet("background-color:#37474f; color:white; font-size: 11px");
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

void RibbonWnd::setModel(QAbstractItemModel *model)
{
    ui->tblMain->setModel(model);
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

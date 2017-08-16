#include "ribbonwnd.h"
#include "ui_ribbonwnd.h"

#include <QMouseEvent>

RibbonWnd::RibbonWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RibbonWnd)
{
    ui->setupUi(this);
    setStyleSheet("background-color:#37474f; color:white; font-size: 12px");
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);    
    ui->tblMain->setAttribute(Qt::WA_TransparentForMouseEvents);
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

void RibbonWnd::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - drag_pos);
        event->accept();
    }
}

void RibbonWnd::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        drag_pos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

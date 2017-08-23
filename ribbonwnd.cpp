#include "ribbonwnd.h"
#include "ui_ribbonwnd.h"

#include <QMouseEvent>

RibbonWnd::RibbonWnd(int depth_, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RibbonWnd),
    depth(depth_)
{
    ui->setupUi(this);
    setStyleSheet("background-color:#37474f; color:white; font-size: 12px; font-family: \"Roboto Condensed\"");
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);    
    ui->tblMain->setAttribute(Qt::WA_TransparentForMouseEvents);    
}

void RibbonWnd::setModel(QAbstractItemModel *model)
{
    ui->tblMain->setModel(model);
}

QFontMetrics RibbonWnd::getRibbonFontMetrics()
{
    return QFontMetrics(ui->tblMain->font());
}

RibbonWnd::~RibbonWnd()
{
    delete ui;
}

void RibbonWnd::toggle()
{    
    resize(this->width(), ui->tblMain->verticalHeader()->minimumSectionSize()*depth + ui->gridLayout->margin()*2);
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

void RibbonWnd::keyPressEvent(QKeyEvent *event)
{
        if(event->key() != Qt::Key_Escape)
            QDialog::keyPressEvent(event);
        else
            event->accept();
}
